#include "stdafx.h"
#include "CDarkPropPageFrame.h"
#include "CDarkTheme.h"
#include "CDarkChildHelper.h"
#include "TreePropSheet/PropPageFrameDefault.h"

CDarkPropPageFrame::CDarkPropPageFrame() : CPropPageFrameDefault() {
}


CDarkPropPageFrame::~CDarkPropPageFrame() {
}

BEGIN_MESSAGE_MAP(CDarkPropPageFrame, CPropPageFrameDefault)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CDarkPropPageFrame::Create(DWORD dwWindowStyle, const RECT & rect, CWnd * pwndParent, UINT nID) {
    return CWnd::Create(
        AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, AfxGetApp()->LoadStandardCursor(IDC_ARROW), 0),
        _T("Dark Page Frame"),
        dwWindowStyle, rect, pwndParent, nID);
}

CWnd * CDarkPropPageFrame::GetWnd() {
    return static_cast<CWnd*>(this);
}

void CDarkPropPageFrame::DrawCaption(CDC *pDC, CRect rect, LPCTSTR lpszCaption, HICON hIcon) {
    COLORREF    clrLeft = CDarkTheme::ContentSelectedColor;
    COLORREF    clrRight = CDarkTheme::ContentBGColor;
    FillGradientRectH(pDC, rect, clrLeft, clrRight);

    rect.left += 2;

    COLORREF clrPrev = pDC->SetTextColor(CDarkTheme::TextFGColor);
    int nBkStyle = pDC->SetBkMode(TRANSPARENT);

    CFont f;
    CDarkTheme::getFontByFace(f, pDC, CDarkTheme::uiTextFont, 10, FW_BOLD);
    CFont *pFont = pDC->SelectObject(&f);

    pDC->DrawText(lpszCaption, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

    pDC->SetTextColor(clrPrev);
    pDC->SelectObject(pFont);
    pDC->SetBkMode(nBkStyle);
}

void CDarkPropPageFrame::OnPaint() {
    CPaintDC dc(this);
    Draw(&dc);
}

BOOL CDarkPropPageFrame::OnEraseBkgnd(CDC * pDC) {
    bool ret = CDarkChildHelper::MPCThemeEraseBkgnd(pDC, this, CTLCOLOR_DLG);
    if (ret) {
        return ret;
    } else {
        return __super::OnEraseBkgnd(pDC);
    }
}
