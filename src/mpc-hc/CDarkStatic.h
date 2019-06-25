#pragma once
#include <afxwin.h>
class CDarkStatic :
	public CStatic
{
    DECLARE_DYNAMIC(CDarkStatic)
public:

	CDarkStatic();
	virtual ~CDarkStatic();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    afx_msg void OnNcPaint();
};

