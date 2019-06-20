#pragma once

class CDarkButton :	public CMFCButton {
public:
	CDarkButton();
	virtual ~CDarkButton();
    void PreSubclassWindow();
    void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};

