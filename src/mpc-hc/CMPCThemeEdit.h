#pragma once
#include <afxwin.h>
#include "CMPCThemeScrollBarHelper.h"
class CMPCThemeEdit :
	public CEdit
    ,public CMPCThemeScrollable

{
    DECLARE_DYNAMIC(CMPCThemeEdit)
public:
	CMPCThemeEdit();
	virtual ~CMPCThemeEdit();
    void PreSubclassWindow();
    void setBuddy(CWnd* buddyWindow) { this->buddy = buddyWindow; };
    void setFileDialogChild(bool set) { isFileDialogChild = set; };
    void SetFixedWidthFont(CFont& f);
protected:
    CWnd *buddy;
    CMPCThemeScrollBarHelper *themedSBHelper;
    CFont font;
    bool isFileDialogChild;

    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

