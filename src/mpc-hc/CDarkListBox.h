#pragma once
#include <afxwin.h>
#include "CDarkScrollBar.h"
#include "CDarkToolTipCtrl.h"

class CDarkListBox :
	public CListBox
{
    DECLARE_DYNAMIC(CDarkListBox)
private:
    CDarkScrollBar darkVSB;
    CDarkToolTipCtrl darkTT;
    UINT_PTR darkTTcid;
protected:
    virtual void PreSubclassWindow();
public:
	CDarkListBox();
	virtual ~CDarkListBox();
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    void setDarkDrawingArea(CRect &cr, CRect &wr, bool clipping);
    void hideSB();
    void updateDarkScrollInfo();
    BOOL PreTranslateMessage(MSG * pMsg);
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
public:
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnLbnSelchange();
    void updateToolTip(CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

