#pragma once
#include <afxwin.h>
#include "CDarkButton.h"
#include "CDarkGroupBox.h"
#include "CDarkLinkCtrl.h"
#include "CDarkChildHelper.h"

class CDarkDialog :
	public CDialog, public CDarkChildHelper
{
public:
	CDarkDialog();
    explicit CDarkDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
    virtual ~CDarkDialog();
    void enableDarkThemeIfActive() { CDarkChildHelper::enableDarkThemeIfActive((CWnd*)this); };
    DECLARE_MESSAGE_MAP()
public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

