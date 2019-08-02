#pragma once
#include <vector>
#include <afxdlgs.h>

class CMPCThemeUtil
{
public:
    CMPCThemeUtil();
	virtual ~CMPCThemeUtil();
    static bool ModifyTemplates(CPropertySheet * sheet, CRuntimeClass* pageClass, DWORD id, DWORD addStyle, DWORD removeStyle = 0);

    void enableFileDialogHook();

    static HBRUSH getCtlColorFileDialog(HDC hDC, UINT nCtlColor);
    HBRUSH getCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
    static bool MPCThemeEraseBkgnd(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    void subClassFileDialog(CWnd* wnd, HWND hwnd, bool findSink = true);

protected:
    static CBrush contentBrush, windowBrush, controlAreaBrush, W10DarkThemeFileDialogInjectedBGBrush;
    static CFont dialogFont;
    std::vector<CWnd *> allocatedWindows;

    void fulfillThemeReqs(CWnd *wnd);
    void initHelperObjects(CWnd* wnd);
    void makeThemed(CWnd* pObject, CWnd* tChild);
};

