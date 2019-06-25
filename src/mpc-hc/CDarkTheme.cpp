#include "stdafx.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

const COLORREF CDarkTheme::MenuBGColor = COLORREF(RGB(43, 43, 43));
const COLORREF CDarkTheme::WindowBGColor = COLORREF(RGB(25, 25, 25));
const COLORREF CDarkTheme::ControlAreaBGColor = COLORREF(RGB(56, 56, 56));

const COLORREF CDarkTheme::ContentBGColor = COLORREF(RGB(32, 32, 32));
const COLORREF CDarkTheme::ContentSelectedColor = COLORREF(RGB(119, 119, 119));
const COLORREF CDarkTheme::PlayerBGColor = COLORREF(RGB(32, 32, 32));

const COLORREF CDarkTheme::HighLightColor = GetSysColor(COLOR_HIGHLIGHT);

const COLORREF CDarkTheme::MenuSelectedColor = COLORREF(RGB(65, 65, 65));
const COLORREF CDarkTheme::MenuSeparatorColor = COLORREF(RGB(128, 128, 128));
const COLORREF CDarkTheme::MenuItemDisabledColor = COLORREF(RGB(109, 109, 109));

const COLORREF CDarkTheme::ShadowColor = COLORREF(RGB(25, 25, 25));
const COLORREF CDarkTheme::TextFGColor = COLORREF(RGB(255, 255, 255));
const COLORREF CDarkTheme::ContentTextDisabledFGColor = COLORREF(RGB(128, 0, 0));

const COLORREF CDarkTheme::SubmenuColor = COLORREF(RGB(191, 191, 191));
const COLORREF CDarkTheme::LightColor = COLORREF(RGB(100, 100, 100));
const COLORREF CDarkTheme::CloseHoverColor = COLORREF(RGB(232, 17, 35));
const COLORREF CDarkTheme::ClosePushColor = COLORREF(RGB(139, 10, 20));

const COLORREF CDarkTheme::WindowBorderColorLight = COLORREF(RGB(99, 99, 99));
const COLORREF CDarkTheme::WindowBorderColorDim = COLORREF(RGB(43, 43, 43));
const COLORREF CDarkTheme::NoBorderColor = COLORREF(RGB(0, 0, 0));
const COLORREF CDarkTheme::GripperPatternColor = COLORREF(RGB(70, 70, 74)); //visual studio dark, since explorer has no grippers

const COLORREF CDarkTheme::ScrollBGColor = COLORREF(RGB(23, 23, 23));
const COLORREF CDarkTheme::ScrollThumbColor = COLORREF(RGB(77, 77, 77));
const COLORREF CDarkTheme::ScrollThumbHoverColor = COLORREF(RGB(144, 144, 144));
const COLORREF CDarkTheme::ScrollThumbDragColor = COLORREF(RGB(183, 183, 183));
const COLORREF CDarkTheme::ScrollButtonArrowColor = COLORREF(RGB(103, 103, 103));
const COLORREF CDarkTheme::ScrollButtonHoverColor = COLORREF(RGB(55, 55, 55));
const COLORREF CDarkTheme::ScrollButtonClickColor = COLORREF(RGB(166, 166, 166));

const COLORREF CDarkTheme::InlineEditBorderColor = COLORREF(RGB(255, 255, 255));
const COLORREF CDarkTheme::TooltipBorderColor = COLORREF(RGB(118, 118, 118));

const COLORREF CDarkTheme::GroupBoxBorderColor = COLORREF(RGB(118, 118, 118));
const int CDarkTheme::GroupBoxTextIndent = 8;

const COLORREF CDarkTheme::PlayerButtonHotColor = COLORREF(RGB(43, 43, 43));
const COLORREF CDarkTheme::PlayerButtonCheckedColor = COLORREF(RGB(66, 66, 66)); 
const COLORREF CDarkTheme::PlayerButtonClickedColor = COLORREF(RGB(55, 55, 55));
const COLORREF CDarkTheme::PlayerButtonBorderColor = COLORREF(RGB(0, 0, 0));

const COLORREF CDarkTheme::DebugColorRed = COLORREF(RGB(255, 0, 0));
const COLORREF CDarkTheme::DebugColorYellow = COLORREF(RGB(255, 255, 0));
const COLORREF CDarkTheme::DebugColorGreen = COLORREF(RGB(0, 255, 0));

const COLORREF CDarkTheme::ButtonBorderOuterColor = COLORREF(RGB(240, 240, 240));
const COLORREF CDarkTheme::ButtonBorderInnerFocusedColor = COLORREF(RGB(255, 255, 255));
const COLORREF CDarkTheme::ButtonBorderInnerColor = COLORREF(RGB(155, 155, 155));
const COLORREF CDarkTheme::ButtonBorderSelectedKBFocusColor = COLORREF(RGB(150, 150, 150));
const COLORREF CDarkTheme::ButtonBorderHoverKBFocusColor = COLORREF(RGB(181, 181, 181));
const COLORREF CDarkTheme::ButtonBorderKBFocusColor = COLORREF(RGB(195, 195, 195));
const COLORREF CDarkTheme::ButtonFillColor = COLORREF(RGB(51, 51, 51));
const COLORREF CDarkTheme::ButtonFillHoverColor = COLORREF(RGB(69, 69, 69));
const COLORREF CDarkTheme::ButtonFillSelectedColor = COLORREF(RGB(102, 102, 102));
const COLORREF CDarkTheme::ButtonDisabledFGColor = COLORREF(RGB(109, 109, 109));

const COLORREF CDarkTheme::CheckboxBorderColor = COLORREF(RGB(137, 137, 137));
const COLORREF CDarkTheme::CheckboxBGColor = COLORREF(RGB(0, 0, 0));
const COLORREF CDarkTheme::CheckboxBorderHoverColor = COLORREF(RGB(121, 121, 121));
const COLORREF CDarkTheme::CheckboxBGHoverColor = COLORREF(RGB(8, 8, 8));

const COLORREF CDarkTheme::ImageDisabledColor = COLORREF(RGB(109, 109, 109));

const COLORREF CDarkTheme::SliderChannelColor = COLORREF(RGB(109, 109, 109));

const COLORREF CDarkTheme::EditBorderColor = COLORREF(RGB(106, 106, 106));

const COLORREF CDarkTheme::TreeCtrlLineColor = COLORREF(RGB(106, 106, 106));
const COLORREF CDarkTheme::TreeCtrlHoverColor = COLORREF(RGB(77, 77, 77));;
const COLORREF CDarkTheme::TreeCtrlFocusColor = COLORREF(RGB(98, 98, 98));;

const COLORREF CDarkTheme::CheckColor = COLORREF(RGB(222, 222, 222));;

const COLORREF CDarkTheme::ColumnHeaderHotColor = COLORREF(RGB(67, 67, 67));;

const COLORREF CDarkTheme::StaticEtchedColor = COLORREF(RGB(65, 65, 65));


wchar_t* const CDarkTheme::uiTextFont = L"Segoe UI";
wchar_t* const CDarkTheme::uiStaticTextFont = L"Segoe UI Semilight";
wchar_t* const CDarkTheme::uiSymbolFont = L"MS UI Gothic";

const int CDarkTheme::gripPatternLong = 5;
const int CDarkTheme::gripPatternShort = 4;

const BYTE CDarkTheme::GripperBitsH[10] = {
    0x80, 0x00,
    0x00, 0x00,
    0x20, 0x00,
    0x00, 0x00,
    0x80, 0x00,
};

const BYTE CDarkTheme::GripperBitsV[8] = {
    0x88, 0x00,
    0x00, 0x00,
    0x20, 0x00,
    0x00, 0x00,
};

const int CDarkTheme::scrollArrowLong = 7;
const int CDarkTheme::scrollArrowShort = 6;

const BYTE CDarkTheme::ScrollArrowBitsV[12] = {
    0x10, 0x00,
    0x38, 0x00,
    0x7C, 0x00,
    0xEE, 0x00,
    0xC6, 0x00,
    0x82, 0x00,
};
const BYTE CDarkTheme::ScrollArrowBitsH[14] = {
    0x1C, 0x00,
    0x38, 0x00,
    0x70, 0x00,
    0xE0, 0x00,
    0x70, 0x00,
    0x38, 0x00,
    0x1C, 0x00,
};

const BYTE CDarkTheme::ComboArrowBits[10] = {
    0x80, 0x40,
    0x40, 0x80,
    0x21, 0x00,
    0x12, 0x00,
    0x0C, 0x00,
};
const int CDarkTheme::ComboArrowWidth = 10;
const int CDarkTheme::ComboArrowHeight = 5;

const COLORREF CDarkTheme::ComboboxArrowColor[3] = {
    COLORREF(RGB(113, 113, 113)),
    COLORREF(RGB(173, 173, 173)),
    COLORREF(RGB(62, 62, 62)),
};

const COLORREF CDarkTheme::ComboboxArrowColorHover[3] = {
    COLORREF(RGB(123, 123, 123)),
    COLORREF(RGB(177, 177, 177)),
    COLORREF(RGB(78, 78, 78)),
};

const COLORREF CDarkTheme::ComboboxArrowColorClick[3] = {
    COLORREF(RGB(143, 143, 143)),
    COLORREF(RGB(183, 183, 183)),
    COLORREF(RGB(109, 109, 109)),
};

const BYTE CDarkTheme::SpinnerArrowBitsV[6] = {
    0x20, 0x00,
    0x70, 0x00,
    0xF8, 0x00,
};
const BYTE CDarkTheme::SpinnerArrowBitsH[10] = {
    0x20, 0x00,
    0x60, 0x00,
    0xE0, 0x00,
    0x60, 0x00,
    0x20, 0x00,
};

const int CDarkTheme::SpinnerArrowWidth = 5;
const int CDarkTheme::SpinnerArrowHeight = 3;

const BYTE CDarkTheme::CheckBits[14] = {
    0x02, 0x00,
    0x06, 0x00,
    0x8E, 0x00,
    0xDC, 0x00,
    0xF8, 0x00,
    0x70, 0x00,
    0x20, 0x00,
};

const int CDarkTheme::CheckWidth = 7;
const int CDarkTheme::CheckHeight = 7;


void CDarkTheme::getUIFont(CFont &font, HDC hDC, wchar_t *fontName, int size, LONG weight) {
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));

    lf.lfHeight = -MulDiv(size, GetDeviceCaps(hDC, LOGPIXELSY), 72);
    lf.lfQuality = CLEARTYPE_QUALITY;

    //lf.lfQuality = ANTIALIASED_QUALITY;
    lf.lfWeight = weight;
    wcsncpy_s(lf.lfFaceName, fontName, LF_FACESIZE);

    font.CreateFontIndirect(&lf);
}

void CDarkTheme::getUIFont(CFont &font, HDC hDC, int type, bool underline) {
    NONCLIENTMETRICS m = GetMetrics();
    LOGFONT *lf;
    if (type == CDCaptionFont) {
        lf = &m.lfCaptionFont;
    } else if (type == CDSmallCaptionFont) {
        lf = &m.lfSmCaptionFont;
    } else if (type == CDMenuFont) {
        lf = &m.lfMenuFont;
    } else if (type == CDStatusFont) {
        lf = &m.lfStatusFont;
    } else if (type == CDMessageFont) {
        lf = &m.lfMessageFont;
    } else if (type == CDDialogFont) { //hack for compatibility with MS SHell Dlg (8) used in dialogs
        LOGFONT tlf;
        memset(&tlf, 0, sizeof(LOGFONT));
        tlf.lfHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);
        tlf.lfQuality = CLEARTYPE_QUALITY;
        tlf.lfWeight = FW_REGULAR;
        wcsncpy_s(tlf.lfFaceName, m.lfMessageFont.lfFaceName, LF_FACESIZE);
        lf = &tlf;
    } else {
        lf = &m.lfMessageFont;
    }
    if (underline) {
        LOGFONT tlf;
        memset(&tlf, 0, sizeof(LOGFONT));
        tlf.lfHeight = lf->lfHeight;
        tlf.lfQuality = lf->lfQuality;
        tlf.lfWeight = lf->lfWeight;
        wcsncpy_s(tlf.lfFaceName, lf->lfFaceName, LF_FACESIZE);
        tlf.lfUnderline = TRUE;
        font.CreateFontIndirect(&tlf);
    } else {
        font.CreateFontIndirect(lf);
    }
}

CSize CDarkTheme::GetTextSize(CString str, HDC hDC, int type) {
    CDC* cDC = CDC::FromHandle(hDC);
    CFont font;
    getUIFont(font, hDC, type);
    CFont* pOldFont = cDC->SelectObject(&font);

    CSize cs = cDC->GetTextExtent(str);

    cDC->SelectObject(pOldFont);

    return cs;
}

CSize CDarkTheme::GetTextSizeDiff(CString str, HDC hDC, int type, CFont * curFont) {
    CSize cs = GetTextSize(str, hDC, type);
    CDC* cDC = CDC::FromHandle(hDC);
    CFont* pOldFont = cDC->SelectObject(curFont);
    CSize curCs = cDC->GetTextExtent(str);
    cDC->SelectObject(pOldFont);

    return cs - curCs;
}

bool CDarkTheme::haveMetrics = false;
NONCLIENTMETRICS CDarkTheme::_metrics = NONCLIENTMETRICS();
NONCLIENTMETRICS& CDarkTheme::GetMetrics() {
    if (!haveMetrics) {
        CDarkTheme::_metrics.cbSize = sizeof(NONCLIENTMETRICS);
        ::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &CDarkTheme::_metrics, 0);
        haveMetrics = true;
    }
    return CDarkTheme::_metrics;
}

void CDarkTheme::DrawBufferedText(CDC * pDC, CString text, CRect rect, UINT format) {
    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);
    dcMem.SetBkColor(pDC->GetBkColor());
    dcMem.SetTextColor(pDC->GetTextColor());
    dcMem.SetBkMode(pDC->GetBkMode());
    dcMem.SelectObject(pDC->GetCurrentFont());

    CBitmap bmMem;
    bmMem.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
    dcMem.SelectObject(&bmMem);
    dcMem.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rect.left, rect.top, SRCCOPY);

    CRect tr = rect;
    tr.OffsetRect(-tr.left, -tr.top);
    dcMem.DrawText(text, tr, format);

    pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY);
}

void CDarkTheme::Draw2BitTransparent(CDC & dc, int left, int top, int width, int height, CBitmap &bmp, COLORREF fgColor) {
    COLORREF crOldTextColor = dc.GetTextColor();
    COLORREF crOldBkColor = dc.GetBkColor();

    CDC dcBMP;
    dcBMP.CreateCompatibleDC(&dc);

    dcBMP.SelectObject(bmp);
    dc.BitBlt(left, top, width, height, &dcBMP, 0, 0, SRCINVERT); //SRCINVERT works to create mask from 2-bit image. same result as bitblt with text=0 and bk=0xffffff
    dc.SetBkColor(fgColor);        //paint: foreground color (1 in 2 bit)
    dc.SetTextColor(RGB(0, 0, 0)); //paint: black where transparent
    dc.BitBlt(left, top, width, height, &dcBMP, 0, 0, SRCPAINT);

    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);
}

void CDarkTheme::dbg(CString text, ...) {
    va_list args;
    va_start(args, text);
    CString output;
    output.FormatV(text, args);
    OutputDebugString(output);
    OutputDebugString(_T("\n"));
    va_end(args);
}

void CDarkTheme::drawCheckBox(bool isChecked, bool isHover, bool useImage, CRect rectCheck, CDC *pDC) {
    COLORREF borderClr, bgClr;
    COLORREF oldBkClr = pDC->GetBkColor(), oldTextClr = pDC->GetTextColor();
    if (isHover) {
        borderClr = CDarkTheme::CheckboxBorderHoverColor;
        bgClr = CDarkTheme::CheckboxBGHoverColor;
    } else {
        borderClr = CDarkTheme::CheckboxBorderColor;
        bgClr = CDarkTheme::CheckboxBGColor;
    }

    if (isChecked && useImage) {
        CPngImage image;
        image.Load(isHover ? IDB_PNG_DARKCBHOVER : IDB_PNG_DARKCB, AfxGetInstanceHandle());
        CDC mDC;
        mDC.CreateCompatibleDC(pDC);
        mDC.SelectObject(image);
        pDC->BitBlt(rectCheck.left, rectCheck.top, rectCheck.Width(), rectCheck.Height(), &mDC, 0, 0, SRCCOPY);
    } else {
        CBrush brush(borderClr);
        pDC->FrameRect(rectCheck, &brush);
        rectCheck.DeflateRect(1, 1);
        pDC->FillSolidRect(rectCheck, bgClr);
        if (isChecked) {
            CBitmap checkBMP;
            CDC dcCheckBMP;
            dcCheckBMP.CreateCompatibleDC(pDC);

            int left, top, width, height;
            width = CheckWidth;
            height = CheckHeight;
            left = rectCheck.left + (rectCheck.Width() - width) / 2;
            top = rectCheck.top + (rectCheck.Height() - height) / 2;
            checkBMP.CreateBitmap(width, height, 1, 1, CheckBits);
            dcCheckBMP.SelectObject(&checkBMP);

            pDC->SetBkColor(CheckColor);
            pDC->SetTextColor(bgClr);
            pDC->BitBlt(left, top, width, height, &dcCheckBMP, 0, 0, SRCCOPY);
        }
    }
    pDC->SetBkColor(oldBkClr);
    pDC->SetTextColor(oldTextClr);
}

bool CDarkTheme::canUseWin10DarkTheme() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
//        return false; //FIXME.  return false to test behavior for OS < Win10
        return IsWindows10OrGreater();
    }
    return false;
}


