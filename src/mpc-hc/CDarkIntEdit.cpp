#include "stdafx.h"
#include "CDarkIntEdit.h"
#include "FloatEdit.h"

CDarkIntEdit::CDarkIntEdit() {
}


CDarkIntEdit::~CDarkIntEdit() {
}

IMPLEMENT_DYNAMIC(CDarkIntEdit, CDarkEdit)

BEGIN_MESSAGE_MAP(CDarkIntEdit, CDarkEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()

void CDarkIntEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
    //ok, this is cheating, but a CIntEdit has only one unique function from a CEdit!
    //saves subclassing it directly and inheriting from CDarkEdit
    ((CIntEdit*)this)->OnChar(nChar, nRepCnt, nFlags); 
}
