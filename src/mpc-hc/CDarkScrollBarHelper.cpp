#include "stdafx.h"
#include "CDarkScrollBarHelper.h"
#include "CDarkTheme.h"

CDarkScrollBarHelper::CDarkScrollBarHelper(CWnd* scrollWindow) {
    window = scrollWindow;
}


CDarkScrollBarHelper::~CDarkScrollBarHelper() {
}

void CDarkScrollBarHelper::createSB() {
    CWnd* pParent = window->GetParent();
    if (nullptr != pParent && IsWindow(pParent->m_hWnd)) {
        VERIFY(darkVSB.Create(SBS_VERT | WS_CHILD |
            WS_VISIBLE, CRect(0, 0, 0, 0), pParent, 6));
        darkVSB.setScrollWindow(window); //we want messages from this SB
    }
}

void CDarkScrollBarHelper::BeforeNcPaint() {
    if (nullptr == darkVSB) createSB();
    if (nullptr != darkVSB) {
        CRect wr, cr;
        CWindowDC dc(window);
        setDarkDrawingArea(cr, wr, false); //temporarily allow full clipping window
        dc.ExcludeClipRect(&cr);
    }
}

void CDarkScrollBarHelper::AfterNcPaint() {
    hideSB(); //set back scrollbar clipping window
}


void CDarkScrollBarHelper::setDarkDrawingArea(CRect &cr, CRect &wr, bool clipping) {
    window->GetClientRect(&cr);
    window->ClientToScreen(&cr);
    window->GetWindowRect(&wr);

    CWnd* pParent = window->GetParent();
    CRect wrOnParent = wr;
    if (nullptr != pParent) {
        pParent->ScreenToClient(wrOnParent);
    }

    cr.OffsetRect(-wr.left, -wr.top);
    wr.OffsetRect(-wr.left, -wr.top);

    if (clipping) {
        if (nullptr != darkVSB) {
            if (window->GetStyle()&WS_VSCROLL) {
                /*
                LONG sbRight = wr.right;
                CRect rect;
                CHeaderCtrl* pHdr = GetHeaderCtrl();
                pHdr->GetWindowRect(rect);
                int nWidth = rect.Width(); //this will be about where the scrollbar starts
                wr.right = wr.left + nWidth - 1; //1 pixel bleed of scrollbar, list items must be drawn 1 pix short?
                darkVSB.MoveWindow(sbRight - width - 1, cr.top + 2, width, cr.bottom - cr.top);
                */
                const int borderWidth = GetSystemMetrics(SM_CXSIZEFRAME) + 1;
                int width = GetSystemMetrics(SM_CXVSCROLL), height = wr.bottom - wr.top - 2 * borderWidth;
                wr.right -= width + 5; //clip whole SB plus border

                darkVSB.MoveWindow(wrOnParent.right - width - borderWidth, wrOnParent.top + borderWidth, width, height);
                darkVSB.ShowWindow(SW_SHOW);
                updateDarkScrollInfo();
            } else {
                darkVSB.ShowWindow(SW_HIDE);
            }
        }
    }

    HRGN iehrgn = CreateRectRgn(wr.left, wr.top, wr.right, wr.bottom);
    window->SetWindowRgn(iehrgn, false);
}

void CDarkScrollBarHelper::hideSB() {
    CRect wr, cr;
    setDarkDrawingArea(cr, wr, true);
}


void CDarkScrollBarHelper::updateDarkScrollInfo() {
    if (nullptr != darkVSB) {
        darkVSB.updateScrollInfo();
    }
}


//clistctrl does not seem to scroll when receiving thumb messages, so we handle them here
//this will allow the darkscrollbar to update as well
//thanks to flyhigh for this solution https://www.codeproject.com/Articles/14724/Replace-a-Window-s-Internal-Scrollbar-with-a-custo 
bool CDarkScrollBarHelper::WindowProc(CListCtrl *list, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_VSCROLL || message == WM_HSCROLL) {
        WORD sbCode = LOWORD(wParam);
        if (sbCode == SB_THUMBTRACK || sbCode == SB_THUMBPOSITION) {
            SCROLLINFO siv = { 0 };
            siv.cbSize = sizeof(SCROLLINFO);
            siv.fMask = SIF_ALL;
            SCROLLINFO sih = siv;
            int nPos = HIWORD(wParam);
            CRect rcClient;
            list->GetClientRect(&rcClient);
            list->GetScrollInfo(SB_VERT, &siv);
            list->GetScrollInfo(SB_HORZ, &sih);
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
            list->Scroll(size);
            return true; //processed
        }
    }
    return false;
}

