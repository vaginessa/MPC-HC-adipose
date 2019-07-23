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
    static const COLORREF ContentTextDisabledFGColorWarn;
    static const COLORREF ContentTextDisabledFGColorFade;
    static const COLORREF ContentTextDisabledFGColorFade2;
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

    static const COLORREF ColumnHeaderHotColor;

    static const COLORREF StaticEtchedColor;

    static const COLORREF ListCtrlDisabledBGColor;
    static const COLORREF ListCtrlGridColor;

    static const COLORREF TabCtrlBorderColor;
    static const COLORREF TabCtrlInactiveColor;

    static const COLORREF StatusBarBGColor;
    static const COLORREF StatusBarSeparatorColor;
    static const COLORREF StatusBarEditBorderColor;

    static const COLORREF W10DarkThemeFileDialogInjectedTextColor;
    static const COLORREF W10DarkThemeFileDialogInjectedBGColor;
    static const COLORREF W10DarkThemeFileDialogInjectedBGColorEditBorderColor;

    static const COLORREF ProgressBarBGColor;
    static const COLORREF ProgressBarColor;

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

    static const BYTE SpinnerArrowBitsV[6];
    static const BYTE SpinnerArrowBitsH[10];
    static const int SpinnerArrowWidth;
    static const int SpinnerArrowHeight;

    static const BYTE CheckBits[14];
    static const int CheckWidth;
    static const int CheckHeight;

    static void getFontByFace(CFont &font, CDC *pDC, wchar_t *fontName, int size, LONG weight = FW_REGULAR);
    static void getFontByType(CFont &font, CDC *pDC, int type, bool underline = false, bool bold = false);
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


    struct themeMetrics {
        NONCLIENTMETRICS ncMetrics;
        CSize avgCharSize;
        int checkboxWidth;
        int checkboxHeight;
    };

    static themeMetrics _metrics;
    static bool haveMetrics;
    static themeMetrics & GetMetrics(CDC * pDC);
    static void initMemDC(CDC * pDC, CDC & dcMem, CBitmap & bmMem, CRect rect);
    static void flushMemDC(CDC * pDC, CDC & dcMem, CRect rect);
    static void DrawBufferedText(CDC* pDC, CString text, CRect rect, UINT format);
    static void Draw2BitTransparent(CDC &dc, int left, int top, int width, int height, CBitmap &bmp, COLORREF fgColor);
    static void dbg(CString text, ...);
    static UINT getResourceByDPI(CDC *pDC, const UINT * resources);
    static void drawCheckBox(UINT checkState, bool isHover, bool useSystemSize, CRect rectCheck, CDC *pDC, bool isRadio=false);
    static bool canUseWin10DarkTheme();
    static UINT defaultLogo();

    enum CheckBoxStyle {
        CheckBoxRegular = 0,
        CheckBoxHover = 1,
    };

    enum RadoStyle {
        RadioRegular = 0,
        RadioRegularSet = 1,
        RadioHover = 2,
        RadioHoverSet = 3
    };

    const static UINT ThemeCheckBoxes[5];
    const static UINT ThemeRadios[5];
};
