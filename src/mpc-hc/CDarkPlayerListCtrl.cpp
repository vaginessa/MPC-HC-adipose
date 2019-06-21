#include "stdafx.h"
#include "CDarkPlayerListCtrl.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

CDarkPlayerListCtrl::CDarkPlayerListCtrl(int tStartEditingDelay) : CPlayerListCtrl(tStartEditingDelay) {
    darkSBHelper = nullptr;
    if (!CDarkTheme::canUseWin10DarkTheme()) {
        darkSBHelper = DEBUG_NEW CDarkScrollBarHelper(this);
    }
}


CDarkPlayerListCtrl::~CDarkPlayerListCtrl() {
    if (nullptr != darkSBHelper) {
        delete darkSBHelper;
    }
}

void CDarkPlayerListCtrl::PreSubclassWindow() {
    if (!AfxGetAppSettings().bDarkThemeLoaded) {
        EnableToolTips(TRUE);
    } else {
        if (CDarkTheme::canUseWin10DarkTheme()) {
            SetWindowTheme(GetSafeHwnd(), L"DarkMode_Explorer", NULL);
        } else {
            SetWindowTheme(GetSafeHwnd(), L"", NULL);
        }
    }
    CPlayerListCtrl::PreSubclassWindow();
}

IMPLEMENT_DYNAMIC(CDarkPlayerListCtrl, CPlayerListCtrl)

BEGIN_MESSAGE_MAP(CDarkPlayerListCtrl, CPlayerListCtrl)
    ON_WM_NCPAINT()
    ON_WM_CREATE()
    ON_NOTIFY_REFLECT(LVN_ENDSCROLL, &CDarkPlayerListCtrl::OnLvnEndScroll)
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL()
    ON_WM_NCCALCSIZE()
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CDarkPlayerListCtrl::PreTranslateMessage(MSG * pMsg) {
    if (IsWindow(darkTT.m_hWnd)) {
        darkTT.RelayEvent(pMsg);
    }
    return __super::PreTranslateMessage(pMsg);
}

void CDarkPlayerListCtrl::OnNcPaint() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (nullptr != darkSBHelper) {
            darkSBHelper->darkNcPaintWithSB();
        } else {
            CDarkScrollBarHelper::darkNcPaint(this, this);
        }
    } else {
        __super::OnNcPaint();
    }
}

int CDarkPlayerListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (__super::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (AfxGetAppSettings().bDarkThemeLoaded) {
        SetBkColor(CDarkTheme::ContentBGColor);

        darkTT.Create(this, TTS_ALWAYSTIP);
        darkTT.enableFlickerHelper();
    }

    return 0;
}

void CDarkPlayerListCtrl::OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult) {
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
    *pResult = 0;
}

void CDarkPlayerListCtrl::updateSB() {
    if (nullptr != darkSBHelper) {
        darkSBHelper->hideSB();
    }
}

void CDarkPlayerListCtrl::updateDarkScrollInfo() {
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}

LRESULT CDarkPlayerListCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
    if (AfxGetAppSettings().bDarkThemeLoaded && nullptr != darkSBHelper) {
        if (darkSBHelper->WindowProc(this, message, wParam, lParam)) {
            return 1;
        }
    }
    return __super::WindowProc(message, wParam, lParam);
}

void CDarkPlayerListCtrl::updateToolTip(CPoint point) {
    if (AfxGetAppSettings().bDarkThemeLoaded && nullptr != darkTT) {
        TOOLINFO ti = { 0 };
        UINT_PTR tid = OnToolHitTest(point, &ti);
        //OnToolHitTest returns -1 on failure but doesn't update uId to match
        if (tid != -1 && darkTTcid != ti.uId) {
            if (darkTT.GetToolCount() > 0) {
                darkTT.DelTool(this);
                darkTT.Activate(FALSE);
            }

            darkTTcid = ti.uId;

            CRect cr;
            GetClientRect(&cr); //we reset the tooltip every time we move anyway, so this rect is adequate

            darkTT.AddTool(this, LPSTR_TEXTCALLBACK, &cr, ti.uId);
            darkTT.Activate(TRUE);
        }
    }
}

void CDarkPlayerListCtrl::OnMouseMove(UINT nFlags, CPoint point) {
    __super::OnMouseMove(nFlags, point);
    updateToolTip(point);
}


BOOL CDarkPlayerListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    BOOL ret = __super::OnMouseWheel(nFlags, zDelta, pt);
    ScreenToClient(&pt);
    updateToolTip(pt);
    return ret;
}


void CDarkPlayerListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp) {
    __super::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CDarkPlayerListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) {
    NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

    *pResult = CDRF_DODEFAULT;
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT) {
            *pResult = CDRF_NOTIFYITEMDRAW;
        } else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT) {
            *pResult = CDRF_NOTIFYSUBITEMDRAW;
        } else if (pLVCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM)) {
            int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);
            if (IsItemVisible(nItem)) {
                int nSubItem = pLVCD->iSubItem;

                COLORREF textColor = CDarkTheme::TextFGColor;
                COLORREF bgColor = CDarkTheme::ContentBGColor;

                CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
                COLORREF oldTextColor = pDC->GetTextColor();
                COLORREF oldBkColor = pDC->GetBkColor();

                CRect rect, rIcon, rText;
                GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
                GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rText);
                GetSubItemRect(nItem, nSubItem, LVIR_ICON, rIcon);

                CString text = GetItemText(nItem, nSubItem);
                pDC->SetTextColor(textColor);
                pDC->SetBkColor(bgColor);
                //            pDC->FillSolidRect(rText, bgColor);

                HDITEM hditem = { 0 };
                hditem.mask = HDI_FORMAT;
                GetHeaderCtrl()->GetItem(nSubItem, &hditem);
                int align = hditem.fmt & HDF_JUSTIFYMASK;
                UINT textFormat = DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
                if (align == HDF_CENTER)
                    textFormat |= DT_CENTER;
                else if (align == HDF_LEFT) {
                    textFormat |= DT_LEFT;
                    rText.left += 6;
                } else {
                    textFormat |= DT_RIGHT;
                    rText.right -= 6;
                }


                if (nSubItem == 0 && 0 != (GetStyle() & LVS_EX_CHECKBOXES)) {
                    LVITEM lvi = { 0 };
                    lvi.iItem = nItem;
                    lvi.iSubItem = 0;
                    lvi.mask = LVIF_IMAGE;
                    GetItem(&lvi);

                    rIcon.DeflateRect(0, 0, 1, 0);
                    rIcon.DeflateRect(0, (rIcon.Height() - rIcon.Width()) / 2); //as tall as wide

                    //following is a bit of a hack.  mpc-hc often sets the "check" state by changing the image index only (not setcheck), so we will use that to control whether "checked" or not
                    //better solution might be to load different check images based on theme
                    CDarkTheme::drawCheckBox(lvi.iImage == BST_CHECKED, false, false, rIcon, pDC);

                    if (align == HDF_LEFT)
                        rText.left -= 2; //needs less indent when checkboxing
                } else {
                }
                CDarkTheme::DrawBufferedText(pDC, text, rText, textFormat);
                //pDC->DrawText(text, rText, textFormat);
                pDC->SetTextColor(oldTextColor);
                pDC->SetBkColor(oldBkColor);
            }
            *pResult = CDRF_SKIPDEFAULT;
        }
    }
}


BOOL CDarkPlayerListCtrl::OnEraseBkgnd(CDC* pDC) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        CRect r;
        GetClientRect(r);
        pDC->FillSolidRect(r, CDarkTheme::ContentBGColor);
    } else {
        return __super::OnEraseBkgnd(pDC);
    }
    return TRUE;
}


HBRUSH CDarkPlayerListCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    HBRUSH ret;
    ret = DarkCtlColor(pDC, pWnd, nCtlColor);
    if (nullptr != ret) {
        return ret;
    } else {
        return __super::OnCtlColor(pDC, pWnd, nCtlColor);
    }
}
