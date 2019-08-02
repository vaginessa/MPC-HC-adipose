#include "stdafx.h"
#include "CMPCTheme.h"
#include "mplayerc.h"

const COLORREF CMPCTheme::MenuBGColor = COLORREF(RGB(43, 43, 43));
const COLORREF CMPCTheme::WindowBGColor = COLORREF(RGB(25, 25, 25));
const COLORREF CMPCTheme::ControlAreaBGColor = COLORREF(RGB(56, 56, 56));

const COLORREF CMPCTheme::ContentBGColor = COLORREF(RGB(32, 32, 32));
const COLORREF CMPCTheme::ContentSelectedColor = COLORREF(RGB(119, 119, 119));
const COLORREF CMPCTheme::PlayerBGColor = COLORREF(RGB(32, 32, 32));

const COLORREF CMPCTheme::HighLightColor = GetSysColor(COLOR_HIGHLIGHT);

const COLORREF CMPCTheme::MenuSelectedColor = COLORREF(RGB(65, 65, 65));
const COLORREF CMPCTheme::MenuSeparatorColor = COLORREF(RGB(128, 128, 128));
const COLORREF CMPCTheme::MenuItemDisabledColor = COLORREF(RGB(109, 109, 109));

const COLORREF CMPCTheme::ShadowColor = COLORREF(RGB(25, 25, 25));
const COLORREF CMPCTheme::TextFGColor = COLORREF(RGB(255, 255, 255));
const COLORREF CMPCTheme::ContentTextDisabledFGColorFade = COLORREF(RGB(109, 109, 109));
const COLORREF CMPCTheme::ContentTextDisabledFGColorFade2 = COLORREF(RGB(60, 60, 60)); //even more faded, used for NA text on CListCtrl/audio switcher

const COLORREF CMPCTheme::SubmenuColor = COLORREF(RGB(191, 191, 191));
const COLORREF CMPCTheme::LightColor = COLORREF(RGB(100, 100, 100));
const COLORREF CMPCTheme::CloseHoverColor = COLORREF(RGB(232, 17, 35));
const COLORREF CMPCTheme::ClosePushColor = COLORREF(RGB(139, 10, 20));

const COLORREF CMPCTheme::WindowBorderColorLight = COLORREF(RGB(99, 99, 99));
const COLORREF CMPCTheme::WindowBorderColorDim = COLORREF(RGB(43, 43, 43));
const COLORREF CMPCTheme::NoBorderColor = COLORREF(RGB(0, 0, 0));
const COLORREF CMPCTheme::GripperPatternColor = COLORREF(RGB(70, 70, 74)); //visual studio dark, since explorer has no grippers

const COLORREF CMPCTheme::ScrollBGColor = COLORREF(RGB(23, 23, 23));
const COLORREF CMPCTheme::ScrollChapterColor = COLORREF(RGB(60, 60, 60));
const COLORREF CMPCTheme::ScrollThumbColor = COLORREF(RGB(77, 77, 77));
const COLORREF CMPCTheme::ScrollThumbHoverColor = COLORREF(RGB(144, 144, 144));
const COLORREF CMPCTheme::ScrollThumbDragColor = COLORREF(RGB(183, 183, 183));
const COLORREF CMPCTheme::ScrollButtonArrowColor = COLORREF(RGB(103, 103, 103));
const COLORREF CMPCTheme::ScrollButtonHoverColor = COLORREF(RGB(55, 55, 55));
const COLORREF CMPCTheme::ScrollButtonClickColor = COLORREF(RGB(166, 166, 166));

const COLORREF CMPCTheme::InlineEditBorderColor = COLORREF(RGB(255, 255, 255));
const COLORREF CMPCTheme::TooltipBorderColor = COLORREF(RGB(118, 118, 118));

const COLORREF CMPCTheme::GroupBoxBorderColor = COLORREF(RGB(118, 118, 118));
const int CMPCTheme::GroupBoxTextIndent = 8;

const COLORREF CMPCTheme::PlayerButtonHotColor = COLORREF(RGB(43, 43, 43));
const COLORREF CMPCTheme::PlayerButtonCheckedColor = COLORREF(RGB(66, 66, 66)); 
const COLORREF CMPCTheme::PlayerButtonClickedColor = COLORREF(RGB(55, 55, 55));
const COLORREF CMPCTheme::PlayerButtonBorderColor = COLORREF(RGB(0, 0, 0));

const COLORREF CMPCTheme::DebugColorRed = COLORREF(RGB(255, 0, 0));
const COLORREF CMPCTheme::DebugColorYellow = COLORREF(RGB(255, 255, 0));
const COLORREF CMPCTheme::DebugColorGreen = COLORREF(RGB(0, 255, 0));

const COLORREF CMPCTheme::ButtonBorderOuterColor = COLORREF(RGB(240, 240, 240));
const COLORREF CMPCTheme::ButtonBorderInnerFocusedColor = COLORREF(RGB(255, 255, 255));
const COLORREF CMPCTheme::ButtonBorderInnerColor = COLORREF(RGB(155, 155, 155));
const COLORREF CMPCTheme::ButtonBorderSelectedKBFocusColor = COLORREF(RGB(150, 150, 150));
const COLORREF CMPCTheme::ButtonBorderHoverKBFocusColor = COLORREF(RGB(181, 181, 181));
const COLORREF CMPCTheme::ButtonBorderKBFocusColor = COLORREF(RGB(195, 195, 195));
const COLORREF CMPCTheme::ButtonFillColor = COLORREF(RGB(51, 51, 51));
const COLORREF CMPCTheme::ButtonFillHoverColor = COLORREF(RGB(69, 69, 69));
const COLORREF CMPCTheme::ButtonFillSelectedColor = COLORREF(RGB(102, 102, 102));
const COLORREF CMPCTheme::ButtonDisabledFGColor = COLORREF(RGB(109, 109, 109));

const COLORREF CMPCTheme::CheckboxBorderColor = COLORREF(RGB(137, 137, 137));
const COLORREF CMPCTheme::CheckboxBGColor = COLORREF(RGB(0, 0, 0));
const COLORREF CMPCTheme::CheckboxBorderHoverColor = COLORREF(RGB(121, 121, 121));
const COLORREF CMPCTheme::CheckboxBGHoverColor = COLORREF(RGB(8, 8, 8));

const COLORREF CMPCTheme::ImageDisabledColor = COLORREF(RGB(109, 109, 109));

const COLORREF CMPCTheme::SliderChannelColor = COLORREF(RGB(109, 109, 109));

const COLORREF CMPCTheme::EditBorderColor = COLORREF(RGB(106, 106, 106));

const COLORREF CMPCTheme::TreeCtrlLineColor = COLORREF(RGB(106, 106, 106));
const COLORREF CMPCTheme::TreeCtrlHoverColor = COLORREF(RGB(77, 77, 77));;
const COLORREF CMPCTheme::TreeCtrlFocusColor = COLORREF(RGB(98, 98, 98));;

const COLORREF CMPCTheme::CheckColor = COLORREF(RGB(222, 222, 222));;

const COLORREF CMPCTheme::ColumnHeaderHotColor = COLORREF(RGB(67, 67, 67));;

const COLORREF CMPCTheme::StaticEtchedColor = COLORREF(RGB(65, 65, 65));

const COLORREF CMPCTheme::ListCtrlDisabledBGColor = COLORREF(RGB(40, 40, 40));
const COLORREF CMPCTheme::ListCtrlGridColor = COLORREF(RGB(99, 99, 99));

const COLORREF CMPCTheme::TabCtrlBorderColor = COLORREF(RGB(99, 99, 99));
const COLORREF CMPCTheme::TabCtrlInactiveColor = COLORREF(RGB(40, 40, 40));


const COLORREF CMPCTheme::StatusBarBGColor = COLORREF(RGB(51, 51, 51));
const COLORREF CMPCTheme::StatusBarSeparatorColor = COLORREF(RGB(247, 247, 247));

const COLORREF CMPCTheme::W10DarkThemeFileDialogInjectedTextColor = COLORREF(RGB(255, 255, 255));
const COLORREF CMPCTheme::W10DarkThemeFileDialogInjectedBGColor = COLORREF(RGB(56, 56, 56));
const COLORREF CMPCTheme::W10DarkThemeFileDialogInjectedEditBorderColor = COLORREF(RGB(155, 155, 155));


const COLORREF CMPCTheme::ProgressBarBGColor = COLORREF(RGB(0, 0, 0));
const COLORREF CMPCTheme::ProgressBarColor = COLORREF(RGB(75, 75, 75));


wchar_t* const CMPCTheme::uiTextFont = L"Segoe UI";
wchar_t* const CMPCTheme::uiStaticTextFont = L"Segoe UI Semilight";
wchar_t* const CMPCTheme::uiSymbolFont = L"MS UI Gothic";


const int CMPCTheme::gripPatternLong = 5;
const int CMPCTheme::gripPatternShort = 4;

const BYTE CMPCTheme::GripperBitsH[10] = {
    0x80, 0x00,
    0x00, 0x00,
    0x20, 0x00,
    0x00, 0x00,
    0x80, 0x00,
};

const BYTE CMPCTheme::GripperBitsV[8] = {
    0x88, 0x00,
    0x00, 0x00,
    0x20, 0x00,
    0x00, 0x00,
};

const int CMPCTheme::scrollArrowLong = 7;
const int CMPCTheme::scrollArrowShort = 6;

const BYTE CMPCTheme::ScrollArrowBitsV[12] = {
    0x10, 0x00,
    0x38, 0x00,
    0x7C, 0x00,
    0xEE, 0x00,
    0xC6, 0x00,
    0x82, 0x00,
};
const BYTE CMPCTheme::ScrollArrowBitsH[14] = {
    0x1C, 0x00,
    0x38, 0x00,
    0x70, 0x00,
    0xE0, 0x00,
    0x70, 0x00,
    0x38, 0x00,
    0x1C, 0x00,
};

const BYTE CMPCTheme::ComboArrowBits[10] = {
    0x80, 0x40,
    0x40, 0x80,
    0x21, 0x00,
    0x12, 0x00,
    0x0C, 0x00,
};
const int CMPCTheme::ComboArrowWidth = 10;
const int CMPCTheme::ComboArrowHeight = 5;

const COLORREF CMPCTheme::ComboboxArrowColor[3] = {
    COLORREF(RGB(113, 113, 113)),
    COLORREF(RGB(173, 173, 173)),
    COLORREF(RGB(62, 62, 62)),
};

const COLORREF CMPCTheme::ComboboxArrowColorHover[3] = {
    COLORREF(RGB(123, 123, 123)),
    COLORREF(RGB(177, 177, 177)),
    COLORREF(RGB(78, 78, 78)),
};

const COLORREF CMPCTheme::ComboboxArrowColorClick[3] = {
    COLORREF(RGB(143, 143, 143)),
    COLORREF(RGB(183, 183, 183)),
    COLORREF(RGB(109, 109, 109)),
};

const BYTE CMPCTheme::SpinnerArrowBitsV[6] = {
    0x20, 0x00,
    0x70, 0x00,
    0xF8, 0x00,
};
const BYTE CMPCTheme::SpinnerArrowBitsH[10] = {
    0x20, 0x00,
    0x60, 0x00,
    0xE0, 0x00,
    0x60, 0x00,
    0x20, 0x00,
};

const int CMPCTheme::SpinnerArrowWidth = 5;
const int CMPCTheme::SpinnerArrowHeight = 3;

const BYTE CMPCTheme::CheckBits[14] = {
    0x02, 0x00,
    0x06, 0x00,
    0x8E, 0x00,
    0xDC, 0x00,
    0xF8, 0x00,
    0x70, 0x00,
    0x20, 0x00,
};

const int CMPCTheme::CheckWidth = 7;
const int CMPCTheme::CheckHeight = 7;


const UINT CMPCTheme::ThemeCheckBoxes[5] = {
    IDB_DT_CB_96,
    IDB_DT_CB_120,
    IDB_DT_CB_144,
    IDB_DT_CB_144,
    IDB_DT_CB_192,
};

const UINT CMPCTheme::ThemeRadios[5] = {
    IDB_DT_RADIO_96,
    IDB_DT_RADIO_120,
    IDB_DT_RADIO_144,
    IDB_DT_RADIO_144,
    IDB_DT_RADIO_192,
};

void CMPCTheme::getFontByFace(CFont &font, CDC *pDC, wchar_t *fontName, int size, LONG weight) {
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));

    lf.lfHeight = -MulDiv(size, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);
    lf.lfQuality = CLEARTYPE_QUALITY;

    //lf.lfQuality = ANTIALIASED_QUALITY;
    lf.lfWeight = weight;
    wcsncpy_s(lf.lfFaceName, fontName, LF_FACESIZE);

    font.CreateFontIndirect(&lf);
}

void CMPCTheme::getFontByType(CFont &font, CDC *pDC, int type, bool underline, bool bold) {
    themeMetrics tm = GetMetrics(pDC);
    NONCLIENTMETRICS &m = tm.ncMetrics;

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
        tlf.lfHeight = -MulDiv(8, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);
        tlf.lfQuality = CLEARTYPE_QUALITY;
        tlf.lfWeight = FW_REGULAR;
        wcsncpy_s(tlf.lfFaceName, m.lfMessageFont.lfFaceName, LF_FACESIZE);
        //wcsncpy_s(tlf.lfFaceName, _T("MS Shell Dlg"), LF_FACESIZE);
        lf = &tlf;
    } else if (type == CDFixedFont) {
        LOGFONT tlf;
        memset(&tlf, 0, sizeof(LOGFONT));
        tlf.lfHeight = -MulDiv(10, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);
        tlf.lfQuality = CLEARTYPE_QUALITY;
        tlf.lfWeight = FW_REGULAR;
        wcsncpy_s(tlf.lfFaceName, _T("Consolas"), LF_FACESIZE);
        lf = &tlf;
    } else {
        lf = &m.lfMessageFont;
    }
    if (underline || bold) {
        LOGFONT tlf;
        memset(&tlf, 0, sizeof(LOGFONT));
        tlf.lfHeight = lf->lfHeight;
        tlf.lfQuality = lf->lfQuality;
        tlf.lfWeight = lf->lfWeight;
        wcsncpy_s(tlf.lfFaceName, lf->lfFaceName, LF_FACESIZE);
        tlf.lfUnderline = underline;
        if (bold) tlf.lfWeight = FW_BOLD;
        font.CreateFontIndirect(&tlf);
    } else {
        font.CreateFontIndirect(lf);
    }
}

CSize CMPCTheme::GetTextSize(CString str, HDC hDC, int type) {
    CDC* pDC = CDC::FromHandle(hDC);
    CFont font;
    getFontByType(font, pDC, type);
    CFont* pOldFont = pDC->SelectObject(&font);

    CSize cs = pDC->GetTextExtent(str);

    pDC->SelectObject(pOldFont);

    return cs;
}

CSize CMPCTheme::GetTextSizeDiff(CString str, HDC hDC, int type, CFont * curFont) {
    CSize cs = GetTextSize(str, hDC, type);
    CDC* cDC = CDC::FromHandle(hDC);
    CFont* pOldFont = cDC->SelectObject(curFont);
    CSize curCs = cDC->GetTextExtent(str);
    cDC->SelectObject(pOldFont);

    return cs - curCs;
}

bool CMPCTheme::haveMetrics = false;
CMPCTheme::themeMetrics CMPCTheme::_metrics = CMPCTheme::themeMetrics();
CMPCTheme::themeMetrics & CMPCTheme::GetMetrics(CDC *pDC) {
    if (!haveMetrics) {
        _metrics.ncMetrics.cbSize = sizeof(NONCLIENTMETRICS);
        ::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &CMPCTheme::_metrics.ncMetrics, 0);
        /*
        _metrics.checkboxWidth = 12 * pDC->GetDeviceCaps(LOGPIXELSX) / 96 + 1;
        _metrics.checkboxHeight = 12 * pDC->GetDeviceCaps(LOGPIXELSY) / 96 + 1;
        */
        CPngImage image;
        image.Load(getResourceByDPI(pDC, ThemeCheckBoxes), AfxGetInstanceHandle());
        BITMAP bm;
        image.GetBitmap(&bm);
        _metrics.checkboxWidth = bm.bmHeight;
        _metrics.checkboxHeight = bm.bmHeight;


        haveMetrics = true;
    }
    return CMPCTheme::_metrics;
}

void CMPCTheme::initMemDC(CDC * pDC, CDC &dcMem, CBitmap &bmMem, CRect rect) {
    dcMem.CreateCompatibleDC(pDC);
    dcMem.SetBkColor(pDC->GetBkColor());
    dcMem.SetTextColor(pDC->GetTextColor());
    dcMem.SetBkMode(pDC->GetBkMode());
    dcMem.SelectObject(pDC->GetCurrentFont());

    bmMem.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
    dcMem.SelectObject(&bmMem);
    dcMem.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rect.left, rect.top, SRCCOPY);
}

void CMPCTheme::flushMemDC(CDC * pDC, CDC &dcMem, CRect rect) {
    pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY);
}


void CMPCTheme::DrawBufferedText(CDC * pDC, CString text, CRect rect, UINT format) {
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

void CMPCTheme::Draw2BitTransparent(CDC & dc, int left, int top, int width, int height, CBitmap &bmp, COLORREF fgColor) {
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

void CMPCTheme::dbg(CString text, ...) {
    va_list args;
    va_start(args, text);
    CString output;
    output.FormatV(text, args);
    OutputDebugString(output);
    OutputDebugString(_T("\n"));
    va_end(args);
}

UINT CMPCTheme::getResourceByDPI(CDC *pDC, const UINT *resources) {
    int index;
    int dpi = pDC->GetDeviceCaps(LOGPIXELSX);
    if (dpi < 120) index = 0;
    else if (dpi < 144) index = 1;
    else if (dpi < 168) index = 2;
    else if (dpi < 196) index = 3;
    else index = 4;

    return resources[index];
}

void CMPCTheme::drawCheckBox(UINT checkState, bool isHover, bool useSystemSize, CRect rectCheck, CDC *pDC, bool isRadio) {
    COLORREF borderClr, bgClr;
    COLORREF oldBkClr = pDC->GetBkColor(), oldTextClr = pDC->GetTextColor();
    if (isHover) {
        borderClr = CMPCTheme::CheckboxBorderHoverColor;
        bgClr = CMPCTheme::CheckboxBGHoverColor;
    } else {
        borderClr = CMPCTheme::CheckboxBorderColor;
        bgClr = CMPCTheme::CheckboxBGColor;
    }

    if (useSystemSize) {
        CPngImage image;
        image.Load(getResourceByDPI(pDC, isRadio ? ThemeRadios : ThemeCheckBoxes), AfxGetInstanceHandle());
        BITMAP bm;
        image.GetBitmap(&bm);
        int size = bm.bmHeight;

        CDC mDC;
        mDC.CreateCompatibleDC(pDC);
        mDC.SelectObject(image);
        int index;
        if (isRadio) {
            index = RadioRegular;
            if (checkState) index += 1;
            if (isHover) index += 2;
        } else {
            index = CheckBoxRegular;
            if (isHover) index += 1;
        }
        CRect drawRect(0, 0, size, size);
        //drawRect.OffsetRect(rectCheck.left + (rectCheck.Width() - size) / 2, rectCheck.top + (rectCheck.Height() - size) / 2);
        drawRect.OffsetRect(rectCheck.left, rectCheck.top + (rectCheck.Height() - size) / 2);

        if (!isRadio && checkState != BST_CHECKED) { //we can draw this w/o BMPs
            CBrush brush(borderClr);
            pDC->FrameRect(drawRect, &brush);
            drawRect.DeflateRect(1, 1);
            pDC->FillSolidRect(drawRect, bgClr);
            if (checkState == BST_INDETERMINATE) {
                drawRect.DeflateRect(2, 2);
                pDC->FillSolidRect(drawRect, CMPCTheme::TextFGColor);
            }
        } else {
            int left = index * size;
            pDC->BitBlt(drawRect.left, drawRect.top, drawRect.Width(), drawRect.Height(), &mDC, left, 0, SRCCOPY);
        }
    } else {
        CBrush brush(borderClr);
        pDC->FrameRect(rectCheck, &brush);
        rectCheck.DeflateRect(1, 1);
        pDC->FillSolidRect(rectCheck, bgClr);
        if (checkState) {
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

bool CMPCTheme::canUseWin10DarkTheme() {
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        //return false; //FIXME.  return false to test behavior for OS < Win10
        return IsWindows10OrGreater();
    }
    return false;
}

UINT CMPCTheme::defaultLogo() {
    return IDF_LOGO4;
}

struct AFX_CTLCOLOR {
    HWND hWnd;
    HDC hDC;
    UINT nCtlType;
};

void CMPCTheme::fillParentDialogBGClr(CWnd* wnd, CDC *pDC, CRect r) {
    CBrush brush;
    WPARAM w = (WPARAM)pDC;
    AFX_CTLCOLOR ctl;
    ctl.hWnd = wnd->GetSafeHwnd();
    ctl.nCtlType = CTLCOLOR_DLG;
    ctl.hDC = pDC->GetSafeHdc();
    CWnd *parent = wnd->GetParent();
    if (nullptr == parent) {
        parent = wnd;
    }
    HBRUSH bg = (HBRUSH)parent->SendMessage(WM_CTLCOLORDLG, w, (LPARAM)& ctl);
    brush.Attach(bg);
    pDC->FillRect(r, &brush);
    brush.Detach();
}

void CMPCTheme::fulfillThemeReqs(CProgressCtrl* ctl) {
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        SetWindowTheme(ctl->GetSafeHwnd(), _T(""), _T(""));
        ctl->SetBarColor(CMPCTheme::ProgressBarColor);
        ctl->SetBkColor(CMPCTheme::ProgressBarBGColor);
    }
    ctl->UpdateWindow();
}
