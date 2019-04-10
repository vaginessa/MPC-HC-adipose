#include "stdafx.h"
#include "CDarkDockBar.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

IMPLEMENT_DYNAMIC(CDarkDockBar, CDockBar)
BEGIN_MESSAGE_MAP(CDarkDockBar, CDockBar)
    ON_WM_ERASEBKGND()
    ON_WM_NCPAINT()
END_MESSAGE_MAP()

CDarkDockBar::CDarkDockBar() {
}


CDarkDockBar::~CDarkDockBar() {
}


BOOL CDarkDockBar::OnEraseBkgnd(CDC* pDC) {
    const CAppSettings& s = AfxGetAppSettings();
    if (!s.bDarkThemeLoaded) {
        return __super::OnEraseBkgnd(pDC);
    }

    CBrush backBrush(RGB(0, 255, 255));

    CBrush* pOldBrush = pDC->SelectObject(&backBrush);
    CRect rect;
    pDC->GetClipBox(&rect);

    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOldBrush);

    return TRUE;
}


void CDarkDockBar::OnNcPaint() {
    const CAppSettings& s = AfxGetAppSettings();
    if (!s.bDarkThemeLoaded) {
        __super::OnNcPaint();
        return;
    }

    CWindowDC dc(this); // the HDC will be released by the destructor

    CRect rcClient, rcBar;
    GetClientRect(rcClient);
    GetWindowRect(rcBar);
    ScreenToClient(rcBar);

    CRect rcDraw = rcBar;

    dc.FillSolidRect(rcDraw, CDarkTheme::DarkBGColor);

    dc.IntersectClipRect(rcBar);
    dc.ExcludeClipRect(rcClient);
}
