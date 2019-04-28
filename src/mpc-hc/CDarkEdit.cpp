#include "stdafx.h"
#include "CDarkEdit.h"
#include "CDarkTheme.h"

CDarkEdit::CDarkEdit() {
}


CDarkEdit::~CDarkEdit() {
    m_brBkgnd.DeleteObject();
}
BEGIN_MESSAGE_MAP(CDarkEdit, CEdit)
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


HBRUSH CDarkEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/) {
    m_brBkgnd.DeleteObject();
    m_brBkgnd.CreateSolidBrush(CDarkTheme::EditBorderColor);
    pDC->SetTextColor(CDarkTheme::TextFGColor);
    pDC->SetBkColor(CDarkTheme::ContentBGColor);
    return m_brBkgnd;
}
