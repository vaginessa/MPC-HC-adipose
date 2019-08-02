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

    static HBRUSH DarkCtlColorFileDialog(HDC hDC, UINT nCtlColor);
    HBRUSH DarkCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
    static bool MPCThemeEraseBkgnd(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    void subClassFileDialog(CWnd* wnd, HWND hwnd, bool findSink = true);

protected:
    static CBrush darkContentBrush, darkWindowBrush, darkControlAreaBrush, W10DarkThemeFileDialogInjectedBGBrush;
    static CFont dialogFont;
    std::vector<CWnd *> allocatedButtons;
    std::vector<CWnd *> allocatedGroupBoxes;
    std::vector<CWnd *> allocatedLinkCtrls;
    std::vector<CWnd *> allocatedCheckBoxes;
    std::vector<CWnd *> allocatedRadioButtons;
    std::vector<CWnd *> allocated3States;
    std::vector<CWnd *> allocatedEdits;
    std::vector<CWnd *> allocatedSpinButtons;
    std::vector<CWnd *> allocatedStatics;
    std::vector<CWnd*> allocatedDialogs;
    std::vector<CWnd*> allocatedComboBoxes;
    std::vector<CWnd*> allocatedSliders;
    std::vector<CWnd*> allocatedTabCtrls;

    void fulfillThemeReqs(CWnd *wnd);
    void initHelperObjects(CWnd* wnd);
};

