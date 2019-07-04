/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2014 see Authors.txt
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

#include "ColorButton.h"
#include "CDarkPPageBase.h"
#include "../Subtitles/STS.h"
#include "CDarkSliderCtrl.h"

// CPPageSubStyle dialog

class CPPageSubStyle : public CDarkPPageBase
{
    DECLARE_DYNAMIC(CPPageSubStyle)

private:
    CString m_title;
    STSStyle m_stss;
    bool m_bDefaultStyle;

    CDarkButton m_font;
    int m_iCharset;
    CDarkComboBox m_cbCharset;
    int m_spacing;
    CDarkSpinButtonCtrl m_spacingSpin;
    int m_angle;
    CDarkSpinButtonCtrl m_angleSpin;
    int m_scalex;
    CDarkSpinButtonCtrl m_scalexSpin;
    int m_scaley;
    CDarkSpinButtonCtrl m_scaleySpin;
    int m_borderStyle;
    int m_borderWidth;
    CDarkSpinButtonCtrl m_borderWidthSpin;
    int m_shadowDepth;
    CDarkSpinButtonCtrl m_shadowDepthSpin;
    int m_screenAlignment;
    CRect m_margin;
    CDarkSpinButtonCtrl m_marginLeftSpin;
    CDarkSpinButtonCtrl m_marginRightSpin;
    CDarkSpinButtonCtrl m_marginTopSpin;
    CDarkSpinButtonCtrl m_marginBottomSpin;
    std::array<CColorButton, 4> m_color;
    std::array<int, 4> m_alpha;
    std::array<CDarkSliderCtrl, 4> m_alphaSliders;
    BOOL m_bLinkAlphaSliders;
    int m_iRelativeTo;

    void AskColor(int i);

public:
    CPPageSubStyle();
    virtual ~CPPageSubStyle();

    void InitStyle(const CString& title, const STSStyle& stss);
    void GetStyle(STSStyle& stss) const { stss = m_stss; }

    // Dialog Data
    enum { IDD = IDD_PPAGESUBSTYLE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual BOOL OnApply();

    DECLARE_MESSAGE_MAP()

    afx_msg void OnChooseFont();
    afx_msg void OnChoosePrimaryColor();
    afx_msg void OnChooseSecondaryColor();
    afx_msg void OnChooseOutlineColor();
    afx_msg void OnChooseShadowColor();
    afx_msg void OnLinkAlphaSlidersChanged();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
