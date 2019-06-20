#pragma once
#include <afxwin.h>
class CDarkRadioOrCheck : public CButton
{
public:
	CDarkRadioOrCheck();
	virtual ~CDarkRadioOrCheck();
    void PreSubclassWindow();
private:
    bool isHover;
    BOOL isAuto;
    CBrush bgBrush;
    DWORD buttonStyle;
    enum RadioOrCheck {
        radioType,
        checkType,
        unknownType
    };
    RadioOrCheck buttonType;
protected:
    DECLARE_DYNAMIC(CDarkRadioOrCheck)
    DECLARE_MESSAGE_MAP()
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnMouseLeave();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    void checkHover(UINT nFlags, CPoint point, bool invalidate = true);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
    afx_msg void OnPaint();
};

