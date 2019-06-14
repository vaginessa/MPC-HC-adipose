#include "stdafx.h"
#include "CDarkChildHelper.h"
#include "CDarkTheme.h"
#include "mplayerc.h"
#undef SubclassWindow


CBrush CDarkChildHelper::darkContentBrush = CBrush();
CBrush CDarkChildHelper::darkWindowBrush = CBrush();
CBrush CDarkChildHelper::darkControlAreaBrush = CBrush();
CFont CDarkChildHelper::dialogFont = CFont();

CDarkChildHelper::CDarkChildHelper() {
}

CDarkChildHelper::~CDarkChildHelper() {
    for (u_int i = 0; i < allocatedButtons.size(); i++) {
        delete allocatedButtons[i];
    }
    for (u_int i = 0; i < allocatedGroupBoxes.size(); i++) {
        delete allocatedGroupBoxes[i];
    }
    for (u_int i = 0; i < allocatedLinkCtrls.size(); i++) {
        delete allocatedLinkCtrls[i];
    }
    for (u_int i = 0; i < allocatedCheckBoxes.size(); i++) {
        delete allocatedCheckBoxes[i];
    }
    for (u_int i = 0; i < allocatedRadioButtons.size(); i++) {
        delete allocatedRadioButtons[i];
    }
    for (u_int i = 0; i < allocatedEdits.size(); i++) {
        delete allocatedEdits[i];
    }
}

void CDarkChildHelper::enableDarkThemeIfActive(CWnd *wnd) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {

        if (darkContentBrush.m_hObject == nullptr) darkContentBrush.CreateSolidBrush(CDarkTheme::ContentBGColor);
        if (darkWindowBrush.m_hObject == nullptr) darkWindowBrush.CreateSolidBrush(CDarkTheme::WindowBGColor);
        if (darkControlAreaBrush.m_hObject == nullptr) darkControlAreaBrush.CreateSolidBrush(CDarkTheme::ControlAreaBGColor);
        if (dialogFont.m_hObject == nullptr) CDarkTheme::getUIFont(dialogFont, ::GetDC(NULL), CDarkTheme::CDDialogFont);

        CWnd* pChild = wnd->GetWindow(GW_CHILD);
        while (pChild) {
            LRESULT lRes = pChild->SendMessage(WM_GETDLGCODE, 0, 0);
            CWnd* tChild = pChild;
            pChild = pChild->GetNextWindow(); //increment before any unsubclassing
            CString runtimeClass = tChild->GetRuntimeClass()->m_lpszClassName;
            TCHAR windowClass[MAX_PATH];
            ::GetClassName(tChild->GetSafeHwnd(), windowClass, _countof(windowClass));
            DWORD style = tChild->GetStyle();
            DWORD type = (style & BS_TYPEMASK);
            if (runtimeClass.Find(_T("CDark")) != 0) { //do not subclass any members already of type CDarkxxx
                if (lRes & (DLGC_DEFPUSHBUTTON | DLGC_UNDEFPUSHBUTTON)) {
                    CDarkButton * pObject = new CDarkButton();
                    allocatedButtons.push_back(pObject);
                    pObject->SubclassWindow(tChild->GetSafeHwnd());
                } else if (0 != (lRes & DLGC_STATIC) && type == BS_GROUPBOX) {
                    CDarkGroupBox * pObject = new CDarkGroupBox();
                    allocatedGroupBoxes.push_back(pObject);
                    pObject->SubclassWindow(tChild->GetSafeHwnd());
                    SetWindowTheme(tChild->GetSafeHwnd(), L"", L"");
                } else if (0 != (lRes & DLGC_STATIC) && type == BS_TEXT) {
                    tChild->SetFont(&dialogFont);
                    LITEM li = { 0 };
                    li.mask = LIF_ITEMINDEX | LIF_ITEMID;
                    if (::SendMessage(tChild->GetSafeHwnd(), LM_GETITEM, 0, (LPARAM)&li)) { //we appear to have a linkctrl
                        CDarkLinkCtrl * pObject = new CDarkLinkCtrl();
                        allocatedLinkCtrls.push_back(pObject);
                        pObject->SubclassWindow(tChild->GetSafeHwnd());
                    }
                } else if (0 != (lRes & DLGC_BUTTON) && (type == BS_CHECKBOX || type == BS_AUTOCHECKBOX)) {
                    CDarkRadioOrCheck * pObject = new CDarkRadioOrCheck();
                    allocatedCheckBoxes.push_back(pObject);
                    pObject->SubclassWindow(tChild->GetSafeHwnd());
                } else if (0 != (lRes & DLGC_RADIOBUTTON) && (type == BS_RADIOBUTTON || type == BS_AUTORADIOBUTTON)) {
                    CDarkRadioOrCheck * pObject = new CDarkRadioOrCheck();
                    allocatedRadioButtons.push_back(pObject);
                    pObject->SubclassWindow(tChild->GetSafeHwnd());
                } else if (0 == _tcsicmp(windowClass, _T("EDIT")) ) {
                    CDarkEdit * pObject = new CDarkEdit();
                    allocatedEdits.push_back(pObject);
                    pObject->SubclassWindow(tChild->GetSafeHwnd());
                } else {
//                    int a = 1;
                }
            }

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

bool CDarkChildHelper::ModifyTemplates(CPropertySheet *sheet, CRuntimeClass* pageClass, DWORD id, DWORD addStyle, DWORD removeStyle) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
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
                DLGITEMTEMPLATE *pItem = _AfxFindFirstDlgItem(pTemplate);
                DLGITEMTEMPLATE *pNextItem;
                BOOL bDialogEx = IsDialogEx(pTemplate);

                int iItem, iItems = DlgTemplateItemCount(pTemplate);

                for (iItem = 0; iItem < iItems; iItem++) {
                    pNextItem = _AfxFindNextDlgItem(pItem, bDialogEx);
                    DWORD dwOldProtect, tp;
                    if (bDialogEx) {
                        _DialogSplitHelper::DLGITEMTEMPLATEEX *pItemEx = (_DialogSplitHelper::DLGITEMTEMPLATEEX *)pItem;
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
