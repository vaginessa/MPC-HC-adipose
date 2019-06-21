#include "stdafx.h"
#include "CDarkTreeCtrl.h"
#include "CDarkTheme.h"


CDarkTreeCtrl::CDarkTreeCtrl() {
    m_brBkgnd.CreateSolidBrush(CDarkTheme::InlineEditBorderColor);
    darkSBHelper = nullptr;
    if (!CDarkTheme::canUseWin10DarkTheme()) {
        darkSBHelper = DEBUG_NEW CDarkScrollBarHelper(this);
    }
}


CDarkTreeCtrl::~CDarkTreeCtrl() {
    if (nullptr != darkSBHelper) {
        delete darkSBHelper;
    }
}

void CDarkTreeCtrl::PreSubclassWindow() {
    SetLineColor(CDarkTheme::TreeCtrlLineColor);
}

BOOL CDarkTreeCtrl::PreCreateWindow(CREATESTRUCT& cs) {
    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    return __super::PreCreateWindow(cs);
}

void CDarkTreeCtrl::setDarkTheme() {
    if (CDarkTheme::canUseWin10DarkTheme()) {
        SetWindowTheme(GetSafeHwnd(), L"DarkMode_Explorer", NULL);
    } else {
        SetWindowTheme(GetSafeHwnd(), L"", NULL);
    }
}


BEGIN_MESSAGE_MAP(CDarkTreeCtrl, CTreeCtrl)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CDarkTreeCtrl::OnNMCustomdraw)
    ON_WM_ERASEBKGND()
    ON_WM_DRAWITEM()
    ON_WM_NCPAINT()
    ON_WM_MOUSEWHEEL()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
END_MESSAGE_MAP()
IMPLEMENT_DYNAMIC(CDarkTreeCtrl, CTreeCtrl)

void CDarkTreeCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult) {
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    NMTVCUSTOMDRAW* pstCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
    *pResult = CDRF_DODEFAULT;

    if (AfxGetAppSettings().bDarkThemeLoaded) {

        bool isFocus, isHot;
        switch (pNMCD->dwDrawStage) {
        case CDDS_PREPAINT:
            *pResult = CDRF_NOTIFYITEMDRAW;
            break;
        case CDDS_ITEMPREPAINT:
            isFocus = 0 != (pNMCD->uItemState & CDIS_FOCUS);
            isHot = 0 != (pNMCD->uItemState & CDIS_HOT);

            if (!CDarkTheme::canUseWin10DarkTheme()) { //regular theme is a bit ugly but better than Explorer theme.  we will clean up the fonts at least
                pNMCD->uItemState &= ~(CDIS_FOCUS | CDIS_HOT | CDIS_SELECTED);
                if (font.m_hObject == nullptr) CDarkTheme::getUIFont(font, ::GetDC(NULL), CDarkTheme::CDMenuFont);
                ::SelectObject(pNMCD->hdc, font.GetSafeHandle());
            }

            if (isFocus) {
                pstCD->clrTextBk = CDarkTheme::TreeCtrlFocusColor;
            } else if (isHot) {
                pstCD->clrTextBk = CDarkTheme::TreeCtrlHoverColor;
            } else {
                pstCD->clrTextBk = CDarkTheme::ContentBGColor;
            }
            pstCD->clrText = CDarkTheme::TextFGColor;
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


BOOL CDarkTreeCtrl::OnEraseBkgnd(CDC* pDC) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        CRect r;
        GetWindowRect(r);
        r.OffsetRect(-r.left, -r.top);
        pDC->FillSolidRect(r, CDarkTheme::ContentBGColor);
        return TRUE;
    } else {
        return __super::OnEraseBkgnd(pDC);
    }
}


void CDarkTreeCtrl::OnNcPaint() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (nullptr != darkSBHelper) {
            darkSBHelper->darkNcPaintWithSB();
        } else {
            CDarkScrollBarHelper::darkNcPaint(this, this);
        }
    } else {
        __super::OnNcPaint();
    }
}

//no end scroll notification for treectrl, so handle mousewheel, v an h scrolls :-/
BOOL CDarkTreeCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    BOOL ret = __super::OnMouseWheel(nFlags, zDelta, pt);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
    return ret;
}



void CDarkTreeCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    __super::OnVScroll(nSBCode, nPos, pScrollBar);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}


void CDarkTreeCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    __super::OnHScroll(nSBCode, nPos, pScrollBar);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}
