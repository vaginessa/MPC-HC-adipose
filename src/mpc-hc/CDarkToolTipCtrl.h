#pragma once
#include <afxcmn.h>

class CDarkToolTipCtrl;


class CDarkToolTipCtrl : public CToolTipCtrl {
    class CDarkToolTipCtrlHelper : public CWnd {
    private:
        CDarkToolTipCtrl* tt;
    public:
        CDarkToolTipCtrlHelper(CDarkToolTipCtrl* tt);
        virtual ~CDarkToolTipCtrlHelper();
        DECLARE_MESSAGE_MAP()
        afx_msg void OnPaint();
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    };


    DECLARE_DYNAMIC(CDarkToolTipCtrl)
private:
    bool useFlickerHelper;
    CDarkToolTipCtrlHelper* helper;
    void makeHelper();
public:
	CDarkToolTipCtrl();
	virtual ~CDarkToolTipCtrl();
    void enableFlickerHelper();
	static void drawText(CDC & dc, CDarkToolTipCtrl * tt, CRect & rect, bool calcRect=false);
    static void paintTT(CDC& dc, CDarkToolTipCtrl* tt);
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnMove(int x, int y);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

