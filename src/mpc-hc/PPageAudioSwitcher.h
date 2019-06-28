/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2013 see Authors.txt
 *
 * This file is part of MPC-HC.
 *
 * MPC-HC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-HC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "CDarkPPageBase.h"
#include "FloatEdit.h"
#include "../filters/switcher/AudioSwitcher/AudioSwitcher.h"
#include "CDarkButton.h"
#include "CDarkSliderCtrl.h"
#include "CDarkEdit.h"
#include "CDarkSpinButtonCtrl.h"
#include "CDarkIntEdit.h"
#include "CDarkPlayerListCtrl.h"




// CPPageAudioSwitcher dialog

class CPPageAudioSwitcher : public CDarkPPageBase
{
    DECLARE_DYNAMIC(CPPageAudioSwitcher)

private:
    DWORD m_pSpeakerToChannelMap[AS_MAX_CHANNELS][AS_MAX_CHANNELS];
    DWORD m_dwChannelMask;

    BOOL m_fEnableAudioSwitcher;
    BOOL m_fAudioNormalize;
    UINT m_nAudioMaxNormFactor;
    CDarkSpinButtonCtrl m_AudioMaxNormFactorSpin;
    BOOL m_fAudioNormalizeRecover;
    int m_AudioBoostPos;
    CDarkSliderCtrl m_AudioBoostCtrl;
    BOOL m_fDownSampleTo441;
    CDarkRadioOrCheck m_fDownSampleTo441Ctrl;
    BOOL m_fCustomChannelMapping;
    CDarkRadioOrCheck m_fCustomChannelMappingCtrl;
    CDarkEdit m_nChannelsCtrl;
    int m_nChannels;
    CDarkSpinButtonCtrl m_nChannelsSpinCtrl;
    CDarkPlayerListCtrl m_list;
    int m_tAudioTimeShift;
    CDarkRadioOrCheck m_fAudioTimeShiftCtrl;
    CDarkIntEdit m_tAudioTimeShiftCtrl;
    CDarkSpinButtonCtrl m_tAudioTimeShiftSpin;
    BOOL m_fAudioTimeShift;

    // tooltip for slidercontrol
    CToolTipCtrl m_tooltip;

    //replaces tooltip from EnableTooltips()
    CDarkToolTipCtrl darkTT;

public:
    CPPageAudioSwitcher(IFilterGraph* pFG);
    virtual ~CPPageAudioSwitcher();

    // Dialog Data
    enum { IDD = IDD_PPAGEAUDIOSWITCHER };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    virtual BOOL OnApply();

    DECLARE_MESSAGE_MAP()

    afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnUpdateAudioSwitcher(CCmdUI* pCmdUI);
    afx_msg void OnUpdateNormalize(CCmdUI* pCmdUI);
    afx_msg void OnUpdateTimeShift(CCmdUI* pCmdUI);
    afx_msg void OnUpdateChannelMapping(CCmdUI* pCmdUI);

    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg BOOL OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnCancel();
    BOOL PreTranslateMessage(MSG * pMsg);
};
