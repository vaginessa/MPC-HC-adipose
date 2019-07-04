#include "stdafx.h"
#include "CDarkListBox.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

IMPLEMENT_DYNAMIC(CDarkListBox, CListBox)

CDarkListBox::CDarkListBox() {
    darkTTcid = (UINT_PTR)-1;
}


CDarkListBox::~CDarkListBox() {
}

BEGIN_MESSAGE_MAP(CDarkListBox, CListBox)
    ON_WM_NCPAINT()
    ON_WM_MOUSEWHEEL()
    ON_WM_TIMER()
    ON_WM_VSCROLL()
    ON_CONTROL_REFLECT(LBN_SELCHANGE, &CDarkListBox::OnLbnSelchange)
    ON_WM_MOUSEMOVE()
    ON_WM_SIZE()
END_MESSAGE_MAP()


void CDarkListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
    CDC dc;

    dc.Attach(lpDrawItemStruct->hDC);

    COLORREF crOldTextColor = dc.GetTextColor();
    COLORREF crOldBkColor = dc.GetBkColor();

    if ((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED)) {
        dc.SetTextColor(CDarkTheme::TextFGColor);
        dc.SetBkColor(CDarkTheme::ContentSelectedColor);
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, CDarkTheme::ContentSelectedColor);
    } else {
        dc.SetTextColor(CDarkTheme::TextFGColor);
        dc.SetBkColor(CDarkTheme::ContentBGColor);
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, CDarkTheme::ContentBGColor);
    }

    lpDrawItemStruct->rcItem.left += 3;

    CString strText;
    GetText(lpDrawItemStruct->itemID, strText);

    CFont font;
    CDarkTheme::getFontByType(font, &dc, CDarkTheme::CDDialogFont);
    CFont* pOldFont = dc.SelectObject(&font);
    dc.DrawText(strText, strText.GetLength(), &lpDrawItemStruct->rcItem, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);
    dc.SelectObject(pOldFont);

    dc.Detach();
}


void CDarkListBox::OnNcPaint() {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
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


void CDarkListBox::setDarkDrawingArea(CRect &cr, CRect &wr, bool clipping) {
    GetClientRect(&cr);
    ClientToScreen(&cr);
    GetWindowRect(&wr);

    CRect pwr;
    GetParent()->GetWindowRect(&pwr);
    LONG sbTop = wr.top - pwr.top;
    LONG sbRight = wr.right - pwr.left;

    int nWidth = cr.Width(); //this will be about where the scrollbar starts

    cr.OffsetRect(-wr.left, -wr.top);
    wr.OffsetRect(-wr.left, -wr.top);


    if (clipping) {
        int width = GetSystemMetrics(SM_CXVSCROLL);
        int border = GetSystemMetrics(SM_CXEDGE);
        wr.right = wr.left + nWidth - border;

        if (GetStyle()&WS_VSCROLL) {
            darkVSB.MoveWindow(sbRight - width - border, sbTop + border, width, wr.Height() - 2 * border);
            darkVSB.ShowWindow(SW_SHOW);
            updateDarkScrollInfo();
        } else {
            darkVSB.ShowWindow(SW_HIDE);
        }

    }

    HRGN iehrgn = CreateRectRgn(wr.left, wr.top, wr.right, wr.bottom);
    SetWindowRgn(iehrgn, false);
}

void CDarkListBox::hideSB() {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        CRect wr, cr;
        setDarkDrawingArea(cr, wr, true);
    }
}

void CDarkListBox::updateDarkScrollInfo() {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        darkVSB.updateScrollInfo();
    }
}

BOOL CDarkListBox::PreTranslateMessage(MSG* pMsg) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        darkTT.RelayEvent(pMsg);
    }
    return CListBox::PreTranslateMessage(pMsg);
}

void CDarkListBox::PreSubclassWindow() {
    CListBox::PreSubclassWindow();
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        if (CWnd* pParent = GetParent()) {
            VERIFY(darkVSB.Create(SBS_VERT | WS_CHILD |
                WS_VISIBLE, CRect(0, 0, 0, 0), pParent, 0));
            darkVSB.setScrollWindow(this); //we want messages from this SB
        }
        darkTT.Create(this, TTS_ALWAYSTIP);
        darkTT.enableFlickerHelper();
        setIntegralHeight();
    }
}


BOOL CDarkListBox::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    CListBox::OnMouseWheel(nFlags, zDelta, pt);
    updateDarkScrollInfo();
    ScreenToClient(&pt);
    updateToolTip(pt);
    return TRUE;
}

void CDarkListBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
    updateDarkScrollInfo();
}

void CDarkListBox::OnLbnSelchange() {
    updateDarkScrollInfo();
}


void CDarkListBox::updateToolTip(CPoint point) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        TOOLINFO ti = { 0 };
        UINT_PTR tid = OnToolHitTest(point, &ti);
        //OnToolHitTest returns -1 on failure but doesn't update uId to match
        if (tid != -1 && darkTTcid != ti.uId && 0 != ti.uId) {
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


void CDarkListBox::OnMouseMove(UINT nFlags, CPoint point) {
    updateToolTip(point);
}

void CDarkListBox::setIntegralHeight() {
    CWindowDC dc(this);
    CFont font;
    CDarkTheme::getFontByType(font, &dc, CDarkTheme::CDDialogFont);
    CFont* pOldFont = dc.SelectObject(&font);
    CRect r(0, 0, 99, 99);
    CString test = _T("W");
    dc.DrawText(test, test.GetLength(), &r, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
    SetItemHeight(0, r.Height());

    dc.SelectObject(pOldFont);
}

void CDarkListBox::OnSize(UINT nType, int cx, int cy) {
    CListBox::OnSize(nType, cx, cy);
}
