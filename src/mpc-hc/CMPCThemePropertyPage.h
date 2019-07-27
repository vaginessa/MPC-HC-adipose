#pragma once
#include "CDarkChildHelper.h"
class CMPCThemePropertyPage : public CPropertyPage, public CDarkChildHelper {
public:
    CMPCThemePropertyPage(UINT nIDTemplate, UINT nIDCaption);
    virtual ~CMPCThemePropertyPage();


    void enableDarkThemeIfActive() { CDarkChildHelper::enableDarkThemeIfActive((CWnd*)this); };
    DECLARE_DYNAMIC(CMPCThemePropertyPage)

    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
    virtual BOOL OnInitDialog();

};

