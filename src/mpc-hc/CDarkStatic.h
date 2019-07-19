#pragma once
#include <afxwin.h>
class CDarkStatic :
	public CStatic
{
    DECLARE_DYNAMIC(CDarkStatic)
public:

	CDarkStatic();
	virtual ~CDarkStatic();
    void setFileDialogChild(bool set) { isFileDialogChild = set; };
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    afx_msg void OnNcPaint();
    afx_msg void OnEnable(BOOL bEnable);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
    bool isFileDialogChild;
};

