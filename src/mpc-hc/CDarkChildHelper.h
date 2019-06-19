#pragma once
#include <afxwin.h>
#include "CDarkButton.h"
#include "CDarkGroupBox.h"
#include "CDarkLinkCtrl.h"
#include "CDarkRadioOrCheck.h"
#include "CDarkEdit.h"

class CDarkChildHelper
{
public:
    CDarkChildHelper();
	virtual ~CDarkChildHelper();
    static bool ModifyTemplates(CPropertySheet * sheet, CRuntimeClass* pageClass, DWORD id, DWORD addStyle, DWORD removeStyle = 0);

    HBRUSH DarkCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

protected:
    static CBrush darkContentBrush, darkWindowBrush, darkControlAreaBrush;
    static CFont dialogFont;
    std::vector<CDarkButton *> allocatedButtons;
    std::vector<CDarkGroupBox *> allocatedGroupBoxes;
    std::vector<CDarkLinkCtrl *> allocatedLinkCtrls;
    std::vector<CDarkRadioOrCheck *> allocatedCheckBoxes;
    std::vector<CDarkRadioOrCheck *> allocatedRadioButtons;
    std::vector<CDarkEdit *> allocatedEdits;

    void enableDarkThemeIfActive(CWnd *wnd);
};

