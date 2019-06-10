#include "stdafx.h"
#include "CDarkLinkCtrl.h"
#include "CDarkTheme.h"


CDarkLinkCtrl::CDarkLinkCtrl() {

}


CDarkLinkCtrl::~CDarkLinkCtrl() {
}
BEGIN_MESSAGE_MAP(CDarkLinkCtrl, CLinkCtrl)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


HBRUSH CDarkLinkCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    HBRUSH hbr = CLinkCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

    pDC->SetTextColor(CDarkTheme::TextFGColor);
    return hbr;
}

void CDarkLinkCtrl::PreSubclassWindow() {
    LITEM item = { 0 };
    item.mask = LIF_ITEMINDEX | LIF_STATE;
    item.state = LIS_DEFAULTCOLORS;
    item.stateMask = LIS_DEFAULTCOLORS;
    SetItem(&item);
}
