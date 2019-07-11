#include "stdafx.h"
#include "CMPCThemeCmdUIDialog.h"
#include "CDarkTheme.h"
#include "mplayerc.h"


CMPCThemeCmdUIDialog::CMPCThemeCmdUIDialog() {
}

CMPCThemeCmdUIDialog::CMPCThemeCmdUIDialog(UINT nIDTemplate, CWnd* pParent):CCmdUIDialog(nIDTemplate, pParent){
}

CMPCThemeCmdUIDialog::CMPCThemeCmdUIDialog(LPCTSTR lpszTemplateName, CWnd* pParent):CCmdUIDialog(lpszTemplateName, pParent) {
}


CMPCThemeCmdUIDialog::~CMPCThemeCmdUIDialog() {
}

BEGIN_MESSAGE_MAP(CMPCThemeCmdUIDialog, CCmdUIDialog)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


HBRUSH CMPCThemeCmdUIDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        return DarkCtlColor(pDC, pWnd, nCtlColor);
    } else {
        HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);
        return hbr;
    }
}
