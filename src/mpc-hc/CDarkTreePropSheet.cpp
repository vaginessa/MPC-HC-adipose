#include "stdafx.h"
#include "CDarkTreePropSheet.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

CDarkTreePropSheet::CDarkTreePropSheet() {
    darkBrush.CreateSolidBrush(CDarkTheme::ContentBGColor);
}

CDarkTreePropSheet::CDarkTreePropSheet(LPCTSTR pszCaption, CWnd * pParentWnd, UINT iSelectPage)
: TreePropSheet::CTreePropSheet(pszCaption, pParentWnd, iSelectPage) {
}


CDarkTreePropSheet::~CDarkTreePropSheet() {
}

IMPLEMENT_DYNAMIC(CDarkTreePropSheet, TreePropSheet::CTreePropSheet)
BEGIN_MESSAGE_MAP(CDarkTreePropSheet, CTreePropSheet)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


HBRUSH CDarkTreePropSheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        pDC->SetTextColor(CDarkTheme::TextFGColor);
        pDC->SetBkColor(CDarkTheme::ContentBGColor);
        return darkBrush;
    } else {
        HBRUSH hbr = CTreePropSheet::OnCtlColor(pDC, pWnd, nCtlColor);
        return hbr;
    }
}
