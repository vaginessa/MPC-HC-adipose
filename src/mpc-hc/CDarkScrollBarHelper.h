#pragma once
#include "stdafx.h"
#include "CDarkScrollBar.h"
class CDarkTreeCtrl;

class CDarkScrollable {
public:
    CDarkScrollable() {};
    ~CDarkScrollable() {};
    virtual void doDefault() {};
};

class CDarkScrollBarHelper
{
protected:
    CWnd *window;
    CDarkScrollBar darkVSB, darkHSB;
    bool hasVSB;
    bool hasHSB;
    static void doNcPaint(CWnd *window);
public:
	CDarkScrollBarHelper(CWnd* scrollWindow);
	~CDarkScrollBarHelper();
    void createSB();
    void setDarkDrawingArea(CRect & cr, CRect & wr, bool clipping);
    void hideSB();
    void updateDarkScrollInfo();
    bool WindowProc(CListCtrl * list, UINT message, WPARAM wParam, LPARAM lParam);
    bool WindowProc(CTreeCtrl * list, UINT message, WPARAM wParam, LPARAM lParam);
    void darkNcPaintWithSB();
    static void darkNcPaint(CWnd *window, CDarkScrollable *swindow);
};

