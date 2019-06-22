#pragma once
#include "stdafx.h"
#include "VersionHelpersInternal.h"
#include "mplayerc.h"
#undef SubclassWindow

class CDarkTheme {
public:
    static const COLORREF MenuBGColor;
    static const COLORREF WindowBGColor;  //used in explorer for left nav
    static const COLORREF ControlAreaBGColor;  //used in file open dialog for button / file selection bg
    static const COLORREF ContentBGColor; //used in explorer for bg of file list
    static const COLORREF ContentSelectedColor; //used in explorer for bg of file list
    static const COLORREF PlayerBGColor;
    static const COLORREF HighLightColor;

    static const COLORREF MenuSelectedColor;
    static const COLORREF MenuItemDisabledColor;
    static const COLORREF MenuSeparatorColor;

    static const COLORREF ShadowColor;
    static const COLORREF TextFGColor;
    static const COLORREF ContentTextDisabledFGColor;
    static const COLORREF SubmenuColor;
    static const COLORREF LightColor;
    static const COLORREF CloseHoverColor;
    static const COLORREF ClosePushColor;
    static const COLORREF WindowBorderColorLight;
    static const COLORREF WindowBorderColorDim;
    static const COLORREF NoBorderColor;
    static const COLORREF GripperPatternColor;

    static const COLORREF ScrollBGColor;
    static const COLORREF ScrollThumbColor;
    static const COLORREF ScrollThumbHoverColor;
    static const COLORREF ScrollThumbDragColor;
    static const COLORREF ScrollButtonArrowColor;
    static const COLORREF ScrollButtonHoverColor;
    static const COLORREF ScrollButtonClickColor;

    static const COLORREF InlineEditBorderColor;
    static const COLORREF TooltipBorderColor;

    static const COLORREF GroupBoxBorderColor;
    static const int GroupBoxTextIndent;

    static const COLORREF DebugColorRed;
    static const COLORREF DebugColorYellow;
    static const COLORREF DebugColorGreen;

    static const COLORREF PlayerButtonHotColor;
    static const COLORREF PlayerButtonCheckedColor;
    static const COLORREF PlayerButtonClickedColor;
    static const COLORREF PlayerButtonBorderColor;

    static const COLORREF ButtonBorderOuterColor;
    static const COLORREF ButtonBorderInnerFocusedColor;
    static const COLORREF ButtonBorderInnerColor;
    static const COLORREF ButtonBorderSelectedKBFocusColor;
    static const COLORREF ButtonBorderHoverKBFocusColor;
    static const COLORREF ButtonBorderKBFocusColor;
    static const COLORREF ButtonFillColor;
    static const COLORREF ButtonFillHoverColor;
    static const COLORREF ButtonFillSelectedColor;
    static const COLORREF ButtonDisabledFGColor;

    static const COLORREF CheckboxBorderColor;
    static const COLORREF CheckboxBGColor;
    static const COLORREF CheckboxBorderHoverColor;
    static const COLORREF CheckboxBGHoverColor;

    static const COLORREF ImageDisabledColor;

    static const COLORREF SliderChannelColor;

    static const COLORREF EditBorderColor;

    static const COLORREF TreeCtrlLineColor;
    static const COLORREF TreeCtrlHoverColor;
    static const COLORREF TreeCtrlFocusColor;

    static const COLORREF CheckColor;

    static const COLORREF CDarkTheme::ColumnHeaderHotColor;

    static const BYTE GripperBitsH[10];
    static const BYTE GripperBitsV[8];
    static const int gripPatternShort;
    static const int gripPatternLong;

    static wchar_t* const uiTextFont;
    static wchar_t* const uiStaticTextFont;
    static wchar_t* const uiSymbolFont;

    static const BYTE ScrollArrowBitsV[12];
    static const BYTE ScrollArrowBitsH[14];
    static const int scrollArrowShort;
    static const int scrollArrowLong;

    static const BYTE ComboArrowBits[10];
    static const int ComboArrowWidth;
    static const int ComboArrowHeight;

    static const COLORREF ComboboxArrowColor[3];
    static const COLORREF ComboboxArrowColorHover[3];
    static const COLORREF ComboboxArrowColorClick[3];

    static const BYTE SpinnerArrowBits[6];
    static const int SpinnerArrowWidth;
    static const int SpinnerArrowHeight;

    static const BYTE CheckBits[14];
    static const int CheckWidth;
    static const int CheckHeight;

    static void getUIFont(CFont &font, HDC hDC, wchar_t *fontName, int size, LONG weight = FW_REGULAR);
    static void getUIFont(CFont &font, HDC hDC, int type);
    enum fontType {
        CDCaptionFont,
        CDSmallCaptionFont,
        CDMenuFont,
        CDStatusFont,
        CDMessageFont,
        CDDialogFont,
    };

    static CSize GetTextSize(CString str, HDC hDC, int type);
    static CSize GetTextSizeDiff(CString str, HDC hDC, int type, CFont *curFont);

    static NONCLIENTMETRICS _metrics;
    static bool haveMetrics;
    static NONCLIENTMETRICS& GetMetrics();
    static void DrawBufferedText(CDC* pDC, CString text, CRect rect, UINT format);
    static void Draw2BitTransparent(CDC &dc, int left, int top, int width, int height, CBitmap &bmp, COLORREF fgColor);
    static void dbg(CString text, ...);
    static void drawCheckBox(bool isChecked, bool isHover, bool useImage, CRect rectCheck, CDC *pDC);
    static bool canUseWin10DarkTheme();
};
