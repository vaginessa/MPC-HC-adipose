#pragma once
#include <afxcmn.h>
class CDarkLinkCtrl :
	public CLinkCtrl
{
public:
	CDarkLinkCtrl();
	virtual ~CDarkLinkCtrl();
    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    virtual void PreSubclassWindow();
};

