#include "stdafx.h"
#include "CDarkListBox.h"
#include "CDarkTheme.h"
#include "mplayerc.h"

IMPLEMENT_DYNAMIC(CDarkListBox, CListBox)

CDarkListBox::CDarkListBox() {
    darkTTcid = (UINT_PTR)-1;
    darkSBHelper = nullptr;
    if (!CDarkTheme::canUseWin10DarkTheme()) {
        darkSBHelper = DEBUG_NEW CDarkScrollBarHelper(this);
    }
}


CDarkListBox::~CDarkListBox() {
    if (nullptr != darkSBHelper) {
        delete darkSBHelper;
    }
}

BEGIN_MESSAGE_MAP(CDarkListBox, CListBox)
    ON_WM_NCPAINT()
    ON_WM_MOUSEWHEEL()
    ON_WM_TIMER()
    ON_WM_VSCROLL()
    ON_CONTROL_REFLECT(LBN_SELCHANGE, &CDarkListBox::OnLbnSelchange)
    ON_WM_MOUSEMOVE()
    ON_WM_SIZE()
END_MESSAGE_MAP()


void CDarkListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
    CDC dc;

    dc.Attach(lpDrawItemStruct->hDC);

    COLORREF crOldTextColor = dc.GetTextColor();
    COLORREF crOldBkColor = dc.GetBkColor();

    if ((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED)) {
        dc.SetTextColor(CDarkTheme::TextFGColor);
        dc.SetBkColor(CDarkTheme::ContentSelectedColor);
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, CDarkTheme::ContentSelectedColor);
    } else {
        dc.SetTextColor(CDarkTheme::TextFGColor);
        dc.SetBkColor(CDarkTheme::ContentBGColor);
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, CDarkTheme::ContentBGColor);
    }

    lpDrawItemStruct->rcItem.left += 3;

    CString strText;
    GetText(lpDrawItemStruct->itemID, strText);

    CFont font;
    CDarkTheme::getFontByType(font, &dc, CDarkTheme::CDDialogFont);
    CFont* pOldFont = dc.SelectObject(&font);
    dc.DrawText(strText, strText.GetLength(), &lpDrawItemStruct->rcItem, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);
    dc.SelectObject(pOldFont);

    dc.Detach();
}


void CDarkListBox::OnNcPaint() {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        if (nullptr != darkSBHelper) {
            darkSBHelper->darkNcPaintWithSB();
        } else {
            CDarkScrollBarHelper::darkNcPaint(this, this);
        }
    } else {
        __super::OnNcPaint();
    }
}

BOOL CDarkListBox::PreTranslateMessage(MSG* pMsg) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        darkTT.RelayEvent(pMsg);
    }
    return CListBox::PreTranslateMessage(pMsg);
}

void CDarkListBox::PreSubclassWindow() {
    CListBox::PreSubclassWindow();
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (CDarkTheme::canUseWin10DarkTheme()) {
            SetWindowTheme(GetSafeHwnd(), L"DarkMode_Explorer", NULL);
        } else {
            SetWindowTheme(GetSafeHwnd(), L"", NULL);
        }
        darkTT.Create(this, TTS_ALWAYSTIP);
        darkTT.enableFlickerHelper();
        setIntegralHeight();
    }
}


BOOL CDarkListBox::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    CListBox::OnMouseWheel(nFlags, zDelta, pt);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
    ScreenToClient(&pt);
    updateToolTip(pt);
    return TRUE;
}

void CDarkListBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}

void CDarkListBox::OnLbnSelchange() {
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}


void CDarkListBox::updateToolTip(CPoint point) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        TOOLINFO ti = { 0 };
        UINT_PTR tid = OnToolHitTest(point, &ti);
        //OnToolHitTest returns -1 on failure but doesn't update uId to match
        if (tid != -1 && darkTTcid != ti.uId && 0 != ti.uId) {
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


void CDarkListBox::OnMouseMove(UINT nFlags, CPoint point) {
    updateToolTip(point);
}

void CDarkListBox::setIntegralHeight() {
    CWindowDC dc(this);
    CFont font;
    CDarkTheme::getFontByType(font, &dc, CDarkTheme::CDDialogFont);
    CFont* pOldFont = dc.SelectObject(&font);
    CRect r(0, 0, 99, 99);
    CString test = _T("W");
    dc.DrawText(test, test.GetLength(), &r, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
    SetItemHeight(0, r.Height());

    dc.SelectObject(pOldFont);
}

void CDarkListBox::OnSize(UINT nType, int cx, int cy) {
    CListBox::OnSize(nType, cx, cy);
}
