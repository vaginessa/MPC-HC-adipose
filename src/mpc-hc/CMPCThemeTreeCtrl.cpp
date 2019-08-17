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
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        if (CMPCThemeUtil::canUseWin10DarkTheme()) {
            SetWindowTheme(GetSafeHwnd(), L"DarkMode_Explorer", NULL);
        }
        else {
            SetWindowTheme(GetSafeHwnd(), L"", NULL);
        }
        SetExtendedStyle(TVS_EX_DOUBLEBUFFER, TVS_EX_DOUBLEBUFFER); //necessary to prevent significant flicker
        if (font.m_hObject == nullptr) CMPCThemeUtil::getFontByType(font, GetWindowDC(), CMPCThemeUtil::MenuFont);
        SetFont(&font);
    } else {
        //adipose--enabling this cuts down on a very minor flicker in classic mode;
        //the duplicate line above is necessary due to a non-default bg.
        //treat as a separate line of code to be clear that this one is "optional" while the other is not
        SetExtendedStyle(TVS_EX_DOUBLEBUFFER, TVS_EX_DOUBLEBUFFER); //optional
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
        {
            *pResult = CDRF_NOTIFYITEMDRAW;
            CDC dc;
            dc.Attach(pNMCD->hdc);
            dc.FillSolidRect(&pNMCD->rc, CMPCTheme::ContentBGColor);
            //doEraseBkgnd(&dc);
            dc.Detach();
            break;
        }
        case CDDS_ITEMPREPAINT:
            isFocus = 0 != (pNMCD->uItemState & CDIS_FOCUS);
            isHot = 0 != (pNMCD->uItemState & CDIS_HOT);

            //regular theme is a bit ugly but better than Explorer theme. we clear the focus states to control the highlight ourselves
            if (!CMPCThemeUtil::canUseWin10DarkTheme()) {
                pNMCD->uItemState &= ~(CDIS_FOCUS | CDIS_HOT | CDIS_SELECTED);
            }

            if (isFocus) {
                pstCD->clrTextBk = CMPCTheme::TreeCtrlFocusColor;
            } else if (isHot) {
                pstCD->clrTextBk = CMPCTheme::TreeCtrlHoverColor;
            } else {
                pstCD->clrTextBk = CMPCTheme::ContentBGColor;
            }
            pstCD->clrText = CMPCTheme::TextFGColor;
            *pResult = CDRF_DODEFAULT;
            break;
        default:
            pResult = CDRF_DODEFAULT;
            break;
        }
    } else {
        __super::OnPaint();
    }
}

void CMPCThemeTreeCtrl::doEraseBkgnd(CDC* pDC) {
    CRect r;
    GetWindowRect(r);
    r.OffsetRect(-r.left, -r.top);
    pDC->FillSolidRect(r, CMPCTheme::ContentBGColor);
}

BOOL CMPCThemeTreeCtrl::OnEraseBkgnd(CDC* pDC) {
    if (AfxGetAppSettings().bMPCThemeLoaded) {
        //doEraseBkgnd(pDC); //we do this in the custom draw prepaint step now, to allow double buffering to work
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

LRESULT CMPCThemeTreeCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
    if (AfxGetAppSettings().bMPCThemeLoaded && nullptr != themedSBHelper) {
        if (themedSBHelper->WindowProc(this, message, wParam, lParam)) {
            return 1;
        }
    }
    return __super::WindowProc(message, wParam, lParam);
}
