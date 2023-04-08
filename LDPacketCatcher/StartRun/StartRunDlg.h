
// StartRunDlg.h: 头文件
//

#pragma once


// CStartRunDlg 对话框
class CStartRunDlg : public CDialogEx
{
// 构造
public:
	CStartRunDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTRUN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	VOID ListAllProcess();
	CListCtrl m_ListCtrl;
	afx_msg void OnNMDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
};
