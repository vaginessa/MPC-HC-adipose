#include "stdafx.h"
#include "CDarkButton.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

CDarkButton::CDarkButton() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT; //just setting this to get hovering working
    }
}


CDarkButton::~CDarkButton() {
}

void CDarkButton::PreSubclassWindow() {
    CButton::PreSubclassWindow();
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        ModifyStyle(0, BS_OWNERDRAW);
    }
}

#define max(a,b)            (((a) > (b)) ? (a) : (b))
void CDarkButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect rect = CRect(lpDrawItemStruct->rcItem);
    UINT state = lpDrawItemStruct->itemState;

    CString strText;
    GetWindowText(strText);

    CBrush fb, fb2;
    fb.CreateSolidBrush(CDarkTheme::ButtonBorderOuterColor);
    pDC->FrameRect(rect, &fb);

    rect.DeflateRect(1, 1);
    COLORREF bg = CDarkTheme::ButtonFillColor, dottedClr;

    int imageIndex = 0; //Normal
    if (state & ODS_SELECTED) {//mouse down
        fb2.CreateSolidBrush(CDarkTheme::ButtonBorderInnerColor);
        bg = CDarkTheme::ButtonFillSelectedColor;
        dottedClr = CDarkTheme::ButtonBorderSelectedKBFocusColor;
    } else if (IsHighlighted()) {
        fb2.CreateSolidBrush(CDarkTheme::ButtonBorderInnerColor);
        bg = CDarkTheme::ButtonFillHoverColor;
        dottedClr = CDarkTheme::ButtonBorderHoverKBFocusColor;
    } else if (state & ODS_FOCUS) {
        fb2.CreateSolidBrush(CDarkTheme::ButtonBorderInnerFocusedColor);
        dottedClr = CDarkTheme::ButtonBorderKBFocusColor;
    } else {
        fb2.CreateSolidBrush(CDarkTheme::ButtonBorderInnerColor);
    }

    if (state & ODS_DISABLED) {
        imageIndex = 1;
    }


    pDC->FrameRect(rect, &fb2);
    rect.DeflateRect(1, 1);
    pDC->FillSolidRect(rect, bg);


    if (state & ODS_FOCUS) {
        rect.DeflateRect(1, 1);
        COLORREF oldTextFGColor = pDC->SetTextColor(dottedClr);
        COLORREF oldBGColor = pDC->SetBkColor(bg);
        CBrush *dotted = pDC->GetHalftoneBrush();
        pDC->FrameRect(rect, dotted);
        DeleteObject(dotted);
        pDC->SetTextColor(oldTextFGColor);
        pDC->SetBkColor(oldBGColor);
    }

    if (!strText.IsEmpty()) {
        int nMode = pDC->SetBkMode(TRANSPARENT);

        COLORREF oldTextFGColor;
        if (state & ODS_DISABLED)
            oldTextFGColor = pDC->SetTextColor(CDarkTheme::ButtonDisabledFGColor);
        else
            oldTextFGColor = pDC->SetTextColor(CDarkTheme::TextFGColor);

        pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        pDC->SetTextColor(oldTextFGColor);
        pDC->SetBkMode(nMode);
    }

    BUTTON_IMAGELIST imgList;
    GetImageList(&imgList);


    if (CImageList *images = CImageList::FromHandlePermanent(imgList.himl)) { //assume centered
        IMAGEINFO ii;
        if (images->GetImageCount() <= imageIndex) imageIndex = 0;
        images->GetImageInfo(imageIndex, &ii);
        int width = ii.rcImage.right - ii.rcImage.left;
        int height = ii.rcImage.bottom - ii.rcImage.top;
        rect.DeflateRect((rect.Width() - width) / 2, max(0, (rect.Height() - height) / 2));
        images->Draw(pDC, imageIndex, rect.TopLeft(), ILD_NORMAL);
    }

}

