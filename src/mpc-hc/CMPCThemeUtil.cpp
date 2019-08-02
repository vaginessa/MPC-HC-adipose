#include "stdafx.h"
#include "CMPCThemeUtil.h"
#include "CMPCTheme.h"
#include "mplayerc.h"
#include "MainFrm.h"
#include "CMPCThemeStatic.h"
#include "CMPCThemeDialog.h"
#include "CMPCThemeSliderCtrl.h"
#include "CMPCThemeTabCtrl.h"


#undef SubclassWindow


CBrush CMPCThemeUtil::contentBrush = CBrush();
CBrush CMPCThemeUtil::windowBrush = CBrush();
CBrush CMPCThemeUtil::controlAreaBrush = CBrush();
CBrush CMPCThemeUtil::W10DarkThemeFileDialogInjectedBGBrush = CBrush();

CFont CMPCThemeUtil::dialogFont = CFont();

CMPCThemeUtil::CMPCThemeUtil() {
}

CMPCThemeUtil::~CMPCThemeUtil() {
    for (u_int i = 0; i < allocatedWindows.size(); i++) {
        delete allocatedWindows[i];
    }
}


void CMPCThemeUtil::fulfillThemeReqs(CWnd* wnd) {
    if (AfxGetAppSettings().bMPCThemeLoaded) {

        initHelperObjects(wnd);

        CWnd* pChild = wnd->GetWindow(GW_CHILD);
        while (pChild) {
            LRESULT lRes = pChild->SendMessage(WM_GETDLGCODE, 0, 0);
            CWnd* tChild = pChild;
            pChild = pChild->GetNextWindow(); //increment before any unsubclassing
            CString runtimeClass = tChild->GetRuntimeClass()->m_lpszClassName;
            TCHAR windowClass[MAX_PATH];
            ::GetClassName(tChild->GetSafeHwnd(), windowClass, _countof(windowClass));
            DWORD style = tChild->GetStyle();
            DWORD buttonType = (style & BS_TYPEMASK);
            DWORD staticStyle = (style & SS_TYPEMASK);
            CString windowTitle;

            if (tChild->m_hWnd)
                tChild->GetWindowText(windowTitle);
            if (runtimeClass.Find(_T("CMPCTheme")) != 0) {
                if (DLGC_BUTTON == (lRes & DLGC_BUTTON)) {
                    if (DLGC_DEFPUSHBUTTON == (lRes & DLGC_DEFPUSHBUTTON) || DLGC_UNDEFPUSHBUTTON == (lRes & DLGC_UNDEFPUSHBUTTON)) {
                        CMPCThemeButton* pObject = new CMPCThemeButton();
                        makeThemed(pObject, tChild);
                    } else if (DLGC_BUTTON == (lRes & DLGC_BUTTON) && (buttonType == BS_CHECKBOX || buttonType == BS_AUTOCHECKBOX)) {
                        CMPCThemeRadioOrCheck* pObject = new CMPCThemeRadioOrCheck();
                        makeThemed(pObject, tChild);
                    } else if (DLGC_BUTTON == (lRes & DLGC_BUTTON) && (buttonType == BS_3STATE || buttonType == BS_AUTO3STATE)) {
                        CMPCThemeRadioOrCheck* pObject = new CMPCThemeRadioOrCheck();
                        makeThemed(pObject, tChild);
                    } else if (DLGC_RADIOBUTTON == (lRes & DLGC_RADIOBUTTON) && (buttonType == BS_RADIOBUTTON || buttonType == BS_AUTORADIOBUTTON)) {
                        CMPCThemeRadioOrCheck* pObject = new CMPCThemeRadioOrCheck();
                        makeThemed(pObject, tChild);
                    } else { //what other buttons?
//                        int a = 1;
                    }
                } else if (0 == _tcsicmp(windowClass, WC_SCROLLBAR)) {
                } else if (0 == _tcsicmp(windowClass, WC_BUTTON) && buttonType == BS_GROUPBOX) {
                    CMPCThemeGroupBox* pObject = new CMPCThemeGroupBox();
                    makeThemed(pObject, tChild);
                    SetWindowTheme(tChild->GetSafeHwnd(), L"", L"");
                } else if (0 == _tcsicmp(windowClass, WC_STATIC) && SS_ICON == staticStyle) { //don't touch icons for now
                } else if (0 == _tcsicmp(windowClass, WC_STATIC) && SS_BITMAP == staticStyle) { //don't touch BITMAPS for now
                } else if (0 == _tcsicmp(windowClass, WC_STATIC) && SS_OWNERDRAW == staticStyle) { //don't touch OWNERDRAW for now
                } else if (0 == _tcsicmp(windowClass, WC_STATIC) && (staticStyle < SS_OWNERDRAW || SS_ETCHEDHORZ == staticStyle || SS_ETCHEDVERT == staticStyle || SS_ETCHEDFRAME == staticStyle)) {
                    tChild->SetFont(&dialogFont);
                    LITEM li = { 0 };
                    li.mask = LIF_ITEMINDEX | LIF_ITEMID;
                    if (::SendMessage(tChild->GetSafeHwnd(), LM_GETITEM, 0, (LPARAM)& li)) { //we appear to have a linkctrl
                        CMPCThemeLinkCtrl* pObject = new CMPCThemeLinkCtrl();
                        makeThemed(pObject, tChild);
                    } else {
                        CMPCThemeStatic* pObject = new CMPCThemeStatic();
                        makeThemed(pObject, tChild);
                    }
                } else if (0 == _tcsicmp(windowClass, WC_EDIT)) {
                    CMPCThemeEdit* pObject = new CMPCThemeEdit();
                    makeThemed(pObject, tChild);
                } else if (0 == _tcsicmp(windowClass, UPDOWN_CLASS)) {
                    CMPCThemeSpinButtonCtrl* pObject = new CMPCThemeSpinButtonCtrl();
                    makeThemed(pObject, tChild);
                } else if (0 == _tcsicmp(windowClass, _T("#32770"))) { //dialog class
                    CMPCThemeDialog* pObject = new CMPCThemeDialog();
                    makeThemed(pObject, tChild);
                    fulfillThemeReqs(tChild);
                } else if (windowTitle == _T("CInternalPropertyPageWnd")) { //internal window encompassing property pages
                    fulfillThemeReqs(tChild);
                } else if (0 == _tcsicmp(windowClass, WC_COMBOBOX)) {
                    CMPCThemeComboBox* pObject = new CMPCThemeComboBox();
                    makeThemed(pObject, tChild);
                } else if (0 == _tcsicmp(windowClass, TRACKBAR_CLASS)) {
                    CMPCThemeSliderCtrl* pObject = new CMPCThemeSliderCtrl();
                    makeThemed(pObject, tChild);
                } else if (0 == _tcsicmp(windowClass, WC_TABCONTROL)) {
                    CMPCThemeTabCtrl* pObject = new CMPCThemeTabCtrl();
                    makeThemed(pObject, tChild);
                } else {
                    //                    int a = 1;
                }
            }

        }
    }
}

void CMPCThemeUtil::initHelperObjects(CWnd* wnd) {
    if (contentBrush.m_hObject == nullptr) contentBrush.CreateSolidBrush(CMPCTheme::ContentBGColor);
    if (windowBrush.m_hObject == nullptr) windowBrush.CreateSolidBrush(CMPCTheme::WindowBGColor);
    if (controlAreaBrush.m_hObject == nullptr) controlAreaBrush.CreateSolidBrush(CMPCTheme::ControlAreaBGColor);
    if (W10DarkThemeFileDialogInjectedBGBrush.m_hObject == nullptr) W10DarkThemeFileDialogInjectedBGBrush.CreateSolidBrush(CMPCTheme::W10DarkThemeFileDialogInjectedBGColor);
    if (dialogFont.m_hObject == nullptr) CMPCTheme::getFontByType(dialogFont, wnd->GetWindowDC(), CMPCTheme::CDDialogFont);
}

void CMPCThemeUtil::makeThemed(CWnd* pObject, CWnd* tChild) {
    if (CWnd::FromHandlePermanent(tChild->GetSafeHwnd()) == NULL) { //refuse to subclass if already subclassed.  in this case the member class should be updated rather than dynamically subclassing
        allocatedWindows.push_back(pObject);
        pObject->SubclassWindow(tChild->GetSafeHwnd());
    }
}

LRESULT CALLBACK wndProcFileDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    WNDPROC wndProcSink = NULL;
    wndProcSink = (WNDPROC)GetProp(hWnd, _T("WNDPROC_SINK"));
    VERIFY(wndProcSink);
    if (WM_CTLCOLOREDIT == uMsg) {
        return (LRESULT)CMPCThemeUtil::getCtlColorFileDialog((HDC)wParam, CTLCOLOR_EDIT);
    }
    if (!wndProcSink) return 0;
    return ::CallWindowProc(wndProcSink, hWnd, uMsg, wParam, lParam);
}


void CMPCThemeUtil::subClassFileDialog(CWnd* wnd, HWND hWnd, bool findSink) {
    if (AfxGetAppSettings().bWindows10DarkThemeActive) {
        initHelperObjects(wnd);
        HWND pChild = ::GetWindow(hWnd, GW_CHILD);

        while (pChild) {
            TCHAR childWindowClass[MAX_PATH];
            ::GetClassName(pChild, childWindowClass, _countof(childWindowClass));
            if (findSink) {
                if (0 == _tcsicmp(childWindowClass, _T("FloatNotifySink"))) { //children are the injected controls
                    subClassFileDialog(wnd, pChild, false); //recurse into the sinks
                }
            } else {
                if (0 == _tcsicmp(childWindowClass, WC_STATIC)) {
                    CWnd* c = CWnd::FromHandle(pChild);
                    c->UnsubclassWindow();
                    CMPCThemeStatic* pObject = new CMPCThemeStatic();
                    pObject->setFileDialogChild(true);
                    allocatedWindows.push_back(pObject);
                    pObject->SubclassWindow(pChild);
                } else if (0 == _tcsicmp(childWindowClass, WC_EDIT)) {
                    CWnd* c = CWnd::FromHandle(pChild);
                    c->UnsubclassWindow();
                    CMPCThemeEdit* pObject = new CMPCThemeEdit();
                    pObject->setFileDialogChild(true);
                    allocatedWindows.push_back(pObject);
                    pObject->SubclassWindow(pChild);
                    if (nullptr == GetProp(hWnd, _T("WNDPROC_SINK"))) {
                        LONG_PTR wndProcOld = ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG)wndProcFileDialog);
                        SetProp(hWnd, _T("WNDPROC_SINK"), (HANDLE)wndProcOld);
                    }
                }
            }
            pChild = ::GetNextWindow(pChild, GW_HWNDNEXT);
        }
    }
}
AFX_STATIC DLGITEMTEMPLATE* AFXAPI _AfxFindNextDlgItem(DLGITEMTEMPLATE* pItem, BOOL bDialogEx);
AFX_STATIC DLGITEMTEMPLATE* AFXAPI _AfxFindFirstDlgItem(const DLGTEMPLATE* pTemplate);

AFX_STATIC inline BOOL IsDialogEx(const DLGTEMPLATE* pTemplate) {
    return ((_DialogSplitHelper::DLGTEMPLATEEX*)pTemplate)->signature == 0xFFFF;
}

static inline WORD& DlgTemplateItemCount(DLGTEMPLATE* pTemplate) {
    if (IsDialogEx(pTemplate))
        return reinterpret_cast<_DialogSplitHelper::DLGTEMPLATEEX*>(pTemplate)->cDlgItems;
    else
        return pTemplate->cdit;
}

static inline const WORD& DlgTemplateItemCount(const DLGTEMPLATE* pTemplate) {
    if (IsDialogEx(pTemplate))
        return reinterpret_cast<const _DialogSplitHelper::DLGTEMPLATEEX*>(pTemplate)->cDlgItems;
    else
        return pTemplate->cdit;
}

bool CMPCThemeUtil::ModifyTemplates(CPropertySheet* sheet, CRuntimeClass* pageClass, DWORD id, DWORD addStyle, DWORD removeStyle) {
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        PROPSHEETHEADER m_psh = sheet->m_psh;
        for (int i = 0; i < sheet->GetPageCount(); i++) {
            CPropertyPage* pPage = sheet->GetPage(i);
            if (nullptr == AfxDynamicDownCast(pageClass, pPage)) {
                continue;
            }
            PROPSHEETPAGE* tpsp = &pPage->m_psp;

            const DLGTEMPLATE* pTemplate;
            if (tpsp->dwFlags & PSP_DLGINDIRECT) {
                pTemplate = tpsp->pResource;
            } else {
                HRSRC hResource = ::FindResource(tpsp->hInstance, tpsp->pszTemplate, RT_DIALOG);
                if (hResource == NULL) return false;
                HGLOBAL hTemplate = LoadResource(tpsp->hInstance, hResource);
                if (hTemplate == NULL) return false;
                pTemplate = (LPCDLGTEMPLATE)LockResource(hTemplate);
                if (pTemplate == NULL) return false;
            }

            if (afxOccManager != NULL) {
                DLGITEMTEMPLATE* pItem = _AfxFindFirstDlgItem(pTemplate);
                DLGITEMTEMPLATE* pNextItem;
                BOOL bDialogEx = IsDialogEx(pTemplate);

                int iItem, iItems = DlgTemplateItemCount(pTemplate);

                for (iItem = 0; iItem < iItems; iItem++) {
                    pNextItem = _AfxFindNextDlgItem(pItem, bDialogEx);
                    DWORD dwOldProtect, tp;
                    if (bDialogEx) {
                        _DialogSplitHelper::DLGITEMTEMPLATEEX* pItemEx = (_DialogSplitHelper::DLGITEMTEMPLATEEX*)pItem;
                        if (pItemEx->id == id) {
                            if (VirtualProtect(&pItemEx->style, sizeof(pItemEx->style), PAGE_READWRITE, &dwOldProtect)) {
                                pItemEx->style |= addStyle;
                                pItemEx->style &= ~removeStyle;
                                VirtualProtect(&pItemEx->style, sizeof(pItemEx->style), dwOldProtect, &tp);
                            }
                        }
                    } else {
                        if (pItem->id == id) {
                            if (VirtualProtect(&pItem->style, sizeof(pItem->style), PAGE_READWRITE, &dwOldProtect)) {
                                pItem->style |= addStyle;
                                pItem->style &= ~removeStyle;
                                VirtualProtect(&pItem->style, sizeof(pItem->style), dwOldProtect, &tp);
                            }
                        }
                    }
                    pItem = pNextItem;
                }
            }
        }
    }
    return true;
}

void CMPCThemeUtil::enableFileDialogHook() {
    CMainFrame* pMainFrame = AfxGetMainFrame();
    pMainFrame->enableFileDialogHook(this);
}

HBRUSH CMPCThemeUtil::getCtlColorFileDialog(HDC hDC, UINT nCtlColor) {
    if (CTLCOLOR_EDIT == nCtlColor) {
        ::SetTextColor(hDC, CMPCTheme::W10DarkThemeFileDialogInjectedTextColor);
        ::SetBkColor(hDC, CMPCTheme::W10DarkThemeFileDialogInjectedBGColor);
        return W10DarkThemeFileDialogInjectedBGBrush;
    } else if (CTLCOLOR_STATIC == nCtlColor) {
        ::SetTextColor(hDC, CMPCTheme::W10DarkThemeFileDialogInjectedTextColor);
        ::SetBkColor(hDC, CMPCTheme::W10DarkThemeFileDialogInjectedBGColor);
        return W10DarkThemeFileDialogInjectedBGBrush;
    } else {
        return NULL;
    }
}

HBRUSH CMPCThemeUtil::getCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        LRESULT lResult;
        if (pWnd->SendChildNotifyLastMsg(&lResult)) {
            return (HBRUSH)lResult;
        }
        if (CTLCOLOR_LISTBOX == nCtlColor) {
            pDC->SetTextColor(CMPCTheme::TextFGColor);
            pDC->SetBkColor(CMPCTheme::ContentBGColor);
            return contentBrush;
        } else {
            pDC->SetTextColor(CMPCTheme::TextFGColor);
            pDC->SetBkColor(CMPCTheme::WindowBGColor);
            return windowBrush;
        }
    }
    return nullptr;
}

bool CMPCThemeUtil::MPCThemeEraseBkgnd(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        CRect rect;
        pWnd->GetClientRect(rect);
        if (CTLCOLOR_DLG == nCtlColor) { //only supported "class" for now
            pDC->FillSolidRect(rect, CMPCTheme::WindowBGColor);
        } else {
            return false;
        }
        return true;
    } else {
        return false;
    }
}
