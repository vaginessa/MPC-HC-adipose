#pragma once
#include "MessageBoxDialog/MessageBoxDialog.h"
#include "CDarkChildHelper.h"

class CMPCThemeMsgBox : public CMessageBoxDialog, public CDarkChildHelper
{
public:
    CMPCThemeMsgBox(CWnd* pParent, CString strMessage, CString strTitle = _T(""), UINT nStyle = MB_OK, UINT nHelp = 0);
    CMPCThemeMsgBox(CWnd* pParent, UINT nMessageID, UINT nTitleID = 0, UINT nStyle = MB_OK, UINT nHelp = 0);
    DECLARE_DYNAMIC(CMPCThemeMsgBox)
    virtual ~CMPCThemeMsgBox();
    BOOL OnInitDialog();
    void enableDarkThemeIfActive() { CDarkChildHelper::enableDarkThemeIfActive((CWnd*)this); };
    static BOOL MessageBox(CWnd * parent, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

