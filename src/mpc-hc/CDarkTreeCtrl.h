#pragma once
#include <afxcmn.h>
#include "CDarkScrollBarHelper.h"

class CDarkTreeCtrl :
	public CTreeCtrl, public CDarkScrollable
{
public:
	CDarkTreeCtrl();
	virtual ~CDarkTreeCtrl();
    void PreSubclassWindow();
    BOOL PreCreateWindow(CREATESTRUCT & cs);
    void setDarkTheme();
    DECLARE_DYNAMIC(CDarkTreeCtrl)
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnNcPaint();
protected:
    CBrush m_brBkgnd;
    CFont font;
    CDarkScrollBarHelper *darkSBHelper;
public:
    void doDefault() { Default(); }
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

