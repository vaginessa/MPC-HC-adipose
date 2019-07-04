#include "stdafx.h"
#include "CDarkToolTipCtrl.h"
#include "CDarkTheme.h"
#include <afxglobals.h>


CDarkToolTipCtrl::CDarkToolTipCtrl() {
    this->useFlickerHelper = false;
    this->helper = nullptr;
}


CDarkToolTipCtrl::~CDarkToolTipCtrl() {
    if (nullptr != helper) {
        helper->DestroyWindow();
        delete helper;
    }
}

void CDarkToolTipCtrl::enableFlickerHelper() {
    this->useFlickerHelper = true;
}

IMPLEMENT_DYNAMIC(CDarkToolTipCtrl, CToolTipCtrl)
BEGIN_MESSAGE_MAP(CDarkToolTipCtrl, CToolTipCtrl)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_CREATE()
    ON_WM_MOVE()
    ON_WM_SHOWWINDOW()
    ON_WM_SIZE()
END_MESSAGE_MAP()

void CDarkToolTipCtrl::drawText(CDC& dc, CDarkToolTipCtrl* tt, CRect& rect, bool calcRect) {
    CFont font;
    CDarkTheme::getFontByType(font, &dc, CDarkTheme::CDMessageFont);
    CFont* pOldFont = dc.SelectObject(&font);

    CString text;
    tt->GetWindowText(text);
    int maxWidth = tt->GetMaxTipWidth();
    int calcStyle = 0;
    if (calcRect) {
        calcStyle = DT_CALCRECT;
    }
    rect.DeflateRect(6, 2);
    if (maxWidth == -1)
        dc.DrawText(text, rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE | calcStyle);
    else
        dc.DrawText(text, rect, DT_LEFT | DT_WORDBREAK | calcStyle);
    rect.InflateRect(6, 2); //when calculating, put it back


    dc.SelectObject(pOldFont);
}

void CDarkToolTipCtrl::paintTT(CDC& dc, CDarkToolTipCtrl* tt) {
    CRect r;
    tt->GetClientRect(r);

    dc.FillSolidRect(r, CDarkTheme::MenuBGColor);

    CBrush fb;
    fb.CreateSolidBrush(CDarkTheme::TooltipBorderColor);
    dc.FrameRect(r, &fb);
    COLORREF oldClr = dc.SetTextColor(CDarkTheme::TextFGColor);
    drawText(dc, tt, r, false);
    dc.SetTextColor(oldClr);
}

void CDarkToolTipCtrl::OnPaint() {
    CPaintDC dc(this);
    if (useFlickerHelper) { //helper will paint
        return;
    }
    paintTT(dc, this);
}


BOOL CDarkToolTipCtrl::OnEraseBkgnd(CDC* pDC) {
    return TRUE;
}


int CDarkToolTipCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CToolTipCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    makeHelper();
    return 0;
}

void CDarkToolTipCtrl::makeHelper() {
    if (!useFlickerHelper) return;

    if (nullptr != helper) {
        delete helper;
    }
    CRect r;
    GetClientRect(r);
    ClientToScreen(r);

    helper = new CDarkToolTipCtrlHelper(this);
    //do it the long way since no menu for parent
    helper->CreateEx(NULL, AfxRegisterWndClass(0), NULL, WS_POPUP | WS_DISABLED,
        r.left, r.top, r.right - r.left, r.bottom - r.top,
        GetParent()->GetSafeHwnd(), NULL, NULL);
    helper->Invalidate();
    helper->ShowWindow(SW_SHOWNOACTIVATE);
}


BEGIN_MESSAGE_MAP(CDarkToolTipCtrl::CDarkToolTipCtrlHelper, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()


CDarkToolTipCtrl::CDarkToolTipCtrlHelper::CDarkToolTipCtrlHelper(CDarkToolTipCtrl * tt) {
    this->tt = tt;
}

CDarkToolTipCtrl::CDarkToolTipCtrlHelper::~CDarkToolTipCtrlHelper() {
    DestroyWindow();
}

void CDarkToolTipCtrl::CDarkToolTipCtrlHelper::OnPaint() {
    CPaintDC dc(this);
    CDarkToolTipCtrl::paintTT(dc, tt);
}


BOOL CDarkToolTipCtrl::CDarkToolTipCtrlHelper::OnEraseBkgnd(CDC* pDC) {
    return TRUE;
}

void CDarkToolTipCtrl::OnMove(int x, int y) {
    CToolTipCtrl::OnMove(x, y);
    makeHelper();
}


void CDarkToolTipCtrl::OnShowWindow(BOOL bShow, UINT nStatus) {

    CToolTipCtrl::OnShowWindow(bShow, nStatus);
    if (!bShow) {
        if (helper != nullptr) {
            delete helper;
            helper = nullptr;
        }
    }
}

void CDarkToolTipCtrl::OnSize(UINT nType, int cx, int cy) {
    //hack to make it fit if fonts differ from parent. can be manually avoided
    //if the parent widget is set to same font (see CDarkPlayerListCtrl using MessageFont now)
    if (GetMaxTipWidth() == -1) {
        CWindowDC dc(this);

        CRect cr, origCr, wr, origWr;
        GetWindowRect(wr);
        GetClientRect(cr);
        origCr = cr;
        origWr = wr;
        drawText(dc, this, cr, true);//calculate crect required to fit the text
        wr.right += cr.Width() - origCr.Width();//add the difference to the window
        if (origWr.right != wr.right) {
            MoveWindow(wr, FALSE);
        }
    }

    CToolTipCtrl::OnSize(nType, cx, cy);
    makeHelper();
}
