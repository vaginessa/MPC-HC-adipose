#pragma once
#include <afxcmn.h>
#include "CDarkToolTipCtrl.h"

class CDarkSliderCtrl :	public CSliderCtrl {
public:
	CDarkSliderCtrl();
	virtual ~CDarkSliderCtrl();
    virtual void PreSubclassWindow();
    DECLARE_DYNAMIC(CDarkSliderCtrl)
    DECLARE_MESSAGE_MAP()
protected:
    CBrush bgBrush;
    bool m_bDrag, m_bHover;
    CDarkToolTipCtrl darkTT;
public:
    afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    void invalidateThumb();
    void checkHover(CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseLeave();
};

