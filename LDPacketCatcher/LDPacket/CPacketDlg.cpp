// CPacketDlg.cpp: 实现文件
//

#include "pch.h"
#include "LDPacket.h"
#include "CPacketDlg.h"
#include "CSocketPacket.h"

#define MAXNUM 2048


//全局变量声明
INT ID_packet = 0;
PCSOCKETPACKET szPCSP[MAXNUM] = { 0 };
extern CPacketDlg* pMainDlg;

//储存封包
bool SavePacket(SOCKET s, const char* pbuf, int len, SocketType type)
{
	INT ID = ID_packet % MAXNUM;

	if (ID_packet >= MAXNUM)
	{
		delete szPCSP[ID];
	}

	szPCSP[ID] = new CSocketPacket(s, (PBYTE)pbuf, len, type);

	INT _ID_packet = ID_packet;
	::PostMessage(pMainDlg->m_hWnd, WM_FLUSHLIST, 0, _ID_packet);

	++ID_packet;
	return TRUE;
}

// CPacketDlg 对话框
IMPLEMENT_DYNAMIC(CPacketDlg, CDialog)

CPacketDlg::CPacketDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CPacketDlg::~CPacketDlg()
{
}

void CPacketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_CHECK1, m_CheckSend);
	DDX_Control(pDX, IDC_CHECK3, m_CheckRecv);
	DDX_Control(pDX, IDC_CHECK2, m_CheckSendTo);
	DDX_Control(pDX, IDC_CHECK4, m_CheckRecvFrom);
	DDX_Control(pDX, IDC_CHECK5, m_CheckLen);
	DDX_Control(pDX, IDC_CHECK6, m_CheckIP);
	DDX_Control(pDX, IDC_EDIT1, m_EditRaw);
	DDX_Control(pDX, IDC_EDIT2, m_EditChar);
	DDX_Control(pDX, IDC_EDIT3, m_EditMinLen);
	DDX_Control(pDX, IDC_EDIT4, m_EditMaxLen);
	DDX_Control(pDX, IDC_EDIT5, m_EditIP);

}

BEGIN_MESSAGE_MAP(CPacketDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPacketDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPacketDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPacketDlg::OnBnClickedButton3)
	ON_MESSAGE(WM_FLUSHLIST, &CPacketDlg::OnFlushList)
	ON_MESSAGE(WM_DELLIST, &CPacketDlg::OnDelListCtrl)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPacketDlg::OnNMClickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CPacketDlg::OnNMRClickList1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPacketDlg 消息处理程序

//开始
void CPacketDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	StartHook();
}

//重捕
void CPacketDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListCtrl.DeleteAllItems();
	StartHook();
}

//结束
void CPacketDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	StopHook();
}

//初始化列表框
BOOL CPacketDlg::InitListCtrl()
{
	m_ListCtrl.InsertColumn(0, L"序号", 0, 80);
	m_ListCtrl.InsertColumn(1, L"方式", 0, 80);
	m_ListCtrl.InsertColumn(2, L"发送端", 0, 220);
	m_ListCtrl.InsertColumn(3, L"接收端", 0, 220);
	m_ListCtrl.InsertColumn(4, L"数据", 0, 308);
	m_ListCtrl.InsertColumn(5, L"长度", 0, 80);
	m_ListCtrl.InsertColumn(6, L"套接字", 0, 84);

	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;
}

//初始化对话框
BOOL CPacketDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置图标
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(m_hIcon, TRUE);            // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	//设置标题
	InitListCtrl();
	InitDlgCfg();
	InitMenu();
	InitChildDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

VOID CPacketDlg::InitChildDialog()
{
	SendDlg.Create(IDD_DIALOG2, this);
	AnalysisDlg.Create(IDD_DIALOG3, this);
}

VOID CPacketDlg::InitMenu()
{
	hMenu = ::CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, 10001, _T("转到发送窗"));
	AppendMenu(hMenu, MF_STRING, 10002, _T("转到解析窗"));
	AppendMenu(hMenu, MF_STRING, 10003, _T("取消"));
}

//初始化界面配置
BOOL CPacketDlg::InitDlgCfg()
{
	m_CheckSend.SetCheck(1);
	m_CheckRecv.SetCheck(1);
	m_CheckSendTo.SetCheck(0);
	m_CheckRecvFrom.SetCheck(0);

	m_CheckLen.SetCheck(1);
	m_EditMinLen.SetWindowTextW(L"0");
	m_EditMaxLen.SetWindowTextW(L"2048");

	m_CheckIP.SetCheck(0);
	m_EditIP.SetWindowTextW(L"0.0.0.0");

	return TRUE;
}

//刷新工作函数
LRESULT CPacketDlg::OnFlushList(WPARAM wParam, LPARAM lParam)
{
	INT ID = (INT)lParam;
	
	PCSOCKETPACKET pCsp = szPCSP[ID % MAXNUM];
	
	//过滤方式
	if (!m_CheckSend.GetCheck() && pCsp->type == SocketType::Send) return LRESULT();
	if (!m_CheckRecv.GetCheck() && pCsp->type == SocketType::Recv) return LRESULT();
	if (!m_CheckSendTo.GetCheck() && pCsp->type == SocketType::SendTo) return LRESULT();
	if (!m_CheckRecvFrom.GetCheck() && pCsp->type == SocketType::RecvFrom) return LRESULT();

	//过滤长度
	if (m_CheckLen.GetCheck() && !FilterLen(pCsp->len)) return LRESULT();

	//锁定IP
	if (m_CheckIP.GetCheck() && !FilterIP(ID)) return LRESULT();

	//获得当前行数
	INT Count = m_ListCtrl.GetItemCount();
	INT Column = 0;

	//删除
	if (szPCSP[MAXNUM - 1])PostMessage(WM_DELLIST, 0, ID);

	CString str;
	str.Format(L"%d", ID);
	m_ListCtrl.InsertItem(Count, str);

	m_ListCtrl.SetItemText(Count, ++Column, CSOCKETPACKET::DisplayType(pCsp->type));
	
	m_ListCtrl.SetItemText(Count, ++Column, pCsp->LocAddr);
	m_ListCtrl.SetItemText(Count, ++Column, pCsp->PeerAddr);

	m_ListCtrl.SetItemText(Count, ++Column, CSOCKETPACKET::DisplayBuf(pCsp->pByte, pCsp->len, 10));

	m_ListCtrl.SetItemText(Count, ++Column, CSOCKETPACKET::DisplayLen(pCsp->len));

	m_ListCtrl.SetItemText(Count, ++Column, CSOCKETPACKET::DisplaySocket(pCsp->s));

	return LRESULT();
}

LRESULT CPacketDlg::OnDelListCtrl(WPARAM wParam, LPARAM lParam)
{
	INT ID = (INT)lParam;
	INT Count = m_ListCtrl.GetItemCount();
	for (INT i = 0; i < Count; ++i)
	{
		INT ITEM_ID = _ttoi(m_ListCtrl.GetItemText(i, 0));
		if (ITEM_ID <= ID - MAXNUM)
		{
			m_ListCtrl.DeleteItem(i);
		}
		else
		{
			break;
		}
	}

	return LRESULT();
}

//过滤长度
BOOL CPacketDlg::FilterLen(INT len)
{
	CString cMinLen, cMaxLen;
	m_EditMinLen.GetWindowTextW(cMinLen);
	int minlen = _ttoi(cMinLen);
	m_EditMaxLen.GetWindowTextW(cMaxLen);
	int maxlen = _ttoi(cMaxLen);

	if (len < maxlen && len > minlen) return TRUE;
	return FALSE;
}

//锁定IP
BOOL CPacketDlg::FilterIP(INT ID)
{
	CString IP;
	m_EditIP.GetWindowTextW(IP);

	if (CSOCKETPACKET::DisplayIP_peer(szPCSP[ID]->s).Compare(IP) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

//点击显示详细信息
void CPacketDlg::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	if (pNMItemActivate->iItem == -1) return;

	INT ID = _ttoi(m_ListCtrl.GetItemText(pNMItemActivate->iItem, 0));

	PCSOCKETPACKET pCsp = szPCSP[ID % MAXNUM];

	m_EditRaw.SetWindowTextW(CSocketPacket::DisplayBuf(pCsp->pByte, pCsp->len));
	m_EditChar.SetWindowTextW(CSocketPacket::DisplayChar(pCsp->pByte, pCsp->len, 12));

	*pResult = 0;
}

//右键菜单
void CPacketDlg::OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	//无项目退出
	if (pNMItemActivate->iItem == -1) return;
	// TODO: 在此添加控件通知处理程序代码

	//暂停捕获
	StopHook();

	//TO DO
	CPoint pt;
	GetCursorPos(&pt); //获得当前鼠标位置

	UINT Cmd = (UINT)::TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, 0, m_hWnd, NULL);//弹出菜单

	INT ID = _ttoi(m_ListCtrl.GetItemText(pNMItemActivate->iItem, 0)); //获得该行ID

	switch (Cmd)//响应点击的菜单
	{
	case 10001:
		//发送窗口指针,只能单独创建一个发送窗口
		SendDlg.pCsp = new CSOCKETPACKET(szPCSP[ID % MAXNUM]);
		SendDlg.SetInfo();
		SendDlg.ShowWindow(SW_SHOW);
		break;
	case 10002:
		AnalysisDlg.pCsp = new CSOCKETPACKET(szPCSP[ID % MAXNUM]);
		AnalysisDlg.pCsp_Backup = new CSOCKETPACKET(szPCSP[ID % MAXNUM]);
		AnalysisDlg.SetInfo();
		AnalysisDlg.ShowWindow(SW_SHOW);
		break;
	case 10003:

		break;
	default:
		break;
	}

	*pResult = 0;
}

void CPacketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC   dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);  //对话框的背景图片  

		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		CDialog::OnPaint();
	}
}

HBRUSH CPacketDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(33, 66, 66));
		pDC->SetBkMode(TRANSPARENT);

		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CPacketDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	SendDlg.DestroyWindow();
}
