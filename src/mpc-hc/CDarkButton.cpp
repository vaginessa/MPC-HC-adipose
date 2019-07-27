#include "stdafx.h"
#include "CDarkButton.h"
#include "CDarkTheme.h"
#include "CDarkChildHelper.h"
#include "mplayerc.h"

CDarkButton::CDarkButton() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT; //just setting this to get hovering working
    }
}

CDarkButton::~CDarkButton() {
}

void CDarkButton::PreSubclassWindow() { //bypass CMFCButton impl since it will enable ownerdraw
    InitStyle(GetStyle());
    CButton::PreSubclassWindow();
}

BOOL CDarkButton::PreCreateWindow(CREATESTRUCT& cs) {//bypass CMFCButton impl since it will enable ownerdraw
    InitStyle(cs.style);
    return CButton::PreCreateWindow(cs);
}


IMPLEMENT_DYNAMIC(CDarkButton, CMFCButton)
BEGIN_MESSAGE_MAP(CDarkButton, CMFCButton)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CDarkButton::OnNMCustomdraw)
END_MESSAGE_MAP()


void CDarkButton::drawButtonBase(CDC* pDC, CRect rect, CString strText, bool selected, bool highLighted, bool focused, bool disabled, bool thin) {
    CBrush fb, fb2;
    fb.CreateSolidBrush(CDarkTheme::ButtonBorderOuterColor);

    if (!thin) { //some small buttons look very ugly with the full border.  make up our own solution
        pDC->FrameRect(rect, &fb);
        rect.DeflateRect(1, 1);
    }
    COLORREF bg = CDarkTheme::ButtonFillColor, dottedClr = CDarkTheme::ButtonBorderKBFocusColor;

    if (selected) {//mouse down
        fb2.CreateSolidBrush(CDarkTheme::ButtonBorderInnerColor);
        bg = CDarkTheme::ButtonFillSelectedColor;
        dottedClr = CDarkTheme::ButtonBorderSelectedKBFocusColor;
    } else if (highLighted) {
        fb2.CreateSolidBrush(CDarkTheme::ButtonBorderInnerColor);
        bg = CDarkTheme::ButtonFillHoverColor;
        dottedClr = CDarkTheme::ButtonBorderHoverKBFocusColor;
    } else if (focused) {
        fb2.CreateSolidBrush(CDarkTheme::ButtonBorderInnerFocusedColor);
    } else {
        fb2.CreateSolidBrush(CDarkTheme::ButtonBorderInnerColor);
    }

    pDC->FrameRect(rect, &fb2);
    rect.DeflateRect(1, 1);
    pDC->FillSolidRect(rect, bg);


    if (focused) {
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
        if (disabled)
            oldTextFGColor = pDC->SetTextColor(CDarkTheme::ButtonDisabledFGColor);
        else
            oldTextFGColor = pDC->SetTextColor(CDarkTheme::TextFGColor);

        pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        pDC->SetTextColor(oldTextFGColor);
        pDC->SetBkMode(nMode);
    }
}

#define max(a,b)            (((a) > (b)) ? (a) : (b))
void CDarkButton::drawButton(HDC hdc, CRect rect, UINT state) {
    CDC* pDC = CDC::FromHandle(hdc);
    CFont* oldFont, *curFont = GetFont();
    oldFont = pDC->SelectObject(curFont);

    CString strText;
    GetWindowText(strText);
    bool selected = ODS_SELECTED == (state & ODS_SELECTED);
    bool focused = ODS_FOCUS == (state & ODS_FOCUS);
    bool disabled = ODS_DISABLED == (state & ODS_DISABLED);

    BUTTON_IMAGELIST imgList;
    GetImageList(&imgList);
    CImageList *images = CImageList::FromHandlePermanent(imgList.himl);
    bool thin = (images != nullptr); //thin borders for image buttons
   
    drawButtonBase(pDC, rect, strText, selected, IsHighlighted(), focused, disabled, thin);

    int imageIndex = 0; //Normal
    if (state & ODS_DISABLED) {
        imageIndex = 1;
    }

    if (images != nullptr) { //assume centered
        IMAGEINFO ii;
        if (images->GetImageCount() <= imageIndex) imageIndex = 0;
        images->GetImageInfo(imageIndex, &ii);
        int width = ii.rcImage.right - ii.rcImage.left;
        int height = ii.rcImage.bottom - ii.rcImage.top;
        rect.DeflateRect((rect.Width() - width) / 2, max(0, (rect.Height() - height) / 2));
        images->Draw(pDC, imageIndex, rect.TopLeft(), ILD_NORMAL);
    }
    pDC->SelectObject(oldFont);
}

void CDarkButton::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult) {
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    *pResult = CDRF_DODEFAULT;
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (pNMCD->dwDrawStage == CDDS_PREERASE) {
            drawButton(pNMCD->hdc, pNMCD->rc, pNMCD->uItemState);
            *pResult = CDRF_SKIPDEFAULT;
        }
    }
}
