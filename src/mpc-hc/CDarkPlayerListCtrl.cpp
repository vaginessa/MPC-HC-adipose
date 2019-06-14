#include "stdafx.h"
#include "CDarkPlayerListCtrl.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

CDarkPlayerListCtrl::CDarkPlayerListCtrl(int tStartEditingDelay) : CPlayerListCtrl(tStartEditingDelay) {
}


CDarkPlayerListCtrl::~CDarkPlayerListCtrl() {
}

void CDarkPlayerListCtrl::PreSubclassWindow() {
    if (!AfxGetAppSettings().bDarkThemeLoaded) {
        EnableToolTips(TRUE);
    }
    CPlayerListCtrl::PreSubclassWindow();
}


IMPLEMENT_DYNAMIC(CDarkPlayerListCtrl, CPlayerListCtrl)

BEGIN_MESSAGE_MAP(CDarkPlayerListCtrl, CListCtrl)
    ON_WM_NCPAINT()
    ON_WM_NCCALCSIZE()
    ON_WM_CREATE()
    ON_NOTIFY_REFLECT(LVN_ENDSCROLL, &CDarkPlayerListCtrl::OnLvnEndScroll)
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


BOOL CDarkPlayerListCtrl::PreTranslateMessage(MSG * pMsg) {
    if (IsWindow(darkTT.m_hWnd)) {
        darkTT.RelayEvent(pMsg);
    }
    return CListCtrl::PreTranslateMessage(pMsg);
}


void CDarkPlayerListCtrl::OnNcPaint() {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded && nullptr != darkVSB) {
        CRect wr, cr;

        CWindowDC dc(this);
        setDarkDrawingArea(cr, wr, false); //temporarily allow full clipping window
        dc.ExcludeClipRect(&cr);
        CBrush brush(CDarkTheme::WindowBorderColorLight); //color used for column sep in explorer
        dc.FillSolidRect(wr, CDarkTheme::ContentBGColor);

        dc.FrameRect(wr, &brush);
        hideSB(); //set back scrollbar clipping window
    } else {
        __super::OnNcPaint();
    }
}


void CDarkPlayerListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp) {
    //    ModifyStyle(WS_HSCROLL | WS_VSCROLL, 0);

    CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CDarkPlayerListCtrl::setDarkDrawingArea(CRect &cr, CRect &wr, bool clipping) {
    GetClientRect(&cr);
    ClientToScreen(&cr);
    GetWindowRect(&wr);

    CRect rect;
    CHeaderCtrl* pHdr = GetHeaderCtrl();
    pHdr->GetWindowRect(rect);
    int nWidth = rect.Width(); //this will be about where the scrollbar starts
    cr.OffsetRect(-wr.left, -wr.top);
    wr.OffsetRect(-wr.left, -wr.top);

    if (clipping) {
        LONG sbRight = wr.right;
        int width = GetSystemMetrics(SM_CXVSCROLL);
        wr.right -= width + 5;
        //        wr.right = wr.left + nWidth - 1; //1 pixel bleed of scrollbar, list items must be drawn 1 pix short?
        if (nullptr != darkVSB) {
            if (GetStyle()&WS_VSCROLL) {
                darkVSB.MoveWindow(sbRight - width - 1, cr.top + 1, width, cr.bottom - cr.top + 2);
                darkVSB.ShowWindow(SW_SHOW);
                updateDarkScrollInfo();
            } else {
                darkVSB.ShowWindow(SW_HIDE);
            }
        }
    }

    HRGN iehrgn = CreateRectRgn(wr.left, wr.top, wr.right, wr.bottom);
    SetWindowRgn(iehrgn, false);
}

void CDarkPlayerListCtrl::hideSB() {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        CRect wr, cr;
        setDarkDrawingArea(cr, wr, true);
    }
}


int CDarkPlayerListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CListCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        CWnd* pParent = GetParent();
        if (nullptr != pParent) {
            VERIFY(darkVSB.Create(SBS_VERT | WS_CHILD |
                WS_VISIBLE, CRect(0, 0, 0, 0), pParent, IDC_DARKVSCROLLBAR));
            darkVSB.setScrollWindow(this); //we want messages from this SB
        }
        SetBkColor(CDarkTheme::ContentBGColor);

        darkTT.Create(this, TTS_ALWAYSTIP);
        darkTT.enableFlickerHelper();
    }

    return 0;
}

void CDarkPlayerListCtrl::updateDarkScrollInfo() {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded && nullptr != darkVSB) {
        darkVSB.updateScrollInfo();
    }
}


void CDarkPlayerListCtrl::OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult) {
    //    LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
    updateDarkScrollInfo();
    *pResult = 0;
}

//clistctrl does not seem to scroll when receiving thumb messages, so we handle them here
//this will allow the darkscrollbar to update as well
//thanks to flyhigh for this solution https://www.codeproject.com/Articles/14724/Replace-a-Window-s-Internal-Scrollbar-with-a-custo 
LRESULT CDarkPlayerListCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        if (message == WM_VSCROLL || message == WM_HSCROLL) {
            WORD sbCode = LOWORD(wParam);
            if (sbCode == SB_THUMBTRACK || sbCode == SB_THUMBPOSITION) {
                SCROLLINFO siv = { 0 };
                siv.cbSize = sizeof(SCROLLINFO);
                siv.fMask = SIF_ALL;
                SCROLLINFO sih = siv;
                int nPos = HIWORD(wParam);
                CRect rcClient;
                GetClientRect(&rcClient);
                GetScrollInfo(SB_VERT, &siv);
                GetScrollInfo(SB_HORZ, &sih);
                SIZE sizeAll;
                if (sih.nPage == 0) {
                    sizeAll.cx = rcClient.right;
                } else {
                    sizeAll.cx = rcClient.right*(sih.nMax + 1) / sih.nPage;
                }
                if (siv.nPage == 0) {
                    sizeAll.cy = rcClient.bottom;
                } else {
                    sizeAll.cy = rcClient.bottom*(siv.nMax + 1) / siv.nPage;
                }

                SIZE size = { 0,0 };
                if (WM_VSCROLL == message) {
                    size.cx = sizeAll.cx*sih.nPos / (sih.nMax + 1);
                    size.cy = sizeAll.cy*(nPos - siv.nPos) / (siv.nMax + 1);
                } else {
                    size.cx = sizeAll.cx*(nPos - sih.nPos) / (sih.nMax + 1);
                    size.cy = sizeAll.cy*siv.nPos / (siv.nMax + 1);
                }
                Scroll(size);
                return 1;
            }
        }
    }
    return CListCtrl::WindowProc(message, wParam, lParam);
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
    CListCtrl::OnMouseMove(nFlags, point);
    updateToolTip(point);
}


BOOL CDarkPlayerListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    BOOL ret = CPlayerListCtrl::OnMouseWheel(nFlags, zDelta, pt);
    ScreenToClient(&pt);
    updateToolTip(pt);
    return ret;
}
