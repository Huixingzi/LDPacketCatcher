#pragma once


// CAnalysisDlg 对话框

class CAnalysisDlg : public CDialog
{
	DECLARE_DYNAMIC(CAnalysisDlg)

public:
	CAnalysisDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAnalysisDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	PCSOCKETPACKET pCsp;
	PCSOCKETPACKET pCsp_Backup;

	VOID SetInfo();

	virtual BOOL OnInitDialog();
	CBufEdit m_Edit_OrgBytes;
	CEdit m_Edit_Char;
	afx_msg void OnEnChangeEdit1();
	CEdit m_Edit_Loc;
	CEdit m_Edit_Len;
	CComboBox m_ComBox_Lib;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CBufEdit m_Edit_ByBytes;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CEdit m_Edit_bit;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();

	VOID InitInfo();
	afx_msg void OnBnClickedButton8();
	CEdit m_Edit_FormatDisplay;
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnClose();
};
