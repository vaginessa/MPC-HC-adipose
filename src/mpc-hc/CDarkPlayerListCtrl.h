#pragma once
#include "PlayerListCtrl.h"
#include "CDarkScrollBar.h"
#include "CDarkToolTipCtrl.h"

class CDarkPlayerListCtrl :	public CPlayerListCtrl {
public:
	CDarkPlayerListCtrl(int tStartEditingDelay = 500);
	virtual ~CDarkPlayerListCtrl();
    DECLARE_DYNAMIC(CDarkPlayerListCtrl)

    void setDarkDrawingArea(CRect &cr, CRect &wr, bool clipping);
    void hideSB();
    void updateDarkScrollInfo();
    LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    void updateToolTip(CPoint point);
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
    CDarkScrollBar darkVSB;
    CDarkToolTipCtrl darkTT;
    UINT_PTR darkTTcid;
    virtual void PreSubclassWindow();
public:
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

