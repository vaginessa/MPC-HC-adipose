#include "stdafx.h"
#include "CDarkTheme.h"

const COLORREF CDarkTheme::DarkBGColor = COLORREF(RGB(43, 43, 43));
const COLORREF CDarkTheme::DarkShadowColor = COLORREF(RGB(25, 25, 25));
const COLORREF CDarkTheme::DarkSelectedColor = COLORREF(RGB(65, 65, 65));
const COLORREF CDarkTheme::DarkTextFGColor = COLORREF(RGB(255, 255, 255));
const COLORREF CDarkTheme::DarkSubmenuColor = COLORREF(RGB(191, 191, 191));
const COLORREF CDarkTheme::DarkMenuSeparatorColor = COLORREF(RGB(128, 128, 128));
const COLORREF CDarkTheme::DarkDisabledColor = COLORREF(RGB(109, 109, 109));
const COLORREF CDarkTheme::DarkLightColor = COLORREF(RGB(100, 100, 100));
const COLORREF CDarkTheme::DarkDebugColor = COLORREF(RGB(255, 0, 0));
const COLORREF CDarkTheme::DarkDebugColor2 = COLORREF(RGB(255, 255, 0));
const COLORREF CDarkTheme::DarkCloseHoverColor = COLORREF(RGB(232, 17, 35));
const COLORREF CDarkTheme::DarkClosePushColor = COLORREF(RGB(139, 10, 20));
const COLORREF CDarkTheme::NoBorderColor = COLORREF(RGB(0, 0, 0));
const COLORREF CDarkTheme::GripperPatternColor = COLORREF(RGB(70, 70, 74)); //visual studio dark, since explorer has no grippers



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
    0x00, 0x00
};
