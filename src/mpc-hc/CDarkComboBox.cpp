#include "stdafx.h"
#include "CDarkComboBox.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

IMPLEMENT_DYNAMIC(CDarkComboBox, CComboBox)

BEGIN_MESSAGE_MAP(CDarkComboBox, CComboBox)
    ON_WM_PAINT()
    ON_WM_SETFOCUS()
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSELEAVE()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_CREATE()
END_MESSAGE_MAP()

CDarkComboBox::CDarkComboBox() {
    isHover = false;
    isThemedDropDown = false;
}

void CDarkComboBox::doDraw(CDC& dc, CString strText, CRect rText, COLORREF bkColor, bool drawDotted) {
    COLORREF crOldTextColor = dc.GetTextColor();
    COLORREF crOldBkColor = dc.GetBkColor();

    dc.SetBkColor(bkColor);
    dc.SetTextColor(CDarkTheme::TextFGColor);

    CRect textRect = rText;
    textRect.left += 3;

    CFont font;
    CDarkTheme::getUIFont(font, dc.m_hDC, CDarkTheme::CDDialogFont);
    CFont* pOldFont = dc.SelectObject(&font);
    dc.DrawText(strText, &textRect, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
    dc.SelectObject(pOldFont);

    if (drawDotted) {
        dc.SetTextColor(bkColor ^ 0xffffff);
        CBrush *dotted = dc.GetHalftoneBrush();
        dc.FrameRect(rText, dotted);
        DeleteObject(dotted);
    }

    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);
}

CDarkComboBox::~CDarkComboBox() {
}

void CDarkComboBox::themeDropDown() {
    if (IsWindows10OrGreater() && false == isThemedDropDown) {
        COMBOBOXINFO info = { sizeof(COMBOBOXINFO) };
        if (GetComboBoxInfo(&info)) {
            SetWindowTheme(info.hwndList, L"DarkMode_Explorer", NULL);
            isThemedDropDown = true;
        }
    }
}

void CDarkComboBox::PreSubclassWindow() {
    themeDropDown();
}


void CDarkComboBox::OnPaint() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        CPaintDC dc(this);
        CRect r, rBorder, rText, rBG, rSelect, rDownArrow;
        GetClientRect(r);
        CString strText;
        GetWindowText(strText);
        const COLORREF* arrClr;

        CBrush fb;
        bool isFocused = (GetFocus() == this);
        bool drawDotted = false;
        if (isFocused) {
            //unless edit exists, no inner border -- fixme if edit combobox needed
            //fb.CreateSolidBrush(CDarkTheme::ButtonBorderInnerFocusedColor);
            fb.CreateSolidBrush(CDarkTheme::ButtonBorderInnerColor);
            drawDotted = true;
        } else {
            fb.CreateSolidBrush(CDarkTheme::ButtonBorderInnerColor);
        }
        COMBOBOXINFO info = { sizeof(COMBOBOXINFO) };
        GetComboBoxInfo(&info);

        COLORREF bkColor;
        if (::IsWindowVisible(info.hwndList) || info.stateButton == STATE_SYSTEM_PRESSED) { //always looks the same once the list is open
            bkColor = CDarkTheme::ButtonFillSelectedColor;
            drawDotted = false;
            arrClr = CDarkTheme::ComboboxArrowColorClick;
        } else if (info.stateButton == 0 && isHover) {  //not pressed and hovered
            bkColor = CDarkTheme::ButtonFillHoverColor;
            arrClr = CDarkTheme::ComboboxArrowColorHover;
        } else {
            bkColor = CDarkTheme::ButtonFillColor;
            arrClr = CDarkTheme::ComboboxArrowColor;
        }

        rBG = r;
        rBG.DeflateRect(1, 1);
        dc.FillSolidRect(rBG, bkColor);

        rText = r;
        rText.right = info.rcItem.right;
        rText.DeflateRect(3, 3);
        doDraw(dc, strText, rText, bkColor, drawDotted);

        rDownArrow = info.rcButton;
        CBitmap arrowLowerBMP, arrowUpperBMP;
        int arrowLeft, arrowTop, arrowWidth, arrowHeight, arrowUpperHeight;
        arrowWidth = CDarkTheme::ComboArrowWidth;
        arrowHeight = CDarkTheme::ComboArrowHeight;
        arrowUpperHeight = arrowHeight - 1;
        arrowLowerBMP.CreateBitmap(arrowWidth, arrowHeight, 1, 1, CDarkTheme::ComboArrowBits);
        arrowUpperBMP.CreateBitmap(arrowWidth, arrowUpperHeight, 1, 1, CDarkTheme::ComboArrowBits + sizeof(BYTE) * 2);
        arrowLeft = rDownArrow.left + (rDownArrow.Width() - arrowWidth) / 2;
        arrowTop = rDownArrow.top + (rDownArrow.Height() - (arrowHeight + 1) + 1) / 2; //add 1 to height because arrow is 1 taller than BMP.  add 1 to force rounding positive

        CDarkTheme::Draw2BitTransparent(dc, arrowLeft, arrowTop, arrowWidth, arrowUpperHeight, arrowUpperBMP, arrClr[0]);
        CDarkTheme::Draw2BitTransparent(dc, arrowLeft, arrowTop + 1, arrowWidth, arrowUpperHeight, arrowUpperBMP, arrClr[1]);
        CDarkTheme::Draw2BitTransparent(dc, arrowLeft, arrowTop + 1, arrowWidth, arrowHeight, arrowLowerBMP, arrClr[2]);

        rBorder = r;
        dc.FrameRect(rBorder, &fb);
    } else {
        CComboBox::OnPaint();
    }
}


void CDarkComboBox::OnSetFocus(CWnd* pOldWnd) {
    CComboBox::OnSetFocus(pOldWnd);
    //Invalidate();
}

void CDarkComboBox::checkHover(UINT nFlags, CPoint point, bool invalidate) {
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

void CDarkComboBox::OnMouseMove(UINT nFlags, CPoint point) {
    checkHover(nFlags, point);
    CComboBox::OnMouseMove(nFlags, point);
}


void CDarkComboBox::OnMouseLeave() {
    checkHover(0, CPoint(-1,-1));
    CComboBox::OnMouseLeave();
}


void CDarkComboBox::OnLButtonUp(UINT nFlags, CPoint point) {
    checkHover(nFlags, point, false);
    CComboBox::OnLButtonUp(nFlags, point);
}


void CDarkComboBox::OnLButtonDown(UINT nFlags, CPoint point) {
    checkHover(nFlags, point);
    CComboBox::OnLButtonDown(nFlags, point);
}


int CDarkComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (__super::OnCreate(lpCreateStruct) == -1)
        return -1;

    themeDropDown();

    return 0;
}
