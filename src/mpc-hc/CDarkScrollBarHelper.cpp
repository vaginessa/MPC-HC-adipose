#include "stdafx.h"
#include "CDarkScrollBarHelper.h"
#include "CDarkTheme.h"

CDarkScrollBarHelper::CDarkScrollBarHelper(CWnd* scrollWindow) {
    window = scrollWindow;
}


CDarkScrollBarHelper::~CDarkScrollBarHelper() {
}

void CDarkScrollBarHelper::createSB() {
    pParent = window->GetParent();
    hasVSB = 0 != (window->GetStyle() & WS_VSCROLL);
    hasHSB = 0 != (window->GetStyle() & WS_HSCROLL);
    if (nullptr != pParent && IsWindow(pParent->m_hWnd)) {
        if (hasVSB && !IsWindow(darkVSB.m_hWnd)) {
            VERIFY(darkVSB.Create(SBS_VERT | WS_CHILD |
                WS_VISIBLE, CRect(0, 0, 0, 0), pParent, 0));
            darkVSB.setScrollWindow(window); //we want messages from this SB
        }

        if (hasHSB && !IsWindow(darkHSB.m_hWnd)) {
            VERIFY(darkHSB.Create(SBS_HORZ | WS_CHILD |
                WS_VISIBLE, CRect(0, 0, 0, 0), pParent, 0));
            darkHSB.setScrollWindow(window); //we want messages from this SB
        }
    }
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
        //system metrics doesn't consider other border sizes--client-window works better in all cases so far
        int borderWidth = cr.left - wr.left; //GetSystemMetrics(SM_CXSIZEFRAME) + 1;
        int sbThickness = GetSystemMetrics(SM_CXVSCROLL);
        CRect realWR = wr;

        if (IsWindow(darkVSB.m_hWnd)) {
            if (hasVSB) {
                int width = sbThickness, height = realWR.bottom - realWR.top - 2 * borderWidth - (hasHSB ? sbThickness : 0);
                wr.right -= sbThickness + borderWidth; //clip whole SB plus border

                darkVSB.MoveWindow(wrOnParent.right - width - borderWidth, wrOnParent.top + borderWidth, width, height);
                darkVSB.ShowWindow(SW_SHOW);
                updateDarkScrollInfo();
            } else {
                darkVSB.ShowWindow(SW_HIDE);
            }
        }

        if (IsWindow(darkHSB.m_hWnd)) {
            if (hasHSB) {
                int height = sbThickness, width = realWR.right - realWR.left - 2 * borderWidth - (hasVSB ? sbThickness : 0);
                wr.bottom -= sbThickness + borderWidth; //clip whole SB plus border

                darkHSB.MoveWindow(wrOnParent.left + borderWidth, wrOnParent.bottom - height - borderWidth, width, height);
                darkHSB.ShowWindow(SW_SHOW);
                updateDarkScrollInfo();
            } else {
                darkHSB.ShowWindow(SW_HIDE);
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
    if (IsWindow(darkVSB.m_hWnd)) {
        darkVSB.updateScrollInfo();
    }
    if (IsWindow(darkHSB.m_hWnd)) {
        darkHSB.updateScrollInfo();
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
            //adipose: this code is needed to prevent listctrl glitchy drawing.
            //scroll sends a cascade of redraws which are untenable during a thumb drag
            //only one redraw per scroll call this way
            if (nullptr != pParent && IsWindow(pParent->m_hWnd)) {
                pParent->SetRedraw(FALSE);
                list->Scroll(size);
                pParent->SetRedraw();
                list->Invalidate();
            }
            return true; //processed
        }
    }
    return false;
}

void CDarkScrollBarHelper::darkNcPaintWithSB() {
    createSB();
    if (IsWindow(darkVSB.m_hWnd) || IsWindow(darkHSB.m_hWnd)) {
        CRect wr, cr;
        CWindowDC dc(window);
        setDarkDrawingArea(cr, wr, false); //temporarily allow full clipping window
        dc.ExcludeClipRect(&cr);
    }

    doNcPaint(window);

    hideSB(); //set back scrollbar clipping window
}

void CDarkScrollBarHelper::darkNcPaint(CWnd *window, CDarkScrollable *swindow) {
    if (window->GetStyle() & WS_HSCROLL) {
        SCROLLBARINFO sbHorz = { sizeof(SCROLLBARINFO) };
        if (window->GetScrollBarInfo(OBJID_HSCROLL, &sbHorz)) {
            if (0 == (sbHorz.rgstate[0] & (STATE_SYSTEM_INVISIBLE | STATE_SYSTEM_UNAVAILABLE))) {
                swindow->doDefault(); //required to get the horz sb buttons to draw
            }
        }
    }

    doNcPaint(window);
    if (window->GetStyle() & WS_VSCROLL) {
        window->SetScrollPos(SB_VERT, window->GetScrollPos(SB_VERT), TRUE);
    }
}

void CDarkScrollBarHelper::doNcPaint(CWnd * window) {
    CWindowDC dc(window);
    int oldDC = dc.SaveDC();

    CRect wr, cr, clip, corner;
    window->GetWindowRect(wr);
    window->ScreenToClient(wr);

    window->GetClientRect(&cr);
    int borderThickness = cr.left - wr.left;
    wr.OffsetRect(-wr.left, -wr.top);
    clip = wr; //client rect is insufficient to clip scrollbars
    clip.DeflateRect(borderThickness, borderThickness);
    dc.ExcludeClipRect(clip);
    CBrush brush(CDarkTheme::WindowBorderColorLight); //color used for column sep in explorer
    dc.FillSolidRect(wr, CDarkTheme::ContentBGColor);
    dc.FrameRect(wr, &brush);

    dc.RestoreDC(oldDC);
    if ((window->GetStyle() & (WS_VSCROLL | WS_HSCROLL)) == (WS_VSCROLL | WS_HSCROLL)) {
        int sbThickness = GetSystemMetrics(SM_CXVSCROLL);
        corner = { wr.right - sbThickness - borderThickness, wr.bottom - sbThickness - borderThickness,  wr.right-borderThickness, wr.bottom-borderThickness};
        dc.FillSolidRect(corner, CDarkTheme::ContentBGColor);
    }
}

