#pragma once
#include "PPageBase.h"
#include "CDarkButton.h"
#include "CDarkChildHelper.h"
class CDarkPPageBase :
	public CPPageBase, public CDarkChildHelper
{
    DECLARE_DYNAMIC(CDarkPPageBase)
public:
    CDarkPPageBase(UINT nIDTemplate, UINT nIDCaption);
    virtual ~CDarkPPageBase();
    void enableDarkThemeIfActive() { CDarkChildHelper::fulfillThemeReqs((CWnd*)this); };

    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
    virtual BOOL OnInitDialog();
    void SetDarkButtonIcon(UINT nIDButton, UINT nIDIcon);
};

