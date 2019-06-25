#pragma once
#include <afxcmn.h>
class CDarkSpinButtonCtrl : public CSpinButtonCtrl {
public:
	CDarkSpinButtonCtrl();
	virtual ~CDarkSpinButtonCtrl();
    DECLARE_DYNAMIC(CDarkSpinButtonCtrl)
    DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
    CPoint downPos;
    void OnPaint();
};

