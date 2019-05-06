#include "stdafx.h"
#include "CDarkTheme.h"

const COLORREF CDarkTheme::MenuBGColor = COLORREF(RGB(43, 43, 43));
const COLORREF CDarkTheme::WindowBGColor = COLORREF(RGB(25, 25, 25));
const COLORREF CDarkTheme::ContentBGColor = COLORREF(RGB(32, 32, 32));
const COLORREF CDarkTheme::ContentSelectedColor = COLORREF(RGB(119, 119, 119));
const COLORREF CDarkTheme::PlayerBGColor = COLORREF(RGB(32, 32, 32));

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

const COLORREF CDarkTheme::EditBorderColor = COLORREF(RGB(255, 255, 255));
const COLORREF CDarkTheme::TooltipBorderColor = COLORREF(RGB(118, 118, 118));

const COLORREF CDarkTheme::PlayerButtonHotColor = COLORREF(RGB(43, 43, 43));
const COLORREF CDarkTheme::PlayerButtonCheckedColor = COLORREF(RGB(66, 66, 66)); 
const COLORREF CDarkTheme::PlayerButtonClickedColor = COLORREF(RGB(55, 55, 55));
const COLORREF CDarkTheme::PlayerButtonBorderColor = COLORREF(RGB(0, 0, 0));

const COLORREF CDarkTheme::DebugColorRed = COLORREF(RGB(255, 0, 0));
const COLORREF CDarkTheme::DebugColorYellow = COLORREF(RGB(255, 255, 0));
const COLORREF CDarkTheme::DebugColorGreen = COLORREF(RGB(0, 255, 0));


wchar_t* const CDarkTheme::uiTextFont = L"Segoe UI";
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


CFont* CDarkTheme::getUIFont(HDC hDC, wchar_t *fontName, int size, LONG weight) {
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));

    lf.lfHeight = -MulDiv(size, GetDeviceCaps(hDC, LOGPIXELSY), 72);
    lf.lfQuality = CLEARTYPE_QUALITY;

    //lf.lfQuality = ANTIALIASED_QUALITY;
    lf.lfWeight = weight;
    wcsncpy_s(lf.lfFaceName, fontName, LF_FACESIZE);

    CFont* font = new CFont();
    font->CreateFontIndirect(&lf);

    return font;
}


CSize CDarkTheme::GetTextSize(CString str, HDC hDC) {
    CDC* cDC = CDC::FromHandle(hDC);
    CFont *font = CDarkTheme::getUIFont(hDC, CDarkTheme::uiTextFont, 9);
    CFont* pOldFont = cDC->SelectObject(font);

    CSize cs = cDC->GetTextExtent(str);

    cDC->SelectObject(pOldFont);
    delete font;

    return cs;
}
