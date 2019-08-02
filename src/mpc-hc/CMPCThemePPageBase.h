#pragma once
#include "PPageBase.h"
#include "CMPCThemeButton.h"
#include "CMPCThemeUtil.h"
class CMPCThemePPageBase :
	public CPPageBase, public CMPCThemeUtil
{
    DECLARE_DYNAMIC(CMPCThemePPageBase)
public:
    CMPCThemePPageBase(UINT nIDTemplate, UINT nIDCaption);
    virtual ~CMPCThemePPageBase();
    void fulfillThemeReqs() { CMPCThemeUtil::fulfillThemeReqs((CWnd*)this); };

    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
    virtual BOOL OnInitDialog();
    void SetButtonIcon(UINT nIDButton, UINT nIDIcon); //non-virtual override, only used internally
};

