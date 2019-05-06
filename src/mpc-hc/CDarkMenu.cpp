#include "stdafx.h"
#include "CDarkMenu.h"
#include "CDarkTheme.h"
#include <strsafe.h>
#include "AppSettings.h"
#include "PPageAccelTbl.h"


std::map<UINT, CDarkMenu*> CDarkMenu::subMenuIDs;
const int CDarkMenu::subMenuPadding = 20;
const int CDarkMenu::iconSpacing = 22;
const int CDarkMenu::rowHeight = 22;
const int CDarkMenu::iconPadding = 10;
const int CDarkMenu::separatorPadding = 8;
const int CDarkMenu::separatorHeight = 7;
const int CDarkMenu::postTextSpacing = 20;
const int CDarkMenu::accelSpacing = 30;


IMPLEMENT_DYNAMIC(CDarkMenu, CMenu);

CDarkMenu::CDarkMenu(){
}


CDarkMenu::~CDarkMenu() {
    std::map<UINT, CDarkMenu*>::iterator itr = subMenuIDs.begin();
    while (itr != subMenuIDs.end()) {
        if (itr->second == this) {
            itr = subMenuIDs.erase(itr);
        } else {
            ++itr;
        }
    }

    for (u_int i = 0; i < allocatedItems.size(); i++) {
        delete allocatedItems[i];
    }
    for (u_int i = 0; i < allocatedMenus.size(); i++) {
        delete allocatedMenus[i];
    }
}

void CDarkMenu::ActivateDarkTheme(bool isMenubar) {

    MENUINFO MenuInfo = { 0 };
    MenuInfo.cbSize = sizeof(MENUINFO);
    MenuInfo.fMask = MIM_BACKGROUND | MIM_STYLE | MIM_APPLYTOSUBMENUS;
    MenuInfo.dwStyle = MNS_AUTODISMISS;
    MenuInfo.hbrBack = ::CreateSolidBrush(CDarkTheme::MenuBGColor);
    SetMenuInfo(&MenuInfo);

    int iMaxItems = GetMenuItemCount();
    for (int i = 0; i < iMaxItems; i++) {
		CString nameHolder;
        MenuObject* pObject = new MenuObject;
        allocatedItems.push_back(pObject);
        pObject->m_hIcon = NULL;
        pObject->isMenubar = isMenubar;
        if (i == 0) pObject->isFirstMenuInMenuBar = true;

        GetMenuString(i, pObject->m_strCaption, MF_BYPOSITION);

        UINT nID = GetMenuItemID(i);
        pObject->m_strAccel = CPPageAccelTbl::MakeAccelShortcutLabel(nID);

        subMenuIDs[nID] = this;

        MENUITEMINFO tInfo;
        ZeroMemory(&tInfo, sizeof(MENUITEMINFO));
        tInfo.fMask = MIIM_FTYPE;
        tInfo.cbSize = sizeof(MENUITEMINFO);
        GetMenuItemInfo(i, &tInfo, true);

        if (tInfo.fType & MFT_SEPARATOR) {
            pObject->isSeparator = true;
        }

        MENUITEMINFO mInfo;
        ZeroMemory(&mInfo, sizeof(MENUITEMINFO));

        mInfo.fMask = MIIM_FTYPE | MIIM_DATA;
        mInfo.fType = MFT_OWNERDRAW | tInfo.fType;
        mInfo.cbSize = sizeof(MENUITEMINFO);
        mInfo.dwItemData = (ULONG_PTR)pObject;
        SetMenuItemInfo(i, &mInfo, true);

        CMenu *t = GetSubMenu(i);
        if (nullptr != t) {
            CDarkMenu* pSubMenu = new CDarkMenu;
            allocatedMenus.push_back(pSubMenu);
            pSubMenu->Attach(t->GetSafeHmenu());
            pSubMenu->ActivateDarkTheme();
        }
    }
}

void CDarkMenu::ActivateItemDarkTheme(UINT i, bool byCommand) {

    int iMaxItems = GetMenuItemCount();

    CString nameHolder;
    MenuObject* pObject = new MenuObject;
    allocatedItems.push_back(pObject);
    pObject->m_hIcon = NULL;

    UINT posOrCmd = byCommand ? MF_BYCOMMAND : MF_BYPOSITION;

    GetMenuString(i, pObject->m_strCaption, posOrCmd);


    UINT nID;
    if (byCommand) {
        nID = i;
        bool found = false;
        for (int j = 0; j < iMaxItems; j++) {
            if (nID == GetMenuItemID(j)) {
                i = j;
                found = true;
                break;
            }
        }
        if (!found) return;
    } else {
        nID = GetMenuItemID(i);
    }

    pObject->m_strAccel = CPPageAccelTbl::MakeAccelShortcutLabel(nID);

    subMenuIDs[nID] = this;

    MENUITEMINFO tInfo;
    ZeroMemory(&tInfo, sizeof(MENUITEMINFO));
    tInfo.fMask = MIIM_FTYPE;
    tInfo.cbSize = sizeof(MENUITEMINFO);
    GetMenuItemInfo(i, &tInfo, true);

    if (tInfo.fType & MFT_SEPARATOR) {
        pObject->isSeparator = true;
    }

    MENUITEMINFO mInfo;
    ZeroMemory(&mInfo, sizeof(MENUITEMINFO));

    mInfo.fMask = MIIM_FTYPE | MIIM_DATA;
    mInfo.fType = MFT_OWNERDRAW | tInfo.fType;
    mInfo.cbSize = sizeof(MENUITEMINFO);
    mInfo.dwItemData = (ULONG_PTR)pObject;
    SetMenuItemInfo(i, &mInfo, true);

    CMenu *t = GetSubMenu(i);
    if (nullptr != t) {
        CDarkMenu* pSubMenu = new CDarkMenu;
        allocatedMenus.push_back(pSubMenu);
        pSubMenu->Attach(t->GetSafeHmenu());
        pSubMenu->ActivateDarkTheme();
    }
}

void CDarkMenu::ActivateItemDarkTheme(CMenu* parent, UINT i, bool byCommand) {
    CDarkMenu* t;
    if ((t = DYNAMIC_DOWNCAST(CDarkMenu, parent)) != nullptr) {
        t->ActivateItemDarkTheme(i, byCommand);
    }
}

UINT CDarkMenu::getPosFromID(CMenu * parent, UINT nID) {
    int iMaxItems = parent->GetMenuItemCount();
    for (int j = 0; j < iMaxItems; j++) {
        if (nID == parent->GetMenuItemID(j)) {
            return j;
        }
    }
    return (UINT)-1;
}

CDarkMenu* CDarkMenu::getParentMenu(UINT itemID) {
    if (subMenuIDs.count(itemID) == 1) {
        CDarkMenu *m = subMenuIDs.at(itemID);
        /* // checks if submenu for overriding of onmeasureitem (win32 limitation).
           // but mpc-hc doesn't set up some submenus until later
           // which is too late for measureitem to take place
           // so we return all items for measuring
        MENUITEMINFO mInfo;
        ZeroMemory(&mInfo, sizeof(MENUITEMINFO));
        mInfo.fMask = MIIM_SUBMENU;
        mInfo.cbSize = sizeof(MENUITEMINFO);
        m->GetMenuItemInfo(itemID, &mInfo);
        if (mInfo.hSubMenu)      //  */
            return m;
    }

    return nullptr;
}


void CDarkMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {

    MenuObject* menuObject = (MenuObject*)lpDrawItemStruct->itemData;

    MENUITEMINFO mInfo;
    ZeroMemory(&mInfo, sizeof(MENUITEMINFO));

    mInfo.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_SUBMENU;
    mInfo.cbSize = sizeof(MENUITEMINFO);
    GetMenuItemInfo(lpDrawItemStruct->itemID, &mInfo);
  

    CRect rectFull(lpDrawItemStruct->rcItem);


    //CRect rectM(0, 0, rectFull.right - rectFull.left, rectFull.bottom - rectFull.top);
    CRect rectM = rectFull;
    CRect rectIcon(rectM.left, rectM.top, rectM.left + iconSpacing, rectM.bottom);
    CRect rectText(rectM.left + iconSpacing + iconPadding, rectM.top, rectM.right - subMenuPadding, rectM.bottom);
    CRect rectArrow(rectM.right - subMenuPadding, rectM.top, rectM.right, rectM.bottom);
    
    UINT captionAlign = DT_LEFT;


    COLORREF ArrowColor = CDarkTheme::SubmenuColor;
    COLORREF TextFGColor;
    COLORREF TextBGColor = CDarkTheme::MenuBGColor;
    //TextBGColor = R255; //test
    COLORREF TextSelectColor = CDarkTheme::MenuSelectedColor;

    CDC* mDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    /* for fake grayscale smoothing
    CDC* cDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    CDC *mDC = new mDC;
    CBitmap bitmap;
    CBitmap *pOldBmp;
    mDC->CreateCompatibleDC(cDC);
    bitmap.CreateCompatibleBitmap(cDC, rectM.right, rectM.bottom);
    pOldBmp = mDC->SelectObject(&bitmap);
    */

    if ((lpDrawItemStruct->itemState & ODS_DISABLED)) {
        TextFGColor = CDarkTheme::MenuItemDisabledColor;
        ArrowColor = CDarkTheme::MenuItemDisabledColor;
    } else {
        TextFGColor = CDarkTheme::TextFGColor;
    }

    int oldBKMode = mDC->SetBkMode(TRANSPARENT);
    mDC->FillSolidRect(&rectM, TextBGColor);

    if (menuObject->isMenubar) {
        if (menuObject->isFirstMenuInMenuBar) { //clean up white borders
            CRect wndSize;
            GetWindowRect(AfxGetMainWnd()->m_hWnd, &wndSize);

            CRect rectBorder(rectM.left, rectM.bottom, rectM.left + wndSize.right - wndSize.left, rectM.bottom+1);
            mDC->FillSolidRect(&rectBorder, CDarkTheme::MenuItemDisabledColor);
            ExcludeClipRect(lpDrawItemStruct->hDC, rectBorder.left, rectBorder.top, rectBorder.right, rectBorder.bottom);
        }
        rectM = rectFull;
        rectText = rectFull;
        captionAlign = DT_CENTER;
    } 

    if (mInfo.fType & MFT_SEPARATOR) {
        int centerOffset = (separatorHeight - 1) / 2;
        CRect rectSeparator(rectM.left + separatorPadding, rectM.top + centerOffset, rectM.right - separatorPadding, rectM.top + centerOffset + 1);
        mDC->FillSolidRect(&rectSeparator, CDarkTheme::MenuSeparatorColor);
    } else {



        COLORREF oldTextFGColor = mDC->SetTextColor(TextFGColor);
        CFont *font = CDarkTheme::getUIFont(lpDrawItemStruct->hDC, CDarkTheme::uiTextFont, 9);
        CFont* pOldFont = mDC->SelectObject(font);
        delete font;


        if ((lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE))) {
            mDC->FillSolidRect(&rectM, TextSelectColor);
        }

        if (lpDrawItemStruct->itemState & ODS_NOACCEL) { //removing single &s before drawtext
            CString t = menuObject->m_strCaption;
            t.Replace(TEXT("&&"), TEXT("{{amp}}"));
            t.Remove(TEXT('&'));
            t.Replace(TEXT("{{amp}}"), TEXT("&&"));

            mDC->DrawText(t, rectText, DT_VCENTER | captionAlign | DT_SINGLELINE);
        }
        else {
            mDC->DrawText(menuObject->m_strCaption, rectText, DT_VCENTER | captionAlign | DT_SINGLELINE);
        }

        if (!menuObject->isMenubar) {

            if (menuObject->m_strAccel.GetLength() > 0) {
                mDC->DrawText(menuObject->m_strAccel, rectText, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
            }


            if (mInfo.hSubMenu) {
                font = CDarkTheme::getUIFont(lpDrawItemStruct->hDC, CDarkTheme::uiSymbolFont, 14, FW_BOLD); //this seems right but explorer has subpixel hints and we don't. why (directdraw)?

                mDC->SelectObject(font);
                mDC->SetTextColor(ArrowColor);
                mDC->DrawText(TEXT(">"), rectArrow, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
                delete font;
            }

            if (mInfo.fState & MFS_CHECKED) {
                CString check;
                int size;
                if (mInfo.fType & MFT_RADIOCHECK) {
                    check = TEXT("\u25CF"); //bullet
                    size = 6;
                }
                else {
                    check = TEXT("\u2714"); //checkmark
                    size = 10;
                }
                font = CDarkTheme::getUIFont(lpDrawItemStruct->hDC, CDarkTheme::uiSymbolFont, size, FW_REGULAR); //this seems right but explorer has subpixel hints and we don't. why (directdraw)?
                mDC->SelectObject(font);
                mDC->SetTextColor(TextFGColor);
                mDC->DrawText(check, rectIcon, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
                delete font;
            }
        }

        mDC->SetBkMode(oldBKMode);
        mDC->SetTextColor(oldTextFGColor);
        mDC->SelectObject(pOldFont);


        //fake greyscale anti-aliasing to emulate explorer (using directdraw?) SLOW!
        /*
        for (int y = 0; y < rectM.bottom; y++) {
            for (int x = 0; x < rectM.right; x++) {
                COLORREF rgb = mDC->GetPixel(x, y);
                BYTE r = GetRValue(rgb);
                BYTE g = GetGValue(rgb);
                BYTE b = GetBValue(rgb);
                BYTE bw = (BYTE)(0.299 * r + 0.587 * g + 0.114 * b);
             //   mDC->SetPixel(x, y, RGB(bw, bw, bw));
            }
        }
        cDC->BitBlt(rectFull.left, rectFull.top, rectM.right, rectM.bottom, &mDC, 0, 0, SRCCOPY);
        mDC->DeleteDC();
    */
    }
    ExcludeClipRect(lpDrawItemStruct->hDC, rectFull.left, rectFull.top, rectFull.right, rectFull.bottom);
}

void CDarkMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) {
    lpMeasureItemStruct->itemHeight = rowHeight;
    MenuObject* mo = (MenuObject*)lpMeasureItemStruct->itemData;
    HDC hDC = ::GetDC(NULL);
    if (mo->isSeparator) {
        lpMeasureItemStruct->itemWidth = 0;
        lpMeasureItemStruct->itemHeight = separatorHeight;
    } else {
        CSize cs = CDarkTheme::GetTextSize(mo->m_strCaption, hDC);
        if (mo->isMenubar) {
            lpMeasureItemStruct->itemWidth = cs.cx;
        } else {
            lpMeasureItemStruct->itemWidth = iconSpacing + cs.cx + postTextSpacing + subMenuPadding;
            if (mo->m_strAccel.GetLength() > 0) {
                cs = CDarkTheme::GetTextSize(mo->m_strAccel, hDC);
                lpMeasureItemStruct->itemWidth += accelSpacing + cs.cx;
            }
        }
    }
}

CDarkMenu* CDarkMenu::GetSubMenu(int nPos) {
    return (CDarkMenu*) CMenu::GetSubMenu(nPos);
}

void CDarkMenu::updateItem(CCmdUI* pCmdUI) {
    CMenu* cm = pCmdUI->m_pMenu;

    if (DYNAMIC_DOWNCAST(CDarkMenu, cm)) {
        MENUITEMINFO mInfo;
        ZeroMemory(&mInfo, sizeof(MENUITEMINFO));

        mInfo.fMask = MIIM_DATA;
        mInfo.cbSize = sizeof(MENUITEMINFO);
        VERIFY(cm->GetMenuItemInfo(pCmdUI->m_nID, &mInfo));
        
        MenuObject* menuObject = (MenuObject*)mInfo.dwItemData;
        cm->GetMenuString(pCmdUI->m_nID, menuObject->m_strCaption, MF_BYCOMMAND);
    }
}

