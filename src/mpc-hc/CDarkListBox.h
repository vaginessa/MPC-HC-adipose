#pragma once
#include <afxwin.h>
#include "CDarkScrollBar.h"
#include "CDarkToolTipCtrl.h"
#include "CDarkScrollBarHelper.h"

class CDarkListBox :
	public CListBox, public CDarkScrollable
{
    DECLARE_DYNAMIC(CDarkListBox)
private:
    CDarkScrollBar darkVSB;
    CDarkToolTipCtrl darkTT;
    UINT_PTR darkTTcid;
    CDarkScrollBarHelper *darkSBHelper;
protected:
    virtual void PreSubclassWindow();
public:
	CDarkListBox();
	virtual ~CDarkListBox();
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    BOOL PreTranslateMessage(MSG * pMsg);
    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
public:
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnLbnSelchange();
    void updateToolTip(CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    void setIntegralHeight();
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

