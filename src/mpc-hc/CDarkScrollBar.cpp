#include "stdafx.h"
#include "CDarkScrollBar.h"
#include "CDarkTheme.h"


IMPLEMENT_DYNAMIC(CDarkScrollBar, CXeScrollBarBase)

BEGIN_MESSAGE_MAP(CDarkScrollBar, CXeScrollBarBase)
END_MESSAGE_MAP()

CDarkScrollBar::CDarkScrollBar() {
}


CDarkScrollBar::~CDarkScrollBar() {
}

void CDarkScrollBar::DrawScrollBar(CDC* pDC) {
    CRect rcC;
    GetClientRect(&rcC);

    // Draw to memory DC
    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);
    CBitmap bmMem;
    bmMem.CreateCompatibleBitmap(pDC, rcC.Width(), rcC.Height());
    CBitmap *pOldBm = dcMem.SelectObject(&bmMem);


    CBrush brushBG(CDarkTheme::ScrollBGColor);
    dcMem.FillRect(rcC, &brushBG);

    CBrush brushChannel(CDarkTheme::ScrollBGColor);

    CBrush brushRed(CDarkTheme::DebugColorRed);
    CBrush brushYellow(CDarkTheme::DebugColorYellow);
    CBrush brushGreen(CDarkTheme::DebugColorGreen);

    XSB_EDRAWELEM eState;
    const CRect *prcElem = 0;
    stXSB_AREA stArea;

    for (int nElem = eTLbutton; nElem <= eThumb; nElem++) {
        stArea.eArea = (eXSB_AREA)nElem;

        prcElem = GetUIelementDrawState(stArea.eArea, eState);
        if (!prcElem || eState == eNotDrawn)	// Rect empty or area not drawn?
            continue;

        CRect butRect = prcElem;
        if (m_bHorizontal) {
            butRect.top += 1;
            butRect.bottom -= 1;
        } else {
            butRect.left += 1;
            butRect.right -= 1;
        }


        if (stArea.IsButton()) {
            CBrush brushButton;
            COLORREF buttonClr=RGB(0,0,0);
            switch (eState) {
            case eDisabled:
                //no example found of disabled dark scrollbar, but when disabled, button bg = scroll bg
                //(see notepad for example of disabled non-dark--bg color matches disabled button)
                buttonClr = CDarkTheme::ScrollBGColor;
                break;
            case eNormal:
                buttonClr = CDarkTheme::ScrollBGColor;
                break;
            case eDown:
                buttonClr = CDarkTheme::ScrollButtonClickColor;
                break;
            case eHot:
                buttonClr = CDarkTheme::ScrollButtonHoverColor;
                break;
            default:
                ASSERT(FALSE);	// Unknown state!
            }
            brushButton.CreateSolidBrush(buttonClr);

            dcMem.FillRect(butRect, &brushButton);
            CBitmap arrowBMP;
            CDC dcArrowBMP;
            dcArrowBMP.CreateCompatibleDC(pDC);

            COLORREF tT, tB;
            tT = dcMem.SetTextColor(buttonClr);
            tB = dcMem.SetBkColor(CDarkTheme::ScrollButtonArrowColor);

            int arrowLeft, arrowTop, arrowWidth, arrowHeight;
            if (m_bHorizontal) {
            } else {
                arrowWidth = CDarkTheme::scrollArrowLong;
                arrowHeight = CDarkTheme::scrollArrowShort;
                arrowBMP.CreateBitmap(arrowWidth, arrowHeight, 1, 1, CDarkTheme::ScrollArrowBitsV);
                arrowLeft = butRect.left + (butRect.Width() - arrowWidth + 1) / 2; //add 1 to force rounding up when odd
                arrowTop = butRect.top + (butRect.Height() - arrowHeight + 1) / 2; //add 1 to force rounding up when odd -- explorer has 6px on top and 5px on bottom
                dcArrowBMP.SelectObject(&arrowBMP);
                if (nElem == eTLbutton) { //top or left
                    dcMem.BitBlt(arrowLeft, arrowTop, arrowWidth, arrowHeight, &dcArrowBMP, 0, 0, SRCCOPY);
                } else {
                    dcMem.StretchBlt(arrowLeft, arrowTop, arrowWidth, arrowHeight, &dcArrowBMP, 0, arrowHeight-1, arrowWidth, -arrowHeight, SRCCOPY);
                }
            }

            dcMem.SetTextColor(tT);
            dcMem.SetBkColor(tB);

        } else if (stArea.IsChannel()) {
            if (m_bHorizontal) {
                dcMem.FillRect(prcElem, &brushChannel);
            } else {
                dcMem.FillRect(prcElem, &brushChannel);
            }
        } else {	// Is thumb
            CBrush brushThumb;
            switch (eState) {
            case eDisabled:
                //no example found of disabled dark scrollbar, but when disabled, we will hide the thumb entirely. put bg color here for now
                brushThumb.CreateSolidBrush(CDarkTheme::ScrollBGColor);
                break;
            case eNormal:
                brushThumb.CreateSolidBrush(CDarkTheme::ScrollThumbColor);
                break;
            case eDown:
                brushThumb.CreateSolidBrush(CDarkTheme::ScrollThumbDragColor);
                break;
            case eHot:
                brushThumb.CreateSolidBrush(CDarkTheme::ScrollThumbHoverColor);
                break;
            default:
                ASSERT(FALSE);	// Unknown state!
            }
            dcMem.FillRect(butRect, &brushThumb);
        }
    }

    pDC->BitBlt(0, 0, rcC.Width(), rcC.Height(), &dcMem, 0, 0, SRCCOPY);

    dcMem.SelectObject(pOldBm);
}

void CDarkScrollBar::SendScrollMsg(WORD wSBcode, WORD wHiWPARAM /*= 0*/) {
    ASSERT(::IsWindow(m_hWnd));
    if (m_scrollWindow && ::IsWindow(m_scrollWindow->m_hWnd)) {
        m_scrollWindow->SendMessage((m_bHorizontal) ? WM_HSCROLL : WM_VSCROLL,
            MAKELONG(wSBcode, wHiWPARAM), (LPARAM)m_hWnd);
    } else if (m_pParent && ::IsWindow(m_pParent->m_hWnd)) {
        m_pParent->SendMessage((m_bHorizontal) ? WM_HSCROLL : WM_VSCROLL,
            MAKELONG(wSBcode, wHiWPARAM), (LPARAM)m_hWnd);
    }
}

void CDarkScrollBar::updateScrollInfo() {
    if (GetStyle()&WS_VISIBLE) {
        SCROLLINFO si = { 0 }, siSelf = { 0 };
        si.cbSize = sizeof(SCROLLINFO);
        si.fMask = SIF_ALL;
        m_scrollWindow->GetScrollInfo(m_bHorizontal ? SB_HORZ : SB_VERT, &si);
        siSelf.cbSize = sizeof(SCROLLINFO);
        siSelf.fMask = SIF_ALL;
        if (si.nMax != siSelf.nMax || si.nMin != siSelf.nMin || si.nPos != siSelf.nPos || si.nPage != siSelf.nPage) {
            SetScrollInfo(&si);
        }
    }
}
