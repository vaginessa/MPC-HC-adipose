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
    buttonStyle = GetButtonStyle();

    if (BS_RADIOBUTTON == (buttonStyle & BS_RADIOBUTTON) || BS_AUTORADIOBUTTON == (buttonStyle & BS_AUTORADIOBUTTON)) {
        buttonType = radioType;
        isAuto = BS_AUTORADIOBUTTON == (buttonStyle & BS_AUTORADIOBUTTON);
    } else if (BS_CHECKBOX == (buttonStyle & BS_CHECKBOX) || BS_AUTOCHECKBOX == (buttonStyle & BS_AUTOCHECKBOX)) {
        buttonType = checkType;
        isAuto = BS_AUTOCHECKBOX == (buttonStyle & BS_AUTOCHECKBOX);
    }
    ASSERT(buttonType != unknownType);

    buttonStyle = GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE);
    CDarkTheme::getUIFont(font, ::GetWindowDC(NULL), CDarkTheme::CDDialogFont);
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

        bool isChecked = (SendMessage(BM_GETCHECK) == BST_CHECKED);

        CRect rectCheck;
        int cbWidth = GetSystemMetrics(SM_CXMENUCHECK);
        int cbHeight = GetSystemMetrics(SM_CYMENUCHECK);

        if (buttonStyle & BS_LEFTTEXT) {
            rectCheck.left = rectItem.right - cbWidth;
            rectCheck.right = rectCheck.left + cbWidth;
            rectItem.right = rectCheck.left - 1;
        } else {
            rectCheck.left = rectItem.left;
            rectCheck.right = rectCheck.left + cbWidth;
            rectItem.left = rectCheck.right + 1;
        }

        rectCheck.top = (rectItem.Height() - cbHeight) / 2;
        rectCheck.bottom = rectCheck.top + cbHeight;

        if (buttonType == checkType) {
            rectCheck.DeflateRect(1, 1); //1 pixel border
            CDarkTheme::drawCheckBox(isChecked, isHover, true, rectCheck, &dc);
        } else if (buttonType == radioType) {
            UINT res;
            if (isChecked) {
                res = isHover ? IDB_PNG_DARKRADIOSETHOVER : IDB_PNG_DARKRADIOSET;
            } else {
                res = isHover ? IDB_PNG_DARKRADIOHOVER : IDB_PNG_DARKRADIO;
            }
            CPngImage image;
            image.Load(res, AfxGetInstanceHandle());
            CDC mDC;
            mDC.CreateCompatibleDC(&dc);
            mDC.SelectObject(image);

            rectCheck.DeflateRect(1, 1); //1 pixel border
            dc.BitBlt(rectCheck.left, rectCheck.top, rectCheck.Width(), rectCheck.Height(), &mDC, 0, 0, SRCCOPY);
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
