#include "stdafx.h"
#include "CDarkHeaderCtrl.h"
#include "CDarkTheme.h"

CDarkHeaderCtrl::CDarkHeaderCtrl() {
    hotItem = -1;
}


CDarkHeaderCtrl::~CDarkHeaderCtrl() {
}
BEGIN_MESSAGE_MAP(CDarkHeaderCtrl, CHeaderCtrl)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CDarkHeaderCtrl::OnNMCustomdraw)
    ON_NOTIFY(HDN_TRACKA, 0, &CDarkHeaderCtrl::OnHdnTrack)
    ON_NOTIFY(HDN_TRACKW, 0, &CDarkHeaderCtrl::OnHdnTrack)
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


void CDarkHeaderCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult) {
    NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

    *pResult = CDRF_DODEFAULT;
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT) {
            *pResult = CDRF_NOTIFYITEMDRAW;
        } else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT) {
            int nItem = pLVCD->nmcd.dwItemSpec;

            COLORREF textColor = CDarkTheme::TextFGColor;
            COLORREF bgColor = CDarkTheme::ContentBGColor;

            CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
            COLORREF oldTextColor = pDC->GetTextColor();
            COLORREF oldBkColor = pDC->GetBkColor();

            CRect rText, rGrid;
            GetItemRect(nItem, rText);
            rGrid = rText;

            HDITEM hditem = { 0 };
            hditem.mask = HDI_FORMAT | HDI_TEXT | HDI_STATE;
            const int c_cchBuffer = 1024;
            TCHAR  lpBuffer[c_cchBuffer];
            hditem.pszText = lpBuffer;
            hditem.cchTextMax = c_cchBuffer;

            GetItem(nItem, &hditem);
            int align = hditem.fmt & HDF_JUSTIFYMASK;
            UINT textFormat = DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
            if (align == HDF_CENTER)
                textFormat |= DT_CENTER;
            else if (align == HDF_LEFT) {
                textFormat |= DT_LEFT;
                rText.left += 6;
            } else {
                textFormat |= DT_RIGHT;
                rText.right -= 6;
            }
                       
            rGrid.top -= 1;
            rGrid.bottom -= 1;

            CPoint ptCursor;
            ::GetCursorPos(&ptCursor);
            ScreenToClient(&ptCursor);
            checkHot(ptCursor);

            if (nItem == hotItem) {
                bgColor = CDarkTheme::ColumnHeaderHotColor;
            }
            pDC->FillSolidRect(rGrid, bgColor);

            CString text = hditem.pszText;
            pDC->SetTextColor(textColor);
            pDC->SetBkColor(bgColor);

            CPen gridPen, *oldPen;
            gridPen.CreatePen(PS_SOLID, 1, CDarkTheme::ListCtrlGridColor);
            oldPen = pDC->SelectObject(&gridPen);
            pDC->MoveTo(rGrid.left, rGrid.bottom);
            pDC->LineTo(rGrid.BottomRight());
            pDC->LineTo(rGrid.right, rGrid.top);
            pDC->SelectObject(oldPen);

            CDarkTheme::DrawBufferedText(pDC, text, rText, textFormat);

            pDC->SetTextColor(oldTextColor);
            pDC->SetBkColor(oldBkColor);

            *pResult = CDRF_SKIPDEFAULT;
        }
    }
}


void CDarkHeaderCtrl::OnHdnTrack(NMHDR *pNMHDR, LRESULT *pResult) {
//    LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
    *pResult = 0;
}

void CDarkHeaderCtrl::checkHot(CPoint point) {
    HDHITTESTINFO hdHitTestInfo;
    hdHitTestInfo.pt = point;

    int prevHotItem = hotItem;
    hotItem = (int)SendMessage(HDM_HITTEST, 0, (LPARAM)&hdHitTestInfo);

    if ((hdHitTestInfo.flags & HHT_ONHEADER) == 0) {
        hotItem = -1;
    }
    if (hotItem != prevHotItem) RedrawWindow();
}


void CDarkHeaderCtrl::OnMouseMove(UINT nFlags, CPoint point) {
    if ((nFlags & MK_LBUTTON) == 0) {
        checkHot(point);
    }

    __super::OnMouseMove(nFlags, point);
}

void CDarkHeaderCtrl::OnMouseLeave() {
    if (hotItem >= 0) {
        hotItem = -1;
        RedrawWindow();
    }
    __super::OnMouseLeave();
}
