#pragma once
#include "ComPropertyPage.h"
#include "CDarkChildHelper.h"
class CMPCThemeComPropertyPage : public CComPropertyPage, public CDarkChildHelper {
public:
    CMPCThemeComPropertyPage(IPropertyPage* pPage);
    virtual ~CMPCThemeComPropertyPage();


    void enableDarkThemeIfActive() { CDarkChildHelper::fulfillThemeReqs((CWnd*)this); };
    DECLARE_DYNAMIC(CMPCThemeComPropertyPage)

    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
    virtual BOOL OnInitDialog();

};

