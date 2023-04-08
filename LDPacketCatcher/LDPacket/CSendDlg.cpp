// CSendDlg.cpp: 实现文件
//

#include "pch.h"
#include "LDPacket.h"
#include "CSendDlg.h"
#include "afxdialogex.h"


// CSendDlg 对话框

IMPLEMENT_DYNAMIC(CSendDlg, CDialog)

CSendDlg::CSendDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

CSendDlg::~CSendDlg()
{
}

void CSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_IPLoc);
	DDX_Control(pDX, IDC_EDIT2, m_Edi_IPPeer);
	DDX_Control(pDX, IDC_EDIT3, m_Edit_Sock);
	DDX_Control(pDX, IDC_EDIT4, m_Edit_Len);
	DDX_Control(pDX, IDC_EDIT5, m_Edit_Buf);
	DDX_Control(pDX, IDC_EDIT6, m_Edit_Char);
	DDX_Control(pDX, IDC_EDIT9, m_Edit_time);
	DDX_Control(pDX, IDC_EDIT8, m_Edit_Num);
	DDX_Control(pDX, IDC_LIST2, m_ListBox_File);
	DDX_Control(pDX, IDC_LIST1, m_ListBox_Send);
	DDX_Control(pDX, IDC_EDIT7, m_Edit_fileName);
}


BEGIN_MESSAGE_MAP(CSendDlg, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CSendDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSendDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CSendDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CSendDlg::OnBnClickedButton5)
	ON_LBN_DBLCLK(IDC_LIST2, &CSendDlg::OnLbnDblclkList2)
	ON_LBN_DBLCLK(IDC_LIST1, &CSendDlg::OnLbnDblclkList1)
	ON_EN_CHANGE(IDC_EDIT5, &CSendDlg::OnEnChangeEdit5)
END_MESSAGE_MAP()


// CSendDlg 消息处理程序


VOID CSendDlg::SetInfo()
{
	m_Edit_IPLoc.SetWindowTextW(CSOCKETPACKET::DisplayIP_local(pCsp->s));
	m_Edi_IPPeer.SetWindowTextW(CSOCKETPACKET::DisplayIP_peer(pCsp->s));
	m_Edit_Sock.SetWindowTextW(CSOCKETPACKET::DisplaySocket(pCsp->s));
	m_Edit_Len.SetWindowTextW(CSOCKETPACKET::DisplayLen(pCsp->len));
	m_Edit_Buf.SetWindowTextW(CSOCKETPACKET::DisplayBuf(pCsp->pByte, pCsp->len));
	m_Edit_Char.SetWindowTextW(CSOCKETPACKET::DisplayChar(pCsp->pByte, pCsp->len, 8));
	m_Edit_time.SetWindowTextW(L"100");
	m_Edit_Num.SetWindowTextW(L"1");

	//覆盖父窗口list
	CRect ParentRect;
	GetParent()->GetWindowRect(&ParentRect);

	CRect SelfRect;
	GetWindowRect(&SelfRect);

	MoveWindow(ParentRect.left + 3, ParentRect.top + 34, SelfRect.Width(), SelfRect.Height());
}


void CSendDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if (pCsp) delete pCsp;
}

//另存为
void CSendDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fileName;
	m_Edit_fileName.GetWindowTextW(fileName);

	if (fileName.Compare(L"") == 0) {
		MessageBox(L"文件名为空", L"温馨提示", 0);
		return;
	}
			
	CSOCKETPACKET::SavePacket(pCsp, fileName);
	InitFileBox();
}

//清空
void CSendDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Edit_IPLoc.SetWindowTextW(L"");
	m_Edi_IPPeer.SetWindowTextW(L"");
	m_Edit_Sock.SetWindowTextW(L"");
	m_Edit_Len.SetWindowTextW(L"");
	m_Edit_Buf.SetWindowTextW(L"");
	m_Edit_Char.SetWindowTextW(L"");
	m_Edit_fileName.SetWindowTextW(L"");
	m_Edit_time.SetWindowTextW(L"100");
	m_Edit_Num.SetWindowTextW(L"1");

}

/// <summary>
/// 发送线程
/// </summary>
/// <param name="pSendDlg"></param>
VOID SendThread(CSendDlg* pSendDlg)
{
	CString str;
	pSendDlg->m_Edit_Num.GetWindowTextW(str);
	int num = _ttoi(str);

	pSendDlg->m_Edit_time.GetWindowTextW(str);
	int interval = _ttoi(str);

	for (int i = 0; i < num; ++i)
	{
		CSOCKETPACKET::Send(pSendDlg->pCsp);
		boost::this_thread::sleep(boost::posix_time::milliseconds(interval));
	}
	
	pSendDlg->SetDlgItemTextW(IDC_BUTTON4, L"发送");
	pSendDlg->SendStatus = true;
}

//send
void CSendDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SendStatus) {
		SetDlgItemText(IDC_BUTTON4, L"停止");
		SendStatus = false;
		m_SendThread = boost::thread(SendThread, this);
	}
	else
	{
		SetDlgItemText(IDC_BUTTON4, L"发送");
		SendStatus = true;
		m_SendThread.interrupt();
		m_SendThread.join();
	}
}

/// <summary>
/// 发送队列线程
/// </summary>
/// <param name="pSendDlg"></param>
VOID SendQueThread(CSendDlg* pSendDlg)
{
	std::list<PCSOCKETPACKET> list;

	CString Sock;
	pSendDlg->m_Edit_Sock.GetWindowTextW(Sock);
	SOCKET s = _ttoi(Sock);

	for (int i = 0; i < pSendDlg->m_ListBox_Send.GetCount(); ++i)
	{
		CString fileName;
		pSendDlg->m_ListBox_Send.GetWindowTextW(fileName);
		list.push_back(new CSOCKETPACKET(s, fileName));
	}

	CString str;
	pSendDlg->m_Edit_Num.GetWindowTextW(str);
	int num = _ttoi(str);

	pSendDlg->m_Edit_time.GetWindowTextW(str);
	int interval = _ttoi(str);

	for (int i = 0; i < num; ++i)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			CSOCKETPACKET::Send(*it);
			boost::this_thread::sleep(boost::posix_time::milliseconds(interval));
		}
	}

	for (auto it = list.begin(); it != list.end(); ++it)
	{
		delete (*it);
	}

	pSendDlg->SetDlgItemTextW(IDC_BUTTON5, L"发送队列");
	pSendDlg->SendQueStatus = true;
}

//sendque
void CSendDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SendQueStatus) {
		SetDlgItemText(IDC_BUTTON5, L"停止");
		SendQueStatus = false;
		m_SendQueThread = boost::thread(SendQueThread, this);
	}
	else
	{
		SetDlgItemText(IDC_BUTTON5, L"发送队列");
		SendQueStatus = true;
		m_SendQueThread.interrupt();
		m_SendQueThread.join();
	}
}

/// <summary>
/// 添加文件到文件筐
/// </summary>
VOID CSendDlg::InitFileBox()
{

	for (int i = m_ListBox_File.GetCount(); i > 0; --i)
	{
		m_ListBox_File.DeleteString(i - 1);
	}

	for (int i = 0; i < m_ListBox_File.GetCount(); ++i)
	{
		m_ListBox_File.DeleteString(i);
	}

	CFileFind fileFind;

	BOOL bRet = fileFind.FindFile(CSOCKETPACKET::GetSaveDir() + L"*.packet");

	while (bRet)
	{
		bRet = fileFind.FindNextFile();
		if (fileFind.IsDots() | fileFind.IsDirectory()) continue;

		CString fileNameEx = fileFind.GetFileName();
		fileNameEx.Replace(L".packet", L"");

		m_ListBox_File.AddString(fileNameEx);
	}

	fileFind.Close();
}


BOOL CSendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitFileBox();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

/// <summary>
/// 双击添加到队列
/// </summary>
void CSendDlg::OnLbnDblclkList2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fileName;
	m_ListBox_File.GetText(m_ListBox_File.GetCurSel(), fileName);
	m_ListBox_Send.AddString(fileName);
}

/// <summary>
/// 双击显示详情
/// </summary>
void CSendDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fileName;
	m_ListBox_Send.GetText(m_ListBox_Send.GetCurSel(), fileName);
	if (pCsp) delete pCsp;
	pCsp = new CSOCKETPACKET(0, fileName);
	SetInfo();
}

/// <summary>
/// 改变文本后刷新char框
/// </summary>
void CSendDlg::OnEnChangeEdit5()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Edit_Char.SetWindowTextW(CSOCKETPACKET::DisplayChar(pCsp->pByte, pCsp->len));
}
