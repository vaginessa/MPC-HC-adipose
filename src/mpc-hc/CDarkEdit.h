#pragma once
#include <afxwin.h>
class CDarkEdit :
	public CEdit
{
public:
	CDarkEdit();
	~CDarkEdit();
    CBrush   m_brBkgnd;
    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};

