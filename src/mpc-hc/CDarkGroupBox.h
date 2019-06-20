#pragma once
#include <afxwin.h>
class CDarkGroupBox :
	public CStatic
{
    DECLARE_DYNAMIC(CDarkGroupBox)
public:
	CDarkGroupBox();
	virtual ~CDarkGroupBox();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
    afx_msg void OnPaint();
};

