#pragma once


// CSendDlg 对话框

class CSendDlg : public CDialog
{
	DECLARE_DYNAMIC(CSendDlg)

public:
	CSendDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSendDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public: 
	PCSOCKETPACKET pCsp;
	VOID SetInfo();

	afx_msg void OnDestroy();

	CEdit m_Edit_IPLoc;
	CEdit m_Edi_IPPeer;
	CEdit m_Edit_Sock;
	CEdit m_Edit_Len;
	CBufEdit m_Edit_Buf;
	CEdit m_Edit_Char;
	CEdit m_Edit_fileName;
	CEdit m_Edit_time;
	CEdit m_Edit_Num;

	CListBox m_ListBox_File;
	CListBox m_ListBox_Send;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

	boost::thread m_SendThread;
	boost::thread m_SendQueThread;

	bool SendStatus = TRUE;
	bool SendQueStatus = TRUE;

	VOID InitFileBox();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkList2();
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnEnChangeEdit5();
};
