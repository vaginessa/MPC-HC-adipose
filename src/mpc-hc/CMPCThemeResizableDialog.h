#pragma once
#include "CMPCThemeResizableDialog.h"
#include "CDarkButton.h"
#include "CDarkGroupBox.h"
#include "CDarkLinkCtrl.h"
#include "CDarkChildHelper.h"
class CMPCThemeResizableDialog : public CResizableDialog, public CDarkChildHelper
{
public:
	CMPCThemeResizableDialog();
    CMPCThemeResizableDialog(UINT nIDTemplate, CWnd* pParent = nullptr);
    CMPCThemeResizableDialog(LPCTSTR lpszTemplateName, CWnd* pParent = nullptr);
    virtual ~CMPCThemeResizableDialog();
    void enableDarkThemeIfActive() { CDarkChildHelper::enableDarkThemeIfActive((CWnd*)this); };
    DECLARE_MESSAGE_MAP()
public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

