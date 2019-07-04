#include "stdafx.h"
#include "CDarkSliderCtrl.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

CDarkSliderCtrl::CDarkSliderCtrl() 
    :m_bDrag(false), m_bHover(false) {

}


CDarkSliderCtrl::~CDarkSliderCtrl() {
}

void CDarkSliderCtrl::PreSubclassWindow() {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        CToolTipCtrl* pTip = GetToolTips();
        if (nullptr != pTip) {
            darkTT.SubclassWindow(pTip->m_hWnd);
        }
    }
}

IMPLEMENT_DYNAMIC(CDarkSliderCtrl, CSliderCtrl)

BEGIN_MESSAGE_MAP(CDarkSliderCtrl, CSliderCtrl)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CDarkSliderCtrl::OnNMCustomdraw)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


void CDarkSliderCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult) {
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    LRESULT lr = CDRF_DODEFAULT;

    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        switch (pNMCD->dwDrawStage) {
        case CDDS_PREPAINT:
            lr = CDRF_NOTIFYITEMDRAW;
            break;

        case CDDS_ITEMPREPAINT:

            if (pNMCD->dwItemSpec == TBCD_CHANNEL) {
                CDC dc;
                dc.Attach(pNMCD->hdc);

                CRect rect;
                GetClientRect(rect);
                dc.FillSolidRect(&rect, CDarkTheme::WindowBGColor);

                CRect channelRect;
                GetChannelRect(channelRect);
                CRect thumbRect;
                GetThumbRect(thumbRect);

                CopyRect(&pNMCD->rc, CRect(channelRect.left, thumbRect.top + 2, channelRect.right - 2, thumbRect.bottom - 2));

                CPen shadow;
                CPen light;
                shadow.CreatePen(PS_SOLID, 1, CDarkTheme::ShadowColor);
                light.CreatePen(PS_SOLID, 1, CDarkTheme::LightColor);
                CRect r(pNMCD->rc);
                r.DeflateRect(0, 6, 0, 6);
                dc.FillSolidRect(r, CDarkTheme::SliderChannelColor);
                CBrush fb;
                fb.CreateSolidBrush(CDarkTheme::NoBorderColor);
                dc.FrameRect(r, &fb);

                dc.Detach();
                lr = CDRF_SKIPDEFAULT;
            } else if (pNMCD->dwItemSpec == TBCD_THUMB) {
                CDC dc;
                dc.Attach(pNMCD->hdc);
                pNMCD->rc.bottom--;
                CRect r(pNMCD->rc);
                r.DeflateRect(0, 0, 1, 0);

                if (s.bDarkThemeLoaded) {
                    CBrush fb;
                    if (m_bDrag) {
                        dc.FillSolidRect(r, CDarkTheme::ScrollThumbDragColor);
                    } else if (m_bHover) {
                        dc.FillSolidRect(r, CDarkTheme::ScrollThumbHoverColor);
                    } else {
                        dc.FillSolidRect(r, CDarkTheme::ScrollThumbColor);
                    }
                    fb.CreateSolidBrush(CDarkTheme::NoBorderColor);
                    dc.FrameRect(r, &fb);
                }

                dc.Detach();
                lr = CDRF_SKIPDEFAULT;
            }

            break;
        };
    }

    *pResult = lr;
}

void CDarkSliderCtrl::invalidateThumb() {
    int max = GetRangeMax();
    SetRangeMax(max, TRUE);
}


void CDarkSliderCtrl::checkHover(CPoint point) {
    CRect thumbRect;
    GetThumbRect(thumbRect);
    bool oldHover = m_bHover;
    m_bHover = false;
    if (thumbRect.PtInRect(point)) {
        m_bHover = true;
    }

    if (m_bHover != oldHover)
        invalidateThumb();
}

void CDarkSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) {
    checkHover(point);
    CSliderCtrl::OnMouseMove(nFlags, point);
}


void CDarkSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) {
    m_bDrag = false;
    invalidateThumb();
    checkHover(point);
    CSliderCtrl::OnLButtonUp(nFlags, point);
}


void CDarkSliderCtrl::OnMouseLeave() {
    checkHover(CPoint(-1,-1));
    CSliderCtrl::OnMouseLeave();
}
