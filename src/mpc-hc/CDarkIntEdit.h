#pragma once
#include "CDarkEdit.h"
class CDarkIntEdit :
	public CDarkEdit
{
public:
	CDarkIntEdit();
	virtual ~CDarkIntEdit();
public:
    DECLARE_DYNAMIC(CDarkIntEdit)
    DECLARE_MESSAGE_MAP()
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

