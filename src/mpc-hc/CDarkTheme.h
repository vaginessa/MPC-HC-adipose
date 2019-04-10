#pragma once
#include "stdafx.h"

class CDarkTheme {
public:
    static const COLORREF DarkBGColor;
    static const COLORREF DarkShadowColor;
    static const COLORREF DarkSelectedColor;
    static const COLORREF DarkTextFGColor;
    static const COLORREF DarkSubmenuColor;
    static const COLORREF DarkDisabledColor;
    static const COLORREF DarkLightColor;
    static const COLORREF DarkDebugColor;
    static const COLORREF DarkDebugColor2;
    static const COLORREF DarkMenuSeparatorColor;
    static const COLORREF DarkCloseHoverColor;
    static const COLORREF DarkClosePushColor;
    static const COLORREF NoBorderColor;
    static const COLORREF GripperPatternColor;

    static const BYTE GripperBitsH[10];
    static const BYTE GripperBitsV[8];
    static const int gripPatternLong;
    static const int gripPatternShort;
};
