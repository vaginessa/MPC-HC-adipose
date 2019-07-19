#include "stdafx.h"
#include "CDarkChildHelper.h"
#include "CDarkTheme.h"
#include "mplayerc.h"
#include "MainFrm.h"

#undef SubclassWindow


CBrush CDarkChildHelper::darkContentBrush = CBrush();
CBrush CDarkChildHelper::darkWindowBrush = CBrush();
CBrush CDarkChildHelper::darkControlAreaBrush = CBrush();
CBrush CDarkChildHelper::W10DarkThemeFileDialogInjectedBGBrush = CBrush();

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
    for (u_int i = 0; i < allocated3States.size(); i++) {
        delete allocated3States[i];
    }
    for (u_int i = 0; i < allocatedEdits.size(); i++) {
        delete allocatedEdits[i];
    }
    for (u_int i = 0; i < allocatedSpinButtons.size(); i++) {
        delete allocatedSpinButtons[i];
    }
    for (u_int i = 0; i < allocatedStatics.size(); i++) {
        delete allocatedStatics[i];
    }
}


void CDarkChildHelper::enableDarkThemeIfActive(CWnd *wnd) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {

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
            DWORD staticStyle = (style &  SS_TYPEMASK);
            CString t;

            if (tChild->m_hWnd)
                tChild->GetWindowText(t);
            if (runtimeClass.Find(_T("CDark")) != 0 && runtimeClass.Find(_T("CMPCTheme")) != 0) {
                if (DLGC_BUTTON == (lRes & DLGC_BUTTON)) {
                    if (DLGC_DEFPUSHBUTTON == (lRes & DLGC_DEFPUSHBUTTON) || DLGC_UNDEFPUSHBUTTON == (lRes & DLGC_UNDEFPUSHBUTTON)) {
                        CDarkButton * pObject = new CDarkButton();
                        allocatedButtons.push_back(pObject);
                        pObject->SubclassWindow(tChild->GetSafeHwnd());
                    } else if (DLGC_BUTTON == (lRes & DLGC_BUTTON) && (buttonType == BS_CHECKBOX || buttonType == BS_AUTOCHECKBOX)) {
                        CDarkRadioOrCheck * pObject = new CDarkRadioOrCheck();
                        allocatedCheckBoxes.push_back(pObject);
                        pObject->SubclassWindow(tChild->GetSafeHwnd());
                    } else if (DLGC_BUTTON == (lRes & DLGC_BUTTON) && (buttonType == BS_3STATE || buttonType == BS_AUTO3STATE)) {
                        CDarkRadioOrCheck * pObject = new CDarkRadioOrCheck();
                        allocated3States.push_back(pObject);
                        pObject->SubclassWindow(tChild->GetSafeHwnd());
                    } else if (DLGC_RADIOBUTTON == (lRes & DLGC_RADIOBUTTON) && (buttonType == BS_RADIOBUTTON || buttonType == BS_AUTORADIOBUTTON)) {
                        CDarkRadioOrCheck * pObject = new CDarkRadioOrCheck();
                        allocatedRadioButtons.push_back(pObject);
                        pObject->SubclassWindow(tChild->GetSafeHwnd());
                    } else { //what other buttons?
//                        int a = 1;
                    }
                } else if (0 == _tcsicmp(windowClass, WC_SCROLLBAR)) {
                } else if (0 == _tcsicmp(windowClass, WC_BUTTON) && buttonType == BS_GROUPBOX) {
                    CDarkGroupBox * pObject = new CDarkGroupBox();
                    allocatedGroupBoxes.push_back(pObject);
                    pObject->SubclassWindow(tChild->GetSafeHwnd());
                    SetWindowTheme(tChild->GetSafeHwnd(), L"", L"");
                } else if (0 == _tcsicmp(windowClass, WC_STATIC) && SS_ICON == staticStyle) { //don't touch icons for now
                } else if (0 == _tcsicmp(windowClass, WC_STATIC) && SS_BITMAP == staticStyle) { //don't touch BITMAPS for now
                } else if (0 == _tcsicmp(windowClass, WC_STATIC) && SS_OWNERDRAW == staticStyle) { //don't touch OWNERDRAW for now
                } else if (0 == _tcsicmp(windowClass, WC_STATIC) && ( staticStyle < SS_OWNERDRAW || SS_ETCHEDHORZ == staticStyle || SS_ETCHEDVERT == staticStyle || SS_ETCHEDFRAME == staticStyle))  {
                    tChild->SetFont(&dialogFont);
                    LITEM li = { 0 };
                    li.mask = LIF_ITEMINDEX | LIF_ITEMID;
                    if (::SendMessage(tChild->GetSafeHwnd(), LM_GETITEM, 0, (LPARAM)&li)) { //we appear to have a linkctrl
                        CDarkLinkCtrl * pObject = new CDarkLinkCtrl();
                        allocatedLinkCtrls.push_back(pObject);
                        pObject->SubclassWindow(tChild->GetSafeHwnd());
                    } else {
                        CDarkStatic * pObject = new CDarkStatic();
                        allocatedStatics.push_back(pObject);
                        pObject->SubclassWindow(tChild->GetSafeHwnd());
                    }
                } else if (0 == _tcsicmp(windowClass, WC_EDIT) ) {
                    CDarkEdit * pObject = new CDarkEdit();
                    allocatedEdits.push_back(pObject);
                    pObject->SubclassWindow(tChild->GetSafeHwnd());
                } else if (0 == _tcsicmp(windowClass, UPDOWN_CLASS)) {
                    CDarkSpinButtonCtrl * pObject = new CDarkSpinButtonCtrl();
                    allocatedSpinButtons.push_back(pObject);
                    pObject->SubclassWindow(tChild->GetSafeHwnd());
                } else {
//                    int a = 1;
                }
            }

        }
    }
}

void CDarkChildHelper::initHelperObjects(CWnd* wnd) {
    if (darkContentBrush.m_hObject == nullptr) darkContentBrush.CreateSolidBrush(CDarkTheme::ContentBGColor);
    if (darkWindowBrush.m_hObject == nullptr) darkWindowBrush.CreateSolidBrush(CDarkTheme::WindowBGColor);
    if (darkControlAreaBrush.m_hObject == nullptr) darkControlAreaBrush.CreateSolidBrush(CDarkTheme::ControlAreaBGColor);
    if (W10DarkThemeFileDialogInjectedBGBrush.m_hObject == nullptr) W10DarkThemeFileDialogInjectedBGBrush.CreateSolidBrush(CDarkTheme::W10DarkThemeFileDialogInjectedBGColor);
    if (dialogFont.m_hObject == nullptr) CDarkTheme::getFontByType(dialogFont, wnd->GetWindowDC(), CDarkTheme::CDDialogFont);
}

LRESULT CALLBACK wndProcFileDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    WNDPROC wndProcSink = NULL;
    wndProcSink = (WNDPROC)GetProp(hWnd, _T("WNDPROC_SINK"));
    VERIFY(wndProcSink);
    if (WM_CTLCOLOREDIT == uMsg) {
        return (LRESULT)CDarkChildHelper::DarkCtlColorFileDialog((HDC)wParam, CTLCOLOR_EDIT);
    }
    if (!wndProcSink) return 0;
    return ::CallWindowProc(wndProcSink, hWnd, uMsg, wParam, lParam);
}


void CDarkChildHelper::subClassFileDialog(CWnd* wnd, HWND hWnd, bool findSink) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
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
                    CDarkStatic* pObject = new CDarkStatic();
                    pObject->setFileDialogChild(true);
                    allocatedStatics.push_back(pObject);
                    pObject->SubclassWindow(pChild);
                } else if (0 == _tcsicmp(childWindowClass, WC_EDIT)) {
                    CWnd* c = CWnd::FromHandle(pChild);
                    c->UnsubclassWindow();
                    CDarkEdit* pObject = new CDarkEdit();
                    pObject->setFileDialogChild(true);
                    allocatedEdits.push_back(pObject);
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

void CDarkChildHelper::enableFileDialogHook() {
    CMainFrame* pMainFrame = AfxGetMainFrame();
    pMainFrame->enableFileDialogHook(this);
}

HBRUSH CDarkChildHelper::DarkCtlColorFileDialog(HDC hDC, UINT nCtlColor) {
    if (CTLCOLOR_EDIT == nCtlColor) {
        ::SetTextColor(hDC, CDarkTheme::W10DarkThemeFileDialogInjectedTextColor);
        ::SetBkColor(hDC, CDarkTheme::W10DarkThemeFileDialogInjectedBGColor);
        return W10DarkThemeFileDialogInjectedBGBrush;
    } else if (CTLCOLOR_STATIC == nCtlColor) {
        ::SetTextColor(hDC, CDarkTheme::W10DarkThemeFileDialogInjectedTextColor);
        ::SetBkColor(hDC, CDarkTheme::W10DarkThemeFileDialogInjectedBGColor);
        return W10DarkThemeFileDialogInjectedBGBrush;
    } else {
        return NULL;
    }
}

HBRUSH CDarkChildHelper::DarkCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        LRESULT lResult;
        if (pWnd->SendChildNotifyLastMsg(&lResult)) {
            return (HBRUSH)lResult;
        }
        if (CTLCOLOR_LISTBOX == nCtlColor) {
            pDC->SetTextColor(CDarkTheme::TextFGColor);
            pDC->SetBkColor(CDarkTheme::ContentBGColor);
            return darkContentBrush;
        } else {
            pDC->SetTextColor(CDarkTheme::TextFGColor);
            pDC->SetBkColor(CDarkTheme::WindowBGColor);
            return darkWindowBrush;
        }
    }
    return nullptr;
}
