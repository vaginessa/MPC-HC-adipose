#pragma once
#include "TreePropSheet\TreePropSheet.h"
class CDarkTreePropSheet :
    public TreePropSheet::CTreePropSheet
{
public:
	CDarkTreePropSheet();
    CDarkTreePropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    CBrush darkBrush;
    virtual ~CDarkTreePropSheet();
    DECLARE_DYNAMIC(CDarkTreePropSheet);
    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

