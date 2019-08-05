#include "stdafx.h"
#include "CMPCThemeTreeCtrl.h"
#include "CMPCTheme.h"
#include "CMPCThemeUtil.h"


CMPCThemeTreeCtrl::CMPCThemeTreeCtrl() {
    m_brBkgnd.CreateSolidBrush(CMPCTheme::InlineEditBorderColor);
    themedSBHelper = nullptr;
    if (!CMPCThemeUtil::canUseWin10DarkTheme()) {
        themedSBHelper = DEBUG_NEW CMPCThemeScrollBarHelper(this);
    }
}


CMPCThemeTreeCtrl::~CMPCThemeTreeCtrl() {
    if (nullptr != themedSBHelper) {
        delete themedSBHelper;
    }
}

void CMPCThemeTreeCtrl::PreSubclassWindow() {
    SetLineColor(CMPCTheme::TreeCtrlLineColor);
}

BOOL CMPCThemeTreeCtrl::PreCreateWindow(CREATESTRUCT& cs) {
    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    return __super::PreCreateWindow(cs);
}

void CMPCThemeTreeCtrl::fulfillThemeReqs() {
    if (CMPCThemeUtil::canUseWin10DarkTheme()) {
        SetWindowTheme(GetSafeHwnd(), L"DarkMode_Explorer", NULL);
    } else {
        SetWindowTheme(GetSafeHwnd(), L"", NULL);
    }
}


BEGIN_MESSAGE_MAP(CMPCThemeTreeCtrl, CTreeCtrl)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMPCThemeTreeCtrl::OnNMCustomdraw)
    ON_WM_ERASEBKGND()
    ON_WM_DRAWITEM()
    ON_WM_NCPAINT()
    ON_WM_MOUSEWHEEL()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
END_MESSAGE_MAP()
IMPLEMENT_DYNAMIC(CMPCThemeTreeCtrl, CTreeCtrl)

void CMPCThemeTreeCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult) {
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    NMTVCUSTOMDRAW* pstCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
    *pResult = CDRF_DODEFAULT;

    if (AfxGetAppSettings().bMPCThemeLoaded) {

        bool isFocus, isHot;
        switch (pNMCD->dwDrawStage) {
        case CDDS_PREPAINT:
            *pResult = CDRF_NOTIFYITEMDRAW;
            break;
        case CDDS_ITEMPREPAINT:
            isFocus = 0 != (pNMCD->uItemState & CDIS_FOCUS);
            isHot = 0 != (pNMCD->uItemState & CDIS_HOT);

            if (!CMPCThemeUtil::canUseWin10DarkTheme()) { //regular theme is a bit ugly but better than Explorer theme.  we will clean up the fonts at least
                pNMCD->uItemState &= ~(CDIS_FOCUS | CDIS_HOT | CDIS_SELECTED);
                if (font.m_hObject == nullptr) CMPCThemeUtil::getFontByType(font, GetWindowDC(), CMPCThemeUtil::MenuFont);
                ::SelectObject(pNMCD->hdc, font.GetSafeHandle());
            }

            if (isFocus) {
                pstCD->clrTextBk = CMPCTheme::TreeCtrlFocusColor;
            } else if (isHot) {
                pstCD->clrTextBk = CMPCTheme::TreeCtrlHoverColor;
            } else {
                pstCD->clrTextBk = CMPCTheme::ContentBGColor;
            }
            pstCD->clrText = CMPCTheme::TextFGColor;
            *pResult = CDRF_NEWFONT;
            break;
        default:
            pResult = CDRF_DODEFAULT;
            break;
        }
    } else {
        __super::OnPaint();
    }
}


BOOL CMPCThemeTreeCtrl::OnEraseBkgnd(CDC* pDC) {
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        CRect r;
        GetWindowRect(r);
        r.OffsetRect(-r.left, -r.top);
        pDC->FillSolidRect(r, CMPCTheme::ContentBGColor);
        return TRUE;
    } else {
        return __super::OnEraseBkgnd(pDC);
    }
}


void CMPCThemeTreeCtrl::OnNcPaint() {
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        if (nullptr != themedSBHelper) {
            themedSBHelper->themedNcPaintWithSB();
        } else {
            CMPCThemeScrollBarHelper::themedNcPaint(this, this);
        }
    } else {
        __super::OnNcPaint();
    }
}

//no end scroll notification for treectrl, so handle mousewheel, v an h scrolls :-/
BOOL CMPCThemeTreeCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    BOOL ret = __super::OnMouseWheel(nFlags, zDelta, pt);
    if (nullptr != themedSBHelper) {
        themedSBHelper->updateScrollInfo();
    }
    return ret;
}



void CMPCThemeTreeCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    __super::OnVScroll(nSBCode, nPos, pScrollBar);
    if (nullptr != themedSBHelper) {
        themedSBHelper->updateScrollInfo();
    }
}


void CMPCThemeTreeCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    __super::OnHScroll(nSBCode, nPos, pScrollBar);
    if (nullptr != themedSBHelper) {
        themedSBHelper->updateScrollInfo();
    }
}
