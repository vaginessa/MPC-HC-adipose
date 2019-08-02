#pragma once
#include <afxcmn.h>
#include "CMPCThemeScrollBarHelper.h"

class CMPCThemeTreeCtrl :
	public CTreeCtrl, public CMPCThemeScrollable
{
public:
	CMPCThemeTreeCtrl();
	virtual ~CMPCThemeTreeCtrl();
    void PreSubclassWindow();
    BOOL PreCreateWindow(CREATESTRUCT & cs);
    void setDarkTheme();
    DECLARE_DYNAMIC(CMPCThemeTreeCtrl)
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnNcPaint();
protected:
    CBrush m_brBkgnd;
    CFont font;
    CMPCThemeScrollBarHelper *darkSBHelper;
public:
    void doDefault() { Default(); }
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

