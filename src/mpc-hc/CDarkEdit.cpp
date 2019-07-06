#include "stdafx.h"
#include "CDarkEdit.h"
#include "CDarkTheme.h"

CDarkEdit::CDarkEdit() {
    buddy = nullptr;
}


CDarkEdit::~CDarkEdit() {
}

IMPLEMENT_DYNAMIC(CDarkEdit, CEdit)
BEGIN_MESSAGE_MAP(CDarkEdit, CEdit)
    ON_WM_NCPAINT()
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

