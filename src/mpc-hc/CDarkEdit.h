#pragma once
#include <afxwin.h>
class CDarkEdit :
	public CEdit
{
    DECLARE_DYNAMIC(CDarkEdit)
public:
	CDarkEdit();
	virtual ~CDarkEdit();
    void PreSubclassWindow();
    void setBuddy(CWnd* buddyWindow) { this->buddy = buddyWindow; };
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
protected:
    CWnd *buddy;

};

