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
    ModifyStyleEx(WS_BORDER, WS_EX_STATICEDGE, 0);
}

void CDarkEdit::OnNcPaint() {
    CDC* pDC = GetWindowDC();

    CRect rect;
    GetWindowRect(&rect);
    rect.OffsetRect(-rect.left, -rect.top);

    CBrush brush(CDarkTheme::EditBorderColor);
    if (nullptr != buddy) { //a bit sloppy, but the nc area is not being clipped by the buddy spin ctrls, so manually exclude it here
        CRect buddyRect;
        buddy->GetWindowRect(buddyRect);
        pDC->IntersectClipRect(buddyRect);
    }

    pDC->FrameRect(&rect, &brush);
    ReleaseDC(pDC);
}
