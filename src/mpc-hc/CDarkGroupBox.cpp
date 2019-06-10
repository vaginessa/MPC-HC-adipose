#include "stdafx.h"
#include "CDarkGroupBox.h"
#include "CDarkTheme.h"

IMPLEMENT_DYNAMIC(CDarkGroupBox, CStatic)

CDarkGroupBox::CDarkGroupBox() {

}


CDarkGroupBox::~CDarkGroupBox() {
}

BEGIN_MESSAGE_MAP(CDarkGroupBox, CStatic)
    ON_WM_NCPAINT()
    ON_WM_PAINT()
END_MESSAGE_MAP()


void CDarkGroupBox::OnNcPaint() {
    // TODO: Add your message handler code here
    // Do not call CStatic::OnNcPaint() for painting messages
}


void CDarkGroupBox::OnPaint() {
    CPaintDC dc(this);

    CRect r, rborder, rtext;
    GetClientRect(r);
    HDC hDC = ::GetDC(NULL);
    CString text;
    GetWindowText(text);
    CSize cs = CDarkTheme::GetTextSize(text, hDC, CDarkTheme::CDCaptionFont);

    CBrush fb;
    fb.CreateSolidBrush(CDarkTheme::GroupBoxBorderColor);
    rborder = r;
    rborder.top += cs.cy / 2;
    dc.FrameRect(rborder, &fb);

    COLORREF oldClr = dc.SetTextColor(CDarkTheme::TextFGColor);
    COLORREF oldBkClr = dc.SetBkColor(CDarkTheme::ContentBGColor);
    //CFont *font = CDarkTheme::getUIFont(dc.GetSafeHdc(), CDarkTheme::uiTextFont, 8);
    CFont font;
    CDarkTheme::getUIFont(font, dc.GetSafeHdc(), CDarkTheme::CDCaptionFont);
    CFont* pOldFont = dc.SelectObject(&font);

    rtext = r;
    rtext.left += CDarkTheme::GroupBoxTextIndent;

    dc.DrawText(text, rtext, DT_TOP | DT_LEFT | DT_SINGLELINE | DT_EDITCONTROL);

    dc.SelectObject(pOldFont);
    dc.SetTextColor(oldClr);
    dc.SetBkColor(oldBkClr);
}
