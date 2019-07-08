#include "stdafx.h"
#include "CDarkEdit.h"
#include "CDarkTheme.h"

CDarkEdit::CDarkEdit() {
    buddy = nullptr;
    darkSBHelper = nullptr;
    if (!CDarkTheme::canUseWin10DarkTheme()) {
        darkSBHelper = DEBUG_NEW CDarkScrollBarHelper(this);
    }
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
        ModifyStyleEx(WS_BORDER, WS_EX_STATICEDGE, 0);
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
        if (nullptr != darkSBHelper) {
            darkSBHelper->darkNcPaintWithSB();
        } else {
            CDarkScrollBarHelper::darkNcPaint(this, this);
        }

        CDC* pDC = GetWindowDC();

        CRect rect;
        GetWindowRect(&rect);
        rect.OffsetRect(-rect.left, -rect.top);

        CBrush brush(CDarkTheme::EditBorderColor);

        pDC->FrameRect(&rect, &brush);
        if (nullptr != buddy) buddy->Invalidate();
        ReleaseDC(pDC);
    } else {
        __super::OnNcPaint();
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
