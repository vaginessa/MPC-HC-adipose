#pragma once
#include <afxwin.h>

struct MenuObject {
    HICON m_hIcon;
    CString m_strCaption;
    CString m_strAccel;
    bool isMenubar = false;
    bool isSeparator = false;
    bool isFirstMenuInMenuBar = false;
};



class CMPCThemeMenu :public CMenu {
    DECLARE_DYNCREATE(CMPCThemeMenu)
public:
	CMPCThemeMenu();
	virtual ~CMPCThemeMenu();

    void fulfillThemeReqs(bool menubar = false);
    void fullfillThemeReqsItem(UINT i, bool byCommand=false);
    static void fullfillThemeReqsItem(CMenu* parent, UINT i, bool byCommand=false);
    static UINT getPosFromID(CMenu* parent, UINT nID);
    static CMPCThemeMenu* getParentMenu(UINT itemID);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    CMPCThemeMenu* GetSubMenu(int nPos);
    static void updateItem(CCmdUI* pCmdUI);
    static void clearDimensions() { hasDimensions = false; };
protected:
    static std::map<UINT, CMPCThemeMenu*> subMenuIDs;
    std::vector<MenuObject*> allocatedItems;
    std::vector<CMPCThemeMenu*> allocatedMenus;
    void initDimensions();

    void GetRects(RECT rcItem, CRect& rectFull, CRect& rectM, CRect& rectIcon, CRect& rectText, CRect& rectArrow);
    static bool hasDimensions;
    static int subMenuPadding;
    static int iconSpacing;
    static int iconPadding;
    static int rowPadding;
    static int separatorPadding;
    static int separatorHeight;
    static int postTextSpacing;
    static int accelSpacing;
};

