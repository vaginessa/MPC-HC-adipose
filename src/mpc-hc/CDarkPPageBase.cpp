#include "stdafx.h"
#include "mplayerc.h"
#include "CDarkPPageBase.h"
#include "CDarkTheme.h"
#include "ImageGrayer.h"

IMPLEMENT_DYNAMIC(CDarkPPageBase, CPPageBase)

CDarkPPageBase::CDarkPPageBase(UINT nIDTemplate, UINT nIDCaption)
    : CPPageBase(nIDTemplate, nIDCaption) {
}


CDarkPPageBase::~CDarkPPageBase() {
}

BOOL CDarkPPageBase::OnInitDialog() {
    __super::OnInitDialog();
    enableDarkThemeIfActive();
    return 0;
}

void CDarkPPageBase::SetDarkButtonIcon(UINT nIDButton, UINT nIDIcon) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        if (!m_buttonIcons.count(nIDIcon)) {
            CImage img, imgEnabled, imgDisabled;
            img.LoadFromResource(AfxGetInstanceHandle(), nIDIcon);

            ImageGrayer::UpdateColor(img, imgEnabled, false, true);
            ImageGrayer::UpdateColor(img, imgDisabled, true, true);

            CImageList& imageList = m_buttonIcons[nIDIcon];
            imageList.Create(img.GetWidth(), img.GetHeight(), ILC_COLOR32, 2, 0);
            imageList.Add(CBitmap::FromHandle(imgEnabled), nullptr);
            imageList.Add(CBitmap::FromHandle(imgDisabled), nullptr);
        }

        BUTTON_IMAGELIST buttonImageList;
        buttonImageList.himl = m_buttonIcons[nIDIcon];
        buttonImageList.margin = { 0, 0, 0, 0 };
        buttonImageList.uAlign = BUTTON_IMAGELIST_ALIGN_CENTER;
        static_cast<CButton*>(GetDlgItem(nIDButton))->SetImageList(&buttonImageList);
    } else {
        CPPageBase::SetButtonIcon(nIDButton, nIDIcon);

    }
}


BEGIN_MESSAGE_MAP(CDarkPPageBase, CPPageBase)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


HBRUSH CDarkPPageBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    if (AfxGetAppSettings().bDarkThemeLoaded) {
        LRESULT lResult;
        if (pWnd->SendChildNotifyLastMsg(&lResult)) {
            return (HBRUSH)lResult;
        }
        if (CTLCOLOR_LISTBOX == nCtlColor) {
            pDC->SetTextColor(CDarkTheme::TextFGColor);
            pDC->SetBkColor(CDarkTheme::ContentBGColor);
            return darkContentBrush;
        } else {
            pDC->SetTextColor(CDarkTheme::TextFGColor);
            pDC->SetBkColor(CDarkTheme::WindowBGColor);
            return darkWindowBrush;
        }
    } else {
        HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
        return hbr;
    }
}
