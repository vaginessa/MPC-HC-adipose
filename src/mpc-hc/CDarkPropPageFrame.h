#pragma once
#include "TreePropSheet/PropPageFrameDefault.h"
class CDarkPropPageFrame : public TreePropSheet::CPropPageFrameDefault
{
public:
	CDarkPropPageFrame();
	virtual ~CDarkPropPageFrame();
    virtual BOOL Create(DWORD dwWindowStyle, const RECT &rect, CWnd *pwndParent, UINT nID);
    virtual CWnd* GetWnd();

    virtual void DrawCaption(CDC * pDc, CRect rect, LPCTSTR lpszCaption, HICON hIcon);

    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    DECLARE_MESSAGE_MAP()

};

