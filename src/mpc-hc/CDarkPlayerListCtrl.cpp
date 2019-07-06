#include "stdafx.h"
#include "CDarkPlayerListCtrl.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

CDarkPlayerListCtrl::CDarkPlayerListCtrl(int tStartEditingDelay) : CPlayerListCtrl(tStartEditingDelay) {
    darkGridLines = false;
    fullRowSelect = false;
    darkSBHelper = nullptr;
    hasCheckedColors = false;
    hasCBImages = false;
    if (!CDarkTheme::canUseWin10DarkTheme()) {
        darkSBHelper = DEBUG_NEW CDarkScrollBarHelper(this);
    }
}


CDarkPlayerListCtrl::~CDarkPlayerListCtrl() {
    if (nullptr != darkSBHelper) {
        delete darkSBHelper;
    }
}


void CDarkPlayerListCtrl::PreSubclassWindow() {
    if (!AfxGetAppSettings().bDarkThemeLoaded) {
        EnableToolTips(TRUE);
    } else {
        if (CDarkTheme::canUseWin10DarkTheme()) {
            SetWindowTheme(GetSafeHwnd(), L"DarkMode_Explorer", NULL);
        } else {
            SetWindowTheme(GetSafeHwnd(), L"", NULL);
        }
        CToolTipCtrl *t = GetToolTips();
        if (nullptr != t) {
            lvsToolTip.SubclassWindow(t->m_hWnd);
        }
        CDarkTheme::getFontByType(listMPCThemeFont, GetWindowDC(), CDarkTheme::CDMessageFont);
        CDarkTheme::getFontByType(listMPCThemeFontBold, GetWindowDC(), CDarkTheme::CDMessageFont, false, true);
        SetFont(&listMPCThemeFont);
        subclassHeader();
    }
    CPlayerListCtrl::PreSubclassWindow();
}

IMPLEMENT_DYNAMIC(CDarkPlayerListCtrl, CPlayerListCtrl)

BEGIN_MESSAGE_MAP(CDarkPlayerListCtrl, CPlayerListCtrl)
    ON_WM_NCPAINT()
    ON_WM_CREATE()
    ON_NOTIFY_REFLECT_EX(LVN_ENDSCROLL, OnLvnEndScroll)
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL()
    ON_WM_NCCALCSIZE()
    ON_NOTIFY_REFLECT_EX(NM_CUSTOMDRAW, OnCustomDraw)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CDarkPlayerListCtrl::subclassHeader() {
    CHeaderCtrl *t = GetHeaderCtrl();
    if (nullptr != t && IsWindow(t->m_hWnd) && darkHdrCtrl.m_hWnd == NULL) {
        darkHdrCtrl.SubclassWindow(t->GetSafeHwnd());
    }
}

void CDarkPlayerListCtrl::setAdditionalStyles(DWORD styles) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        DWORD stylesToAdd = styles, stylesToRemove = 0;
        if (styles & LVS_EX_GRIDLINES) {
            stylesToAdd &= ~LVS_EX_GRIDLINES;
            stylesToRemove |= LVS_EX_GRIDLINES;
            darkGridLines = true;
        }
        if (styles & LVS_EX_FULLROWSELECT) {
            stylesToAdd &= ~LVS_EX_FULLROWSELECT;
            stylesToRemove |= LVS_EX_FULLROWSELECT;
            fullRowSelect = true;
        }
        if (styles & LVS_EX_DOUBLEBUFFER) { //we will buffer ourselves
            stylesToAdd &= ~LVS_EX_DOUBLEBUFFER;
            stylesToRemove |= LVS_EX_DOUBLEBUFFER;
        }
        SetExtendedStyle((GetExtendedStyle() | stylesToAdd) & ~stylesToRemove);
    } else {
        SetExtendedStyle(GetExtendedStyle() | styles);
    }
}

void CDarkPlayerListCtrl::setHasCBImages(bool on) {
    hasCBImages = on;
}

void CDarkPlayerListCtrl::setItemTextWithDefaultFlag(int nItem, int nSubItem, LPCTSTR lpszText, bool flagged) {
    SetItemText(nItem, nSubItem, lpszText);
    setFlaggedItem(nItem, flagged);
}

void CDarkPlayerListCtrl::setFlaggedItem(int iItem, bool flagged) {
    flaggedItems[iItem] = flagged;
}

bool CDarkPlayerListCtrl::getFlaggedItem(int iItem) {
    auto it = flaggedItems.find(iItem);
    if (it != flaggedItems.end()) {
        return it->second;
    } else {
        return false;
    }
}


BOOL CDarkPlayerListCtrl::PreTranslateMessage(MSG * pMsg) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (!IsWindow(darkTT.m_hWnd)) {
            darkTT.Create(this, TTS_ALWAYSTIP);
            darkTT.enableFlickerHelper();
        }
        if (IsWindow(darkTT.m_hWnd)) {
            darkTT.RelayEvent(pMsg);
        }
    }
    return __super::PreTranslateMessage(pMsg);
}

void CDarkPlayerListCtrl::setCheckedColors(COLORREF checkedBG, COLORREF checkedText, COLORREF uncheckedText) {
    checkedBGClr = checkedBG;
    checkedTextClr = checkedText;
    uncheckedTextClr = uncheckedText;
    hasCheckedColors = true;
}

void CDarkPlayerListCtrl::OnNcPaint() {
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


int CDarkPlayerListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (__super::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (AfxGetAppSettings().bDarkThemeLoaded) {
        SetBkColor(CDarkTheme::ContentBGColor);
        subclassHeader();
    }

    return 0;
}

BOOL CDarkPlayerListCtrl::OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (nullptr != darkSBHelper) {
            darkSBHelper->updateDarkScrollInfo();
        }
        *pResult = 0;
    }
    return FALSE;
}

void CDarkPlayerListCtrl::updateSB() {
    if (nullptr != darkSBHelper) {
        darkSBHelper->hideSB();
    }
}

void CDarkPlayerListCtrl::updateDarkScrollInfo() {
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}

LRESULT CDarkPlayerListCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
    if (AfxGetAppSettings().bDarkThemeLoaded && nullptr != darkSBHelper) {
        if (darkSBHelper->WindowProc(this, message, wParam, lParam)) {
            return 1;
        }
    }
    return __super::WindowProc(message, wParam, lParam);
}

void CDarkPlayerListCtrl::updateToolTip(CPoint point) {
    if (AfxGetAppSettings().bDarkThemeLoaded && nullptr != darkTT) {
        TOOLINFO ti = { 0 };
        UINT_PTR tid = OnToolHitTest(point, &ti);
        //OnToolHitTest returns -1 on failure but doesn't update uId to match
        if (tid != -1 && darkTTcid != ti.uId) {
            if (darkTT.GetToolCount() > 0) {
                darkTT.DelTool(this);
                darkTT.Activate(FALSE);
            }

            darkTTcid = ti.uId;

            CRect cr;
            GetClientRect(&cr); //we reset the tooltip every time we move anyway, so this rect is adequate

            darkTT.AddTool(this, LPSTR_TEXTCALLBACK, &cr, ti.uId);
            darkTT.Activate(TRUE);
        }
    }
}

void CDarkPlayerListCtrl::OnMouseMove(UINT nFlags, CPoint point) {
    __super::OnMouseMove(nFlags, point);
    updateToolTip(point);
}


BOOL CDarkPlayerListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    BOOL ret = __super::OnMouseWheel(nFlags, zDelta, pt);
    ScreenToClient(&pt);
    updateToolTip(pt);
    return ret;
}


void CDarkPlayerListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp) {
    __super::OnNcCalcSize(bCalcValidRects, lpncsp);
}

BOOL CDarkPlayerListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

        *pResult = CDRF_DODEFAULT;
        if (pLVCD->nmcd.dwDrawStage == CDDS_PREPAINT) {
            *pResult = CDRF_NOTIFYITEMDRAW;
        } else if (pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT) {
            *pResult = CDRF_NOTIFYSUBITEMDRAW;
        } else if (pLVCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM)) {
            int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);
            if (IsItemVisible(nItem)) {
                int nSubItem = pLVCD->iSubItem;

                COLORREF textColor = CDarkTheme::TextFGColor;
                COLORREF bgColor = CDarkTheme::ContentBGColor;

                CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
                COLORREF oldTextColor = pDC->GetTextColor();
                COLORREF oldBkColor = pDC->GetBkColor();

                CString text = GetItemText(nItem, nSubItem);
                pDC->SetTextColor(textColor);
                pDC->SetBkColor(bgColor);


                CRect rect, rRow, rIcon, rText, rTextBG, rectDC;
                GetItemRect(nItem, rRow, LVIR_BOUNDS);
                GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rText);
                GetSubItemRect(nItem, nSubItem, LVIR_ICON, rIcon);
                GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
                if (0 == nSubItem) { //getsubitemrect gives whole row for 0/LVIR_BOUNDS.  but LVIR_LABEL is limited to text bounds.  MSDN undocumented behavior
                    rect.right = rText.right;
                }

                rectDC = rRow;
                CDC dcMem;
                CBitmap bmMem;
                CDarkTheme::initMemDC(pDC, dcMem, bmMem, rectDC);
                rect.OffsetRect(-rectDC.TopLeft());
                rText.OffsetRect(-rectDC.TopLeft());
                rIcon.OffsetRect(-rectDC.TopLeft());
                rRow.OffsetRect(-rectDC.TopLeft());

                if (!IsWindowEnabled() && 0 == nSubItem) { //no gridlines, bg for full row
                    dcMem.FillSolidRect(rRow, CDarkTheme::ListCtrlDisabledBGColor);
                } else {
                    dcMem.FillSolidRect(rect, CDarkTheme::ContentBGColor); //no flicker because we have a memory dc
                }
                
                rTextBG = rText;
                
                HDITEM hditem = { 0 };
                hditem.mask = HDI_FORMAT;
                GetHeaderCtrl()->GetItem(nSubItem, &hditem);
                int align = hditem.fmt & HDF_JUSTIFYMASK;
                UINT textFormat = DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
                if (align == HDF_CENTER)
                    textFormat |= DT_CENTER;
                else if (align == HDF_LEFT) {
                    textFormat |= DT_LEFT;
                    if (nSubItem == 0) {//less indent for first column
                        rText.left += 2;
                    } else {
                        rText.left += 6;
                    }
                } else {
                    textFormat |= DT_RIGHT;
                    rText.right -= 6;
                }

                bool isChecked = false;
                int contentLeft = rText.left;
                if (rIcon.Width() > 0) {
                    LVITEM lvi = { 0 };
                    lvi.iItem = nItem;
                    lvi.iSubItem = 0;
                    lvi.mask = LVIF_IMAGE;
                    GetItem(&lvi);

                    isChecked = (BST_CHECKED == lvi.iImage);
                    if (nSubItem == 0) {
                        contentLeft = rIcon.left;
                        if (hasCBImages) { //draw manually to match theme
                            rIcon.DeflateRect(0, 0, 1, 0);
                            if (rIcon.Height() > rIcon.Width()) {
                                rIcon.DeflateRect(0, (rIcon.Height() - rIcon.Width()) / 2); //as tall as wide
                            }

                            CDarkTheme::drawCheckBox(isChecked, false, false, rIcon, &dcMem);
                        } else {
                            DWORD dwStyle = GetStyle() & LVS_TYPEMASK;
                            if (dwStyle == LVS_ICON) {
                            } else if (dwStyle == LVS_SMALLICON || dwStyle == LVS_LIST || dwStyle == LVS_REPORT) {
                                CImageList *ilist = GetImageList(LVSIL_SMALL);
                                int cx, cy;
                                ImageList_GetIconSize(ilist->m_hImageList, &cx, &cy);
                                rIcon.top += (rIcon.Height() - cy) / 2;
                                ilist->Draw(&dcMem, lvi.iImage, rIcon.TopLeft(), ILD_TRANSPARENT);
                            }
                        }
                        if (align == HDF_LEFT)
                            rText.left += 2; //more ident after image
                    }
                }
                if (0 != (GetExtendedStyle() & LVS_EX_CHECKBOXES)) {
                    isChecked = (TRUE == GetCheck(nItem));
                    if (nSubItem == 0) {
                        int cbSize = GetSystemMetrics(SM_CXMENUCHECK);
                        int cbYMargin = (rect.Height() - cbSize - 1) / 2;
                        int cbXMargin = (contentLeft - rect.left - cbSize) / 2;
                        CRect rcb = { rect.left + cbXMargin, rect.top + cbYMargin, rect.left + cbXMargin + cbSize, rect.top + cbYMargin + cbSize };
                        CDarkTheme::drawCheckBox(isChecked, false, true, rcb, &dcMem);
                    }
                }

                COLORREF bgClr = CDarkTheme::ContentBGColor;
                if (IsWindowEnabled()) {
                    if (GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED && (nSubItem == 0 || fullRowSelect)) {
                        bgClr = CDarkTheme::ContentSelectedColor;
                    } else if (hasCheckedColors) {
                        if (isChecked && checkedBGClr != -1) {
                            bgClr = checkedBGClr;
                        }
                        if (isChecked && checkedTextClr != -1) dcMem.SetTextColor(checkedTextClr);
                        if (!isChecked && uncheckedTextClr != -1)
                            dcMem.SetTextColor(uncheckedTextClr);
                    }
                    dcMem.FillSolidRect(rTextBG, bgClr);

                    if (darkGridLines) {
                        CRect rGrid = rect;
                        rGrid.bottom -= 1;
                        CPen gridPen, *oldPen;
                        gridPen.CreatePen(PS_SOLID, 1, CDarkTheme::WindowBorderColorDim);
                        oldPen = dcMem.SelectObject(&gridPen);
                        if (nSubItem != 0) {
                            dcMem.MoveTo(rGrid.TopLeft());
                            dcMem.LineTo(rGrid.left, rGrid.bottom);
                        } else {
                            dcMem.MoveTo(rGrid.left, rGrid.bottom);
                        }
                        dcMem.LineTo(rGrid.BottomRight());
                        dcMem.LineTo(rGrid.right, rGrid.top);
                        dcMem.SelectObject(oldPen);
                    }
                }

                if (getFlaggedItem(nItem)) { //could be a setting, but flagged items are bold for now
                    dcMem.SelectObject(listMPCThemeFontBold);
                }
                //CDarkTheme::DrawBufferedText(pDC, text, rText, textFormat);
                dcMem.DrawText(text, rText, textFormat);
                CDarkTheme::flushMemDC(pDC, dcMem, rectDC);
                pDC->SetTextColor(oldTextColor);
                pDC->SetBkColor(oldBkColor);
            }
            *pResult = CDRF_SKIPDEFAULT;
        }
        return TRUE;
    }
    return FALSE;
}


BOOL CDarkPlayerListCtrl::OnEraseBkgnd(CDC* pDC) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        CRect r;
        GetClientRect(r);
        int dcState = pDC->SaveDC();
        for (int y = 0; y < GetItemCount(); y++) {
            CRect clip;
            GetItemRect(y, clip, LVIR_BOUNDS);
            pDC->ExcludeClipRect(clip);
        }
        pDC->FillSolidRect(r, CDarkTheme::ContentBGColor);

        if (darkGridLines) {

            CPen gridPen, *oldPen;
            gridPen.CreatePen(PS_SOLID, 1, CDarkTheme::WindowBorderColorDim);
            oldPen = pDC->SelectObject(&gridPen);

            CRect gr;
            for (int x = 0; x < darkHdrCtrl.GetItemCount(); x++) {
                darkHdrCtrl.GetItemRect(x, gr);
                pDC->MoveTo(gr.right, r.top);
                pDC->LineTo(gr.right, r.bottom);
            }
            gr.bottom = 0;
            for (int y = 0; y < GetItemCount() || gr.bottom < r.bottom; y++) {
                if (y >= GetItemCount()) {
                    gr.OffsetRect(0, gr.Height());
                } else {
                    GetItemRect(y, gr, LVIR_BOUNDS);
                }
                pDC->MoveTo(r.left, gr.bottom-1);
                pDC->LineTo(r.right, gr.bottom-1);
            }
            pDC->SelectObject(oldPen);
        }
        pDC->RestoreDC(dcState);
    } else {
        return __super::OnEraseBkgnd(pDC);
    }
    return TRUE;
}


HBRUSH CDarkPlayerListCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    HBRUSH ret;
    ret = DarkCtlColor(pDC, pWnd, nCtlColor);
    if (nullptr != ret) {
        return ret;
    } else {
        return __super::OnCtlColor(pDC, pWnd, nCtlColor);
    }
}
