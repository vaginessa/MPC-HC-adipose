#pragma once
#include "stdafx.h"
#include "CMPCThemeScrollBar.h"
class CMPCThemeTreeCtrl;

class CMPCThemeScrollable {
public:
    CMPCThemeScrollable() {};
    ~CMPCThemeScrollable() {};
    virtual void doDefault() {};
};

class CMPCThemeScrollBarHelper
{
protected:
    CWnd *window, *pParent;
    CMPCThemeScrollBar darkVSB, darkHSB;
    bool hasVSB;
    bool hasHSB;
    static void doNcPaint(CWnd *window);
public:
	CMPCThemeScrollBarHelper(CWnd* scrollWindow);
	~CMPCThemeScrollBarHelper();
    void createSB();
    void setDarkDrawingArea(CRect & cr, CRect & wr, bool clipping);
    void hideSB();
    void updateDarkScrollInfo();
    bool WindowProc(CListCtrl * list, UINT message, WPARAM wParam, LPARAM lParam);
    bool WindowProc(CTreeCtrl * list, UINT message, WPARAM wParam, LPARAM lParam);
    void darkNcPaintWithSB();
    static void darkNcPaint(CWnd *window, CMPCThemeScrollable *swindow);
};

