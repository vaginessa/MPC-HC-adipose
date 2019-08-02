#include "stdafx.h"
#include "CMPCThemePropPageFrame.h"
#include "CMPCTheme.h"
#include "CMPCThemeUtil.h"
#include "TreePropSheet/PropPageFrameDefault.h"

CMPCThemePropPageFrame::CMPCThemePropPageFrame() : CPropPageFrameDefault() {
}


CMPCThemePropPageFrame::~CMPCThemePropPageFrame() {
}

BEGIN_MESSAGE_MAP(CMPCThemePropPageFrame, CPropPageFrameDefault)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CMPCThemePropPageFrame::Create(DWORD dwWindowStyle, const RECT & rect, CWnd * pwndParent, UINT nID) {
    return CWnd::Create(
        AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, AfxGetApp()->LoadStandardCursor(IDC_ARROW), 0),
        _T("Dark Page Frame"),
        dwWindowStyle, rect, pwndParent, nID);
}

CWnd * CMPCThemePropPageFrame::GetWnd() {
    return static_cast<CWnd*>(this);
}

void CMPCThemePropPageFrame::DrawCaption(CDC *pDC, CRect rect, LPCTSTR lpszCaption, HICON hIcon) {
    COLORREF    clrLeft = CMPCTheme::ContentSelectedColor;
    COLORREF    clrRight = CMPCTheme::ContentBGColor;
    FillGradientRectH(pDC, rect, clrLeft, clrRight);

    rect.left += 2;

    COLORREF clrPrev = pDC->SetTextColor(CMPCTheme::TextFGColor);
    int nBkStyle = pDC->SetBkMode(TRANSPARENT);

    CFont f;
    CMPCThemeUtil::getFontByFace(f, pDC, CMPCTheme::uiTextFont, 10, FW_BOLD);
    CFont *pFont = pDC->SelectObject(&f);

    pDC->DrawText(lpszCaption, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

    pDC->SetTextColor(clrPrev);
    pDC->SelectObject(pFont);
    pDC->SetBkMode(nBkStyle);
}

void CMPCThemePropPageFrame::OnPaint() {
    CPaintDC dc(this);
    Draw(&dc);
}

BOOL CMPCThemePropPageFrame::OnEraseBkgnd(CDC * pDC) {
    bool ret = CMPCThemeUtil::MPCThemeEraseBkgnd(pDC, this, CTLCOLOR_DLG);
    if (ret) {
        return ret;
    } else {
        return __super::OnEraseBkgnd(pDC);
    }
}
