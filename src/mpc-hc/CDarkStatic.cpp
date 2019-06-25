#include "stdafx.h"
#include "CDarkStatic.h"
#include "CDarkTheme.h"

CDarkStatic::CDarkStatic() {
}


CDarkStatic::~CDarkStatic() {
}
IMPLEMENT_DYNAMIC(CDarkStatic, CStatic)
BEGIN_MESSAGE_MAP(CDarkStatic, CStatic)
    ON_WM_PAINT()
    ON_WM_NCPAINT()
END_MESSAGE_MAP()


void CDarkStatic::OnPaint() {
    __super::OnPaint();
}


void CDarkStatic::OnNcPaint() {
    if (GetStyle() & SS_ETCHEDFRAME) {
        CDC* pDC = GetWindowDC();

        CRect rect;
        GetWindowRect(&rect);
        rect.OffsetRect(-rect.left, -rect.top);
        rect.DeflateRect(0, 0, 1, 1) ; //make it thinner
        //CBrush brush(CDarkTheme::StaticEtchedColor);
        pDC->FillSolidRect(rect, CDarkTheme::StaticEtchedColor);
    } else {
        CStatic::OnNcPaint();
    }
}
