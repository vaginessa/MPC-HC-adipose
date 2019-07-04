#include "stdafx.h"
#include "CDarkStaticLink.h"
#include "CDarkTheme.h"

CDarkStaticLink::CDarkStaticLink(LPCTSTR lpText, bool bDeleteOnDestroy) : CStaticLink(lpText, bDeleteOnDestroy) {
}

CDarkStaticLink::~CDarkStaticLink() {
}


IMPLEMENT_DYNAMIC(CDarkStaticLink, CStaticLink)

BEGIN_MESSAGE_MAP(CDarkStaticLink, CStaticLink)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_ENABLE()
END_MESSAGE_MAP()



void CDarkStaticLink::OnPaint() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {  //only reason for custom paint is disabled statics do not honor ctlcolor and draw greyed text which looks terrible on other bgs
        CPaintDC dc(this); // device context for painting
        COLORREF oldBkClr = dc.GetBkColor();
        COLORREF oldTextClr = dc.GetTextColor();
        int oldBkMode = dc.GetBkMode();

        dc.SetBkMode(TRANSPARENT);

        CRect r;

        CString text;
        GetWindowText(text);
        DWORD format = 0;
        DWORD style = GetStyle();
        if (style & SS_RIGHT) {
            format |= DT_RIGHT;
        } else if (style & SS_CENTER) {
            format |= DT_CENTER;
        } //else DT_LEFT is default

        if (style & SS_CENTERIMAGE) { //applies to text, too
            format |= DT_VCENTER;
        }

        if (!IsWindowEnabled()) {
            dc.SetTextColor(CDarkTheme::ContentTextDisabledFGColorWarn);
        } else {
            dc.SetTextColor(CDarkTheme::TextFGColor);
        }
        CFont f;
        CDarkTheme::getFontByType(f, &dc, CDarkTheme::CDMessageFont, true);
        CFont *oldFont = dc.SelectObject(&f);
        dc.DrawText(text, r, format | DT_CALCRECT);
        dc.DrawText(text, r, format);

        dc.SelectObject(oldFont);
        dc.SetBkColor(oldBkClr);
        dc.SetTextColor(oldTextClr);
        dc.SetBkMode(oldBkMode);
    } else {
        __super::OnPaint();
    }
}


HBRUSH CDarkStaticLink::CtlColor(CDC* pDC, UINT nCtlColor) { //avoid overridden cstaticlink ctlcolor
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        return NULL;
    } else {
        return __super::CtlColor(pDC, nCtlColor);
    }
}


void CDarkStaticLink::OnEnable(BOOL bEnable) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        SetRedraw(FALSE);
        __super::OnEnable(bEnable);
        SetRedraw(TRUE);
        Invalidate(); //WM_PAINT not handled when enabling/disabling
    } else {
        __super::OnEnable(bEnable);
    }
}
