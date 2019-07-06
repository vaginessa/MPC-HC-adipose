#include "stdafx.h"
#include "CDarkDialog.h"
#include "CDarkTheme.h"
#include "mplayerc.h"
#undef SubclassWindow


CDarkDialog::CDarkDialog() {
}

CDarkDialog::CDarkDialog(UINT nIDTemplate, CWnd * pParentWnd) : CDialog(nIDTemplate, pParentWnd) {
}


CDarkDialog::~CDarkDialog() {
}



BEGIN_MESSAGE_MAP(CDarkDialog, CDialog)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


HBRUSH CDarkDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        return DarkCtlColor(pDC, pWnd, nCtlColor);
    } else {
        HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
        return hbr;
    }
}
