#pragma once
#include <afxcmn.h>
class CDarkHeaderCtrl :
	public CHeaderCtrl
{
protected:
    int hotItem;
    void checkHot(CPoint point);
    void drawItem(int nItem, CRect rText, CDC* pDC);
public:
	CDarkHeaderCtrl();
	virtual ~CDarkHeaderCtrl();
    DECLARE_MESSAGE_MAP()
    afx_msg	void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnHdnTrack(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnMouseLeave();
	afx_msg void OnPaint();
};

