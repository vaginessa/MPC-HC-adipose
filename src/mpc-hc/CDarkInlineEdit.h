#pragma once
#include <afxwin.h>
class CDarkInlineEdit :
	public CEdit
{
public:
	CDarkInlineEdit();
	virtual ~CDarkInlineEdit();
    CBrush m_brBkgnd;
    DECLARE_MESSAGE_MAP()
    afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};

