#pragma once
#include <afxwin.h>
#include "CDarkButton.h"
#include "CDarkGroupBox.h"
#include "CDarkLinkCtrl.h"
#include "CDarkRadioOrCheck.h"
#include "CDarkEdit.h"
#include "CDarkSpinButtonCtrl.h"
#include "CDarkStatic.h"

class CDarkChildHelper
{
public:
    CDarkChildHelper();
	virtual ~CDarkChildHelper();
    static bool ModifyTemplates(CPropertySheet * sheet, CRuntimeClass* pageClass, DWORD id, DWORD addStyle, DWORD removeStyle = 0);

    void enableFileDialogHook();

    static HBRUSH DarkCtlColorFileDialog(HDC hDC, UINT nCtlColor);
    HBRUSH DarkCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
    void subClassFileDialog(CWnd* wnd, HWND hwnd, bool findSink = true);

protected:
    static CBrush darkContentBrush, darkWindowBrush, darkControlAreaBrush, W10DarkThemeFileDialogInjectedBGBrush;
    static CFont dialogFont;
    std::vector<CDarkButton *> allocatedButtons;
    std::vector<CDarkGroupBox *> allocatedGroupBoxes;
    std::vector<CDarkLinkCtrl *> allocatedLinkCtrls;
    std::vector<CDarkRadioOrCheck *> allocatedCheckBoxes;
    std::vector<CDarkRadioOrCheck *> allocatedRadioButtons;
    std::vector<CDarkRadioOrCheck *> allocated3States;
    std::vector<CDarkEdit *> allocatedEdits;
    std::vector<CDarkSpinButtonCtrl *> allocatedSpinButtons;
    std::vector<CDarkStatic *> allocatedStatics;

    void enableDarkThemeIfActive(CWnd *wnd);
    void initHelperObjects(CWnd* wnd);
};

