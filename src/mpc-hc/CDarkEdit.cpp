#include "stdafx.h"
#include "CDarkEdit.h"
#include "CDarkTheme.h"
#include "CDarkChildHelper.h"

CDarkEdit::CDarkEdit() {
    buddy = nullptr;
    darkSBHelper = nullptr;
    isFileDialogChild = false;
//horizontal scrollbar broken for CEdit, we must theme ourselves
//    if (!CDarkTheme::canUseWin10DarkTheme()) {
        darkSBHelper = DEBUG_NEW CDarkScrollBarHelper(this);
//    }
}


CDarkEdit::~CDarkEdit() {
    if (nullptr != darkSBHelper) {
        delete darkSBHelper;
    }
}

IMPLEMENT_DYNAMIC(CDarkEdit, CEdit)
BEGIN_MESSAGE_MAP(CDarkEdit, CEdit)
    ON_WM_NCPAINT()
    ON_WM_MOUSEWHEEL()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
END_MESSAGE_MAP()


void CDarkEdit::PreSubclassWindow() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        ModifyStyleEx(WS_EX_CLIENTEDGE, WS_EX_STATICEDGE, SWP_FRAMECHANGED);
        CRect r;
        GetClientRect(r);
        r.DeflateRect(2, 2); //some default padding for those spaceless fonts
        SetRect(r);
        if (CDarkTheme::canUseWin10DarkTheme()) {
            SetWindowTheme(GetSafeHwnd(), L"DarkMode_Explorer", NULL);
        } else {
            SetWindowTheme(GetSafeHwnd(), L"", NULL);
        }
    } else {
        __super::PreSubclassWindow();
    }
}

void CDarkEdit::OnNcPaint() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (0 != (GetStyle() & (WS_VSCROLL | WS_HSCROLL) )) { //scrollable edit will be treated like a window, not a field
            if (nullptr != darkSBHelper) {
                darkSBHelper->darkNcPaintWithSB();
            } else {
                CDarkScrollBarHelper::darkNcPaint(this, this);
            }
        } else {
            CWindowDC dc(this);

            CRect rect;
            GetWindowRect(&rect);
            rect.OffsetRect(-rect.left, -rect.top);

            CBrush brush;
            if (isFileDialogChild) {//special case for edits injected to file dialog
                brush.CreateSolidBrush(CDarkTheme::W10DarkThemeFileDialogInjectedEditBorderColor);
            } else {
                brush.CreateSolidBrush(CDarkTheme::EditBorderColor);
            }

            dc.FrameRect(&rect, &brush);
            if (nullptr != buddy) buddy->Invalidate();
        }

    } else {
        __super::OnNcPaint();
    }
}

void CDarkEdit::SetFixedWidthFont(CFont& f) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        CWindowDC dc(this);
        CDarkTheme::getFontByType(font, &dc, CDarkTheme::CDFixedFont);
        SetFont(&font);
    } else {
        SetFont(&f);
    }
}

BOOL CDarkEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    __super::OnMouseWheel(nFlags, zDelta, pt);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
    ScreenToClient(&pt);
    return TRUE;
}

void CDarkEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    __super::OnVScroll(nSBCode, nPos, pScrollBar);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}

void CDarkEdit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    __super::OnHScroll(nSBCode, nPos, pScrollBar);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    } 
}
