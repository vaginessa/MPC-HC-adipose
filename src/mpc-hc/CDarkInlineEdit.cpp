#include "stdafx.h"
#include "CDarkInlineEdit.h"
#include "CDarkTheme.h"

CDarkInlineEdit::CDarkInlineEdit() {
    m_brBkgnd.CreateSolidBrush(CDarkTheme::InlineEditBorderColor);
}


CDarkInlineEdit::~CDarkInlineEdit() {
}
BEGIN_MESSAGE_MAP(CDarkInlineEdit, CEdit)
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


HBRUSH CDarkInlineEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/) {
    pDC->SetTextColor(CDarkTheme::TextFGColor);
    pDC->SetBkColor(CDarkTheme::ContentBGColor);
    return m_brBkgnd;
}
