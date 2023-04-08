#pragma once
#include "afxdialogex.h"

#define WM_FLUSHLIST WM_USER+200
#define WM_DELLIST WM_USER+201

// CPacketDlg 对话框

class CPacketDlg : public CDialog
{
	DECLARE_DYNAMIC(CPacketDlg)

public:
	CPacketDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPacketDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;

	CListCtrl m_ListCtrl;
	CButton m_CheckSend;
	CButton m_CheckRecv;
	CButton m_CheckSendTo;
	CButton m_CheckRecvFrom;
	CEdit m_EditRaw;
	CEdit m_EditChar;
	CEdit m_EditMinLen;
	CEdit m_EditMaxLen;
	CEdit m_EditIP;
	CButton m_CheckLen;
	CButton m_CheckIP;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg LRESULT OnFlushList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelListCtrl(WPARAM wParam, LPARAM lParam);

private:
	BOOL InitListCtrl();
	BOOL InitDlgCfg();
	VOID InitMenu();

	HMENU hMenu;
	CSendDlg SendDlg;
	CAnalysisDlg AnalysisDlg;
	VOID InitChildDialog();

	BOOL FilterLen(INT len);
	BOOL FilterIP(INT ID);
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
};
