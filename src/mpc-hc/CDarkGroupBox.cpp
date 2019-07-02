#include "stdafx.h"
#include "CDarkGroupBox.h"
#include "CDarkTheme.h"

IMPLEMENT_DYNAMIC(CDarkGroupBox, CStatic)

CDarkGroupBox::CDarkGroupBox() {

}


CDarkGroupBox::~CDarkGroupBox() {
}

BEGIN_MESSAGE_MAP(CDarkGroupBox, CStatic)
    ON_WM_PAINT()
END_MESSAGE_MAP()


void CDarkGroupBox::OnPaint() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {

        CPaintDC dc(this);

        CRect r, rborder, rtext;
        GetClientRect(r);
        HDC hDC = ::GetDC(NULL);
        CString text;
        GetWindowText(text);

        CBrush fb;
        fb.CreateSolidBrush(CDarkTheme::GroupBoxBorderColor);
        rborder = r;

        CSize cs = CDarkTheme::GetTextSize(_T("W"), hDC, CDarkTheme::CDCaptionFont);
        rborder.top += cs.cy / 2;
        dc.FrameRect(rborder, &fb);
        if (!text.IsEmpty()) {

            COLORREF oldClr = dc.SetTextColor(CDarkTheme::TextFGColor);
            COLORREF oldBkClr = dc.SetBkColor(CDarkTheme::ContentBGColor);
            //CFont *font = CDarkTheme::getUIFont(dc.GetSafeHdc(), CDarkTheme::uiTextFont, 8);
            CFont font;
            CDarkTheme::getUIFont(font, &dc, CDarkTheme::CDCaptionFont);
            CFont* pOldFont = dc.SelectObject(&font);

            rtext = r;
            rtext.left += CDarkTheme::GroupBoxTextIndent;

            text += _T(" "); //seems to be the default behavior
            dc.DrawText(text, rtext, DT_TOP | DT_LEFT | DT_SINGLELINE | DT_EDITCONTROL);

            dc.SelectObject(pOldFont);
            dc.SetTextColor(oldClr);
            dc.SetBkColor(oldBkClr);
        }

    } else {
        __super::OnPaint();
    }
}
