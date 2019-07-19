#pragma once
#include <afxwin.h>
#include "CDarkScrollBarHelper.h"
class CDarkEdit :
	public CEdit, public CDarkScrollable
{
    DECLARE_DYNAMIC(CDarkEdit)
public:
	CDarkEdit();
	virtual ~CDarkEdit();
    void PreSubclassWindow();
    void setBuddy(CWnd* buddyWindow) { this->buddy = buddyWindow; };
    void setFileDialogChild(bool set) { isFileDialogChild = set; };
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
protected:
    CWnd *buddy;
    CDarkScrollBarHelper *darkSBHelper;
    bool isFileDialogChild;

public:
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

