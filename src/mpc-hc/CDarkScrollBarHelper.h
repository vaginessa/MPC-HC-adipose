#pragma once
#include "stdafx.h"
#include "CDarkScrollBar.h"

class CDarkScrollBarHelper
{
protected:
    CWnd *window;
    CDarkScrollBar darkVSB;
public:
	CDarkScrollBarHelper(CWnd* scrollWindow);
	~CDarkScrollBarHelper();
    void createSB();
    void BeforeNcPaint();
    void AfterNcPaint();
    void setDarkDrawingArea(CRect & cr, CRect & wr, bool clipping);
    void hideSB();
    void updateDarkScrollInfo();
    bool WindowProc(CListCtrl * list, UINT message, WPARAM wParam, LPARAM lParam);
};

