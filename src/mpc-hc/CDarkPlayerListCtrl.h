#pragma once
#include "PlayerListCtrl.h"
#include "CDarkScrollBarHelper.h"
#include "CDarkToolTipCtrl.h"
#include "CDarkChildHelper.h"
#include "CDarkHeaderCtrl.h"

class CDarkPlayerListCtrl :	public CPlayerListCtrl, CDarkChildHelper, CDarkScrollable {
public:
	CDarkPlayerListCtrl(int tStartEditingDelay = 500);
	virtual ~CDarkPlayerListCtrl();
    DECLARE_DYNAMIC(CDarkPlayerListCtrl)

    void updateSB();
    void updateDarkScrollInfo();
    LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    void updateToolTip(CPoint point);
    void setGridLines(bool on);
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
    afx_msg void OnCustomDraw(NMHDR * pNMHDR, LRESULT * pResult);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
    CDarkScrollBarHelper *darkSBHelper;
    CDarkToolTipCtrl darkTT;
    UINT_PTR darkTTcid;
    bool darkGridLines;
    CDarkHeaderCtrl darkHdrCtrl;
    virtual void PreSubclassWindow();
public:
    void doDefault() { Default(); };
};

