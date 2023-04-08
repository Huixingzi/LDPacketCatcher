#pragma once

class CBufEdit : public CEdit
{
public:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnUpdate();

public:
	PCSOCKETPACKET pCsp = NULL;
};

