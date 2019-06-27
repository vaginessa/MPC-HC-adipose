#pragma once
#include <afxwin.h>
class CDarkGroupBox :
	public CStatic
{
    DECLARE_DYNAMIC(CDarkGroupBox)
protected:
    CFont font;
public:
	CDarkGroupBox();
	virtual ~CDarkGroupBox();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
};

