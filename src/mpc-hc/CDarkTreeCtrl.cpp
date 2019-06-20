#include "stdafx.h"
#include "CDarkTreeCtrl.h"
#include "CDarkTheme.h"


CDarkTreeCtrl::CDarkTreeCtrl() {
    m_brBkgnd.CreateSolidBrush(CDarkTheme::InlineEditBorderColor);
}


CDarkTreeCtrl::~CDarkTreeCtrl() {
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
    }
}


BEGIN_MESSAGE_MAP(CDarkTreeCtrl, CTreeCtrl)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CDarkTreeCtrl::OnNMCustomdraw)
    ON_WM_ERASEBKGND()
    ON_WM_DRAWITEM()
    ON_WM_NCPAINT()
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
        CDC* pDC = GetWindowDC();
        CRect r;
        GetWindowRect(r);
        r.OffsetRect(-r.left, -r.top);
        CBrush brushBorder(CDarkTheme::EditBorderColor);
        pDC->FrameRect(r, &brushBorder);
        r.DeflateRect(1, 1);
        CBrush brushBG(CDarkTheme::ContentBGColor);
        pDC->FrameRect(r, &brushBG);
        ReleaseDC(pDC);
    } else {
        __super::OnNcPaint();
    }
}
