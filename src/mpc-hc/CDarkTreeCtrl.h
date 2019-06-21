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
protected:
    CBrush m_brBkgnd;
    CFont font;
    CDarkScrollBarHelper *darkSBHelper;
public:
    afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnNcPaint();
    void doDefault() { Default(); }
};

