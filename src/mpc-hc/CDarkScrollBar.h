#pragma once
#include <afxwin.h>
#include "XeScrollBar/XeScrollBarBase.h"

class CDarkScrollBar :	public CXeScrollBarBase
{
    DECLARE_DYNAMIC(CDarkScrollBar)
public:
	CDarkScrollBar();
	virtual ~CDarkScrollBar();
    void DrawScrollBar(CDC * pDC);
    virtual void SendScrollMsg(WORD wSBcode, WORD wHiWPARAM);
    void setScrollWindow(CWnd* m_SBRepl) { this->m_scrollWindow = m_SBRepl; };
    void updateScrollInfo();
protected:
    CWnd* m_scrollWindow; //real parent is window we overlay the SB
    DECLARE_MESSAGE_MAP()
    UINT scrollLines;
};

