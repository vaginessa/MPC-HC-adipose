#pragma once
#include <afxpriv.h>
class CDarkDockBar : public CDockBar 
{
    DECLARE_DYNAMIC(CDarkDockBar)
public:
	CDarkDockBar();
	virtual ~CDarkDockBar();
protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnNcPaint();
};

