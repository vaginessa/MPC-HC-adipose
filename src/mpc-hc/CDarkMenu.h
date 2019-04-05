#pragma once
#include <afxwin.h>
#include "CDarkTheme.h"

struct MenuObject {
    HICON m_hIcon;
    CString m_strCaption;
    CString m_strAccel;
    bool isMenubar = false;
    bool isFirstMenuInMenuBar = false;
};



class CDarkMenu :public CMenu, public CDarkTheme {
    DECLARE_DYNCREATE(CDarkMenu)
public:
	CDarkMenu();
	virtual ~CDarkMenu();

    static const int subMenuPadding = 20;
    static const int iconSpacing = 22;
    static const int rowHeight = 24;
    static const int iconPadding = 10;
    static const int postTextSpacing = 20;
    static const int accelSpacing = 30;
    static wchar_t* const uiTextFont;
    static wchar_t* const uiSymbolFont;

    std::vector<MenuObject *> allocatedItems;
    std::vector<CDarkMenu *> allocatedMenus;
    static std::map<UINT, CDarkMenu *> subMenuIDs;
    void ActivateDarkTheme(bool menubar=false);
    static CDarkMenu* getParentMenu(UINT itemID);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    CSize GetTextSize(CString str, HDC hDC);
    CFont* getUIFont(HDC hDC, wchar_t *fontName, int size, LONG weight=FW_REGULAR);
    CDarkMenu* GetSubMenu(int nPos);
    static void updateItem(CCmdUI* pCmdUI);
};

