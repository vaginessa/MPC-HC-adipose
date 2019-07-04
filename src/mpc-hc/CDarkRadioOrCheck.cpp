#include "stdafx.h"
#include "CDarkRadioOrCheck.h"
#include "CDarkTheme.h"

CDarkRadioOrCheck::CDarkRadioOrCheck() {
    isHover = false;
    buttonType = unknownType;
}


CDarkRadioOrCheck::~CDarkRadioOrCheck() {
}

void CDarkRadioOrCheck::PreSubclassWindow() {
    DWORD winButtonType = (GetButtonStyle() & BS_TYPEMASK);

    if (BS_RADIOBUTTON == winButtonType || BS_AUTORADIOBUTTON == winButtonType) {
        buttonType = radioType;
        isAuto = BS_AUTORADIOBUTTON == winButtonType;
    } else if (BS_3STATE == winButtonType || BS_AUTO3STATE == winButtonType) {
        buttonType = threeStateType;
        isAuto = BS_AUTO3STATE == winButtonType;
    } else if (BS_CHECKBOX == winButtonType || BS_AUTOCHECKBOX == winButtonType) {
        buttonType = checkType;
        isAuto = BS_AUTOCHECKBOX == winButtonType;
    }
    ASSERT(buttonType != unknownType);

    buttonStyle = GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE);
    CDarkTheme::getFontByType(font, GetWindowDC(), CDarkTheme::CDDialogFont);
    SetFont(&font); //DSUtil checks metrics and resizes.  if our font is a bit different, things can look funny
    CButton::PreSubclassWindow();
}

IMPLEMENT_DYNAMIC(CDarkRadioOrCheck, CButton)
BEGIN_MESSAGE_MAP(CDarkRadioOrCheck, CButton)
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSELEAVE()
    ON_WM_PAINT()
    ON_WM_ENABLE()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CDarkRadioOrCheck::OnPaint() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        CPaintDC dc(this);
        CRect   rectItem;
        GetClientRect(rectItem);

        COLORREF oldBkColor = dc.GetBkColor();
        COLORREF oldTextColor = dc.GetTextColor();

        bool isDisabled = !IsWindowEnabled();
        bool isFocused = (GetFocus() == this);

        LRESULT checkState = SendMessage(BM_GETCHECK);

        CRect rectCheck;
        CDarkTheme::themeMetrics &tm = CDarkTheme::GetMetrics(&dc);
        int cbWidth = GetSystemMetrics(SM_CXMENUCHECK);
        int cbHeight = GetSystemMetrics(SM_CYMENUCHECK);

        if (buttonStyle & BS_LEFTTEXT) {
            rectCheck.left = rectItem.right - cbWidth;
            rectCheck.right = rectCheck.left + cbWidth;
            rectItem.right = rectCheck.left - 2;
        } else {
            rectCheck.left = rectItem.left;
            rectCheck.right = rectCheck.left + cbWidth;
            rectItem.left = rectCheck.right + 2;
        }

        rectCheck.top = (rectItem.Height() - cbHeight) / 2;
        rectCheck.bottom = rectCheck.top + cbHeight;

        if (buttonType == checkType) {
            CDarkTheme::drawCheckBox(checkState, isHover, true, rectCheck, &dc);
        } else if (buttonType == threeStateType) {
            CDarkTheme::drawCheckBox(checkState, isHover, true, rectCheck, &dc);
        } else if (buttonType == radioType) {
            CDarkTheme::drawCheckBox(checkState, isHover, true, rectCheck, &dc, true);
        }

        CString sTitle;
        GetWindowText(sTitle);

        if (!sTitle.IsEmpty()) {
            CRect centerRect = rectItem;
            CFont* pOldFont = dc.SelectObject(&font);

            UINT uFormat = 0;
            if (buttonStyle & BS_MULTILINE) {
                uFormat |= DT_WORDBREAK;
            } else {
                uFormat |= DT_SINGLELINE;
            }

            if (buttonStyle & BS_VCENTER) {
                uFormat |= DT_VCENTER;
            }

            if ((buttonStyle & BS_CENTER) == BS_CENTER) {
                uFormat |= DT_CENTER;
                dc.DrawText(sTitle, -1, &rectItem, uFormat | DT_CALCRECT);
                rectItem.OffsetRect((centerRect.Width() - rectItem.Width()) / 2,
                    (centerRect.Height() - rectItem.Height()) / 2);
            } else if ((buttonStyle & BS_RIGHT) == BS_RIGHT) {
                uFormat |= DT_RIGHT;
                dc.DrawText(sTitle, -1, &rectItem, uFormat | DT_CALCRECT);
                rectItem.OffsetRect(centerRect.Width() - rectItem.Width(),
                    (centerRect.Height() - rectItem.Height()) / 2);
            } else { // if ((buttonStyle & BS_LEFT) == BS_LEFT) {
                uFormat |= DT_LEFT;
                dc.DrawText(sTitle, -1, &rectItem, uFormat | DT_CALCRECT);
                rectItem.OffsetRect(0, (centerRect.Height() - rectItem.Height()) / 2);
            }

            dc.SetBkColor(CDarkTheme::WindowBGColor);
            if (isDisabled) {
                dc.SetTextColor(CDarkTheme::ButtonDisabledFGColor);
                dc.DrawText(sTitle, -1, &rectItem, uFormat);
            } else {
                dc.SetTextColor(CDarkTheme::TextFGColor);
                dc.DrawText(sTitle, -1, &rectItem, uFormat);
            }
            dc.SelectObject(pOldFont);

            if (isFocused) {
                CRect focusRect = rectItem;
                focusRect.InflateRect(0, 0);
                dc.SetTextColor(CDarkTheme::ButtonBorderKBFocusColor); //no example of this in explorer, but white seems too harsh
                CBrush *dotted = dc.GetHalftoneBrush();
                dc.FrameRect(focusRect, dotted);
                DeleteObject(dotted);
            }

        }
        dc.SetBkColor(oldBkColor);
        dc.SetTextColor(oldTextColor);
    } else {
        CButton::OnPaint();
    }
}

void CDarkRadioOrCheck::OnSetFocus(CWnd* pOldWnd) {
    CButton::OnSetFocus(pOldWnd);
    Invalidate();
}

void CDarkRadioOrCheck::checkHover(UINT nFlags, CPoint point, bool invalidate) {
    CRect r;
    GetClientRect(r);
    bool oldHover = isHover;
    CPoint ptScreen = point;
    ClientToScreen(&ptScreen);

    if (r.PtInRect(point) && WindowFromPoint(ptScreen)->GetSafeHwnd() == GetSafeHwnd()) {
        isHover = true;
    } else {
        isHover = false;
    }
    if (isHover != oldHover && invalidate) {
        Invalidate();
    }

}

void CDarkRadioOrCheck::OnMouseMove(UINT nFlags, CPoint point) {
    checkHover(nFlags, point);
    CButton::OnMouseMove(nFlags, point);
}


void CDarkRadioOrCheck::OnMouseLeave() {
    checkHover(0, CPoint(-1, -1));
    CButton::OnMouseLeave();
}


void CDarkRadioOrCheck::OnLButtonUp(UINT nFlags, CPoint point) {
    checkHover(nFlags, point, false);
    CButton::OnLButtonUp(nFlags, point);
}


void CDarkRadioOrCheck::OnLButtonDown(UINT nFlags, CPoint point) {
    checkHover(nFlags, point);
    CButton::OnLButtonDown(nFlags, point);
}



void CDarkRadioOrCheck::OnEnable(BOOL bEnable) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        SetRedraw(FALSE);
        __super::OnEnable(bEnable);
        SetRedraw(TRUE);
        Invalidate(); //WM_PAINT not handled when enabling/disabling
    } else {
        __super::OnEnable(bEnable);
    }
}


BOOL CDarkRadioOrCheck::OnEraseBkgnd(CDC* pDC) {
    CRect r;
    GetClientRect(r);
    pDC->FillSolidRect(r, CDarkTheme::CDarkTheme::WindowBGColor);
    return TRUE;
}
