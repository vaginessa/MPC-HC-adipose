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
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    void setCheckedColors(COLORREF checkedBG, COLORREF checkedText, COLORREF uncheckedText);
    void subclassHeader();
    void setAdditionalStyles(DWORD styles);
    void setHasCBImages(bool on);
    void setItemTextWithDefaultFlag(int nItem, int nSubItem, LPCTSTR lpszText, bool flagged);
    void setFlaggedItem(int iItem, bool flagged);
    bool getFlaggedItem(int iItem);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnNcPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
    afx_msg BOOL OnCustomDraw(NMHDR * pNMHDR, LRESULT * pResult);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
    CDarkScrollBarHelper *darkSBHelper;
    CDarkToolTipCtrl darkTT, lvsToolTip;
    UINT_PTR darkTTcid;
    COLORREF checkedBGClr, checkedTextClr, uncheckedTextClr;
    std::map<int, bool> flaggedItems;
    bool hasCheckedColors;
    bool hasCBImages;
    bool darkGridLines;
    bool fullRowSelect;
    CDarkHeaderCtrl darkHdrCtrl;
    CFont listMPCThemeFont, listMPCThemeFontBold;
    void drawItem(CDC* pDC, int nItem, int nSubItem);
    virtual void PreSubclassWindow();
public:
    void doDefault() { Default(); };
    afx_msg void OnHdnEndtrack(NMHDR *pNMHDR, LRESULT *pResult);
};

