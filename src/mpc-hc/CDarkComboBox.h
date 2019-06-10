#pragma once
#include <afxwin.h>
class CDarkComboBox :
	public CComboBox
{
    DECLARE_DYNAMIC(CDarkComboBox)
private:
    bool isHover;
    CBrush bgBrush;
public:
	CDarkComboBox();
    void doDraw(CDC & dc, CString strText, CRect r, COLORREF bkColor, bool drawDotted);
	virtual ~CDarkComboBox();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnMouseLeave();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    void checkHover(UINT nFlags, CPoint point, bool invalidate = true);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

