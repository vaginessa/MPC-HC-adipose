#include "stdafx.h"
#include "CMPCThemeListBox.h"
#include "CMPCTheme.h"
#include "mplayerc.h"

IMPLEMENT_DYNAMIC(CMPCThemeListBox, CListBox)

CMPCThemeListBox::CMPCThemeListBox() {
    darkTTcid = (UINT_PTR)-1;
    darkSBHelper = nullptr;
    if (!CMPCTheme::canUseWin10DarkTheme()) {
        darkSBHelper = DEBUG_NEW CMPCThemeScrollBarHelper(this);
    }
}


CMPCThemeListBox::~CMPCThemeListBox() {
    if (nullptr != darkSBHelper) {
        delete darkSBHelper;
    }
}

BEGIN_MESSAGE_MAP(CMPCThemeListBox, CListBox)
    ON_WM_NCPAINT()
    ON_WM_MOUSEWHEEL()
    ON_WM_TIMER()
    ON_WM_VSCROLL()
    ON_CONTROL_REFLECT(LBN_SELCHANGE, &CMPCThemeListBox::OnLbnSelchange)
    ON_WM_MOUSEMOVE()
    ON_WM_SIZE()
END_MESSAGE_MAP()


void CMPCThemeListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
    CDC dc;

    dc.Attach(lpDrawItemStruct->hDC);

    COLORREF crOldTextColor = dc.GetTextColor();
    COLORREF crOldBkColor = dc.GetBkColor();

    if ((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED)) {
        dc.SetTextColor(CMPCTheme::TextFGColor);
        dc.SetBkColor(CMPCTheme::ContentSelectedColor);
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, CMPCTheme::ContentSelectedColor);
    } else {
        dc.SetTextColor(CMPCTheme::TextFGColor);
        dc.SetBkColor(CMPCTheme::ContentBGColor);
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, CMPCTheme::ContentBGColor);
    }

    lpDrawItemStruct->rcItem.left += 3;

    CString strText;
    GetText(lpDrawItemStruct->itemID, strText);

    CFont font;
    CMPCTheme::getFontByType(font, &dc, CMPCTheme::CDDialogFont);
    CFont* pOldFont = dc.SelectObject(&font);
    dc.DrawText(strText, strText.GetLength(), &lpDrawItemStruct->rcItem, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);

    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);
    dc.SelectObject(pOldFont);

    dc.Detach();
}


void CMPCThemeListBox::OnNcPaint() {
    const CAppSettings& s = AfxGetAppSettings();
    if (s.bDarkThemeLoaded) {
        if (nullptr != darkSBHelper) {
            darkSBHelper->darkNcPaintWithSB();
        } else {
            CMPCThemeScrollBarHelper::darkNcPaint(this, this);
        }
    } else {
        __super::OnNcPaint();
    }
}

BOOL CMPCThemeListBox::PreTranslateMessage(MSG* pMsg) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        darkTT.RelayEvent(pMsg);
    }
    return CListBox::PreTranslateMessage(pMsg);
}

void CMPCThemeListBox::PreSubclassWindow() {
    CListBox::PreSubclassWindow();
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (CMPCTheme::canUseWin10DarkTheme()) {
            SetWindowTheme(GetSafeHwnd(), L"DarkMode_Explorer", NULL);
        } else {
            SetWindowTheme(GetSafeHwnd(), L"", NULL);
        }
        darkTT.Create(this, TTS_ALWAYSTIP);
        darkTT.enableFlickerHelper();
        setIntegralHeight();
    }
}


BOOL CMPCThemeListBox::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
    CListBox::OnMouseWheel(nFlags, zDelta, pt);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
    ScreenToClient(&pt);
    updateToolTip(pt);
    return TRUE;
}

void CMPCThemeListBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
    CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}

void CMPCThemeListBox::OnLbnSelchange() {
    if (nullptr != darkSBHelper) {
        darkSBHelper->updateDarkScrollInfo();
    }
}


void CMPCThemeListBox::updateToolTip(CPoint point) {
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


void CMPCThemeListBox::OnMouseMove(UINT nFlags, CPoint point) {
    updateToolTip(point);
}

void CMPCThemeListBox::setIntegralHeight() {
    CWindowDC dc(this);
    CFont font;
    CMPCTheme::getFontByType(font, &dc, CMPCTheme::CDDialogFont);
    CFont* pOldFont = dc.SelectObject(&font);
    CRect r(0, 0, 99, 99);
    CString test = _T("W");
    dc.DrawText(test, test.GetLength(), &r, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_CALCRECT);
    SetItemHeight(0, r.Height());

    dc.SelectObject(pOldFont);
}

void CMPCThemeListBox::OnSize(UINT nType, int cx, int cy) {
    CListBox::OnSize(nType, cx, cy);
}
