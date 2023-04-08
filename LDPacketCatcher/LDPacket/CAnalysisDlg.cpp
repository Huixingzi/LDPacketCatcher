// CAnalysisDlg.cpp: 实现文件
//

#include "pch.h"
#include "LDPacket.h"
#include "CAnalysisDlg.h"
#include "afxdialogex.h"



// CAnalysisDlg 对话框

IMPLEMENT_DYNAMIC(CAnalysisDlg, CDialog)

CAnalysisDlg::CAnalysisDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3, pParent)
{

}

CAnalysisDlg::~CAnalysisDlg()
{
}

void CAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_OrgBytes);
	DDX_Control(pDX, IDC_EDIT2, m_Edit_Char);
	DDX_Control(pDX, IDC_EDIT3, m_Edit_Loc);
	DDX_Control(pDX, IDC_EDIT4, m_Edit_Len);
	DDX_Control(pDX, IDC_COMBO1, m_ComBox_Lib);
	DDX_Control(pDX, IDC_EDIT5, m_Edit_ByBytes);
	DDX_Control(pDX, IDC_EDIT6, m_Edit_bit);
	DDX_Control(pDX, IDC_EDIT7, m_Edit_FormatDisplay);
}

VOID CAnalysisDlg::SetInfo()
{
	if (!pCsp) return;
	m_Edit_OrgBytes.pCsp = pCsp;
	m_Edit_OrgBytes.SetWindowTextW(CSOCKETPACKET::DisplayBuf(pCsp->pByte, pCsp->len));

	m_Edit_Char.SetWindowTextW(CSOCKETPACKET::DisplayChar(pCsp->pByte, pCsp->len, 8));

	//覆盖父窗口list
	CRect ParentRect;
	GetParent()->GetWindowRect(&ParentRect);

	CRect SelfRect;
	GetWindowRect(&SelfRect);

	MoveWindow(ParentRect.left + 3, ParentRect.top + 34, SelfRect.Width(), SelfRect.Height());
}


BEGIN_MESSAGE_MAP(CAnalysisDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CAnalysisDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAnalysisDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAnalysisDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAnalysisDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAnalysisDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAnalysisDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAnalysisDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAnalysisDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CAnalysisDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CAnalysisDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CAnalysisDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CAnalysisDlg::OnBnClickedButton11)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CAnalysisDlg 消息处理程序


BOOL CAnalysisDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




void CAnalysisDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_Edit_Char.SetWindowTextW(CSOCKETPACKET::DisplayChar(pCsp->pByte, pCsp->len));
}




/// <summary>
/// 压缩
/// </summary>
void CAnalysisDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString libName, str;
	m_ComBox_Lib.GetLBText(m_ComBox_Lib.GetCurSel(), libName);

	m_Edit_Loc.GetWindowTextW(str);
	int loc = _ttoi(str);

	m_Edit_Len.GetWindowTextW(str);
	int len = _ttoi(str);

	if (len == 0 || (loc + len) > pCsp->len) len = pCsp->len;

	if (libName == L"ZLib")
	{
		CZlibAlgorithm cZlib;
		cZlib.AGcompress(pCsp, loc, len);
	}

	SetInfo();
}

/// <summary>
/// 解压
/// </summary>
void CAnalysisDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString libName, str;
	m_ComBox_Lib.GetLBText(m_ComBox_Lib.GetCurSel(), libName);

	m_Edit_Loc.GetWindowTextW(str);
	int loc = _ttoi(str);

	m_Edit_Len.GetWindowTextW(str);
	int len = _ttoi(str);

	if (len == 0 || (loc + len) > pCsp->len) len = pCsp->len;

	if (libName == L"ZLib")
	{
		CZlibAlgorithm cZlib;
		cZlib.AGuncompress(pCsp, loc, len);
	}
	SetInfo();
}

/// <summary>
/// 异或
/// </summary>
void CAnalysisDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_Edit_ByBytes.GetWindowTextW(str);
	PCSOCKETPACKET pCsp_Tmp = new CSOCKETPACKET;
	CSOCKETPACKET::SetBuf(pCsp_Tmp, str);
	if (!pCsp_Tmp)return;

	m_Edit_Loc.GetWindowTextW(str);
	int loc = _ttoi(str);

	m_Edit_Len.GetWindowTextW(str);
	int len = _ttoi(str);

	if (len == 0 || (loc + len) > pCsp->len) len = pCsp->len;

	for (int i = loc; i < len;)
	{
		for (int j = 0; j < pCsp_Tmp->len && i < len; ++j, ++i)
		{
			pCsp->pByte[i] ^= pCsp_Tmp->pByte[j];
		}
	}
	SetInfo();

	delete pCsp_Tmp;
}

/// <summary>
/// 加法
/// </summary>
void CAnalysisDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_Edit_ByBytes.GetWindowTextW(str);
	PCSOCKETPACKET pCsp_Tmp = new CSOCKETPACKET;
	CSOCKETPACKET::SetBuf(pCsp_Tmp, str);
	if (!pCsp_Tmp)return;

	m_Edit_Loc.GetWindowTextW(str);
	int loc = _ttoi(str);

	m_Edit_Len.GetWindowTextW(str);
	int len = _ttoi(str);

	if (len == 0 || (loc + len) > pCsp->len) len = pCsp->len;

	for (int i = loc; i < len;)
	{
		for (int j = 0; j < pCsp_Tmp->len && i < len; ++j, ++i)
		{
			pCsp->pByte[i] += pCsp_Tmp->pByte[j];
		}
	}
	SetInfo();

	delete pCsp_Tmp;
}

/// <summary>
/// 减法
/// </summary>
void CAnalysisDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_Edit_ByBytes.GetWindowTextW(str);
	PCSOCKETPACKET pCsp_Tmp = new CSOCKETPACKET;
	CSOCKETPACKET::SetBuf(pCsp_Tmp, str);
	if (!pCsp_Tmp)return;

	m_Edit_Loc.GetWindowTextW(str);
	int loc = _ttoi(str);

	m_Edit_Len.GetWindowTextW(str);
	int len = _ttoi(str);

	if (len == 0 || (loc + len) > pCsp->len) len = pCsp->len;

	for (int i = loc; i < len;)
	{
		for (int j = 0; j < pCsp_Tmp->len && i < len; ++j, ++i)
		{
			pCsp->pByte[i] -= pCsp_Tmp->pByte[j];
		}
	}
	SetInfo();

	delete pCsp_Tmp;
}


/// <summary>
/// 左移
/// </summary>
void CAnalysisDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_Edit_bit.GetWindowTextW(str);
	if (str.Compare(L"") == 0) return;
	int bits = _ttoi(str);

	if (bits > 8 && bits < 0) return;

	m_Edit_Loc.GetWindowTextW(str);
	int loc = _ttoi(str);
	
	m_Edit_Len.GetWindowTextW(str);
	int len = _ttoi(str);

	if (len == 0 || (loc + len) > pCsp->len) len = pCsp->len;

	for (int i = loc; i < len; ++i)
	{
		pCsp->pByte[i] = pCsp->pByte[i] << bits;
	}
	SetInfo();
}

/// <summary>
/// 右移
/// </summary>
void CAnalysisDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_Edit_bit.GetWindowTextW(str);
	if (str.Compare(L"") == 0) return;
	int bits = _ttoi(str);

	if (bits > 8 && bits < 0) return;

	m_Edit_Loc.GetWindowTextW(str);
	int loc = _ttoi(str);

	m_Edit_Len.GetWindowTextW(str);
	int len = _ttoi(str);

	if (len == 0 || (loc + len) > pCsp->len) len = pCsp->len;

	for (int i = loc; i < len; ++i)
	{
		pCsp->pByte[i] = pCsp->pByte[i] >> bits;
	}
	SetInfo();
}

VOID CAnalysisDlg::InitInfo()
{
	m_Edit_Loc.SetWindowTextW(L"0");
	m_Edit_Len.SetWindowTextW(L"0");

	m_ComBox_Lib.AddString(L"ZLib");
	m_ComBox_Lib.SetCurSel(0);

	m_Edit_bit.SetWindowTextW(L"1");
}

/// <summary>
/// 初始化
/// </summary>
void CAnalysisDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pCsp) delete pCsp;
	pCsp = new CSOCKETPACKET(pCsp_Backup);
	SetInfo();
}

/// <summary>
/// json格式
/// </summary>
void CAnalysisDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str, Text;
	m_Edit_Loc.GetWindowTextW(str);
	int loc = _ttoi(str);

	PCHAR pChar = (PCHAR)(pCsp->pByte + loc);

	for (int i = 0, j = 0; i < (pCsp->len - loc); ++i)
	{
		if (pChar[i] == '}') {
			Text += L"\r\n";
			--j;
			for (int m = j; m > 0; --m) Text += L"	";
		}

		Text += pChar[i];

		if (pChar[i] == ',') {
			Text += L"\r\n";
			for (int m = j; m > 0; --m) Text += L"	";
		}
		if (pChar[i] == '{') {
			Text += L"\r\n";
			for (int m = j; m > 0; --m) Text += L"	";
			++j;
		}

		
	}
	m_Edit_FormatDisplay.SetWindowTextW(Text);

}

/// <summary>
/// Http格式
/// </summary>
void CAnalysisDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	pCsp->pByte;
	CString Text, str;
	for (int i = 0; i < pCsp->len; ++i)
	{
		str.Format(L"%c", pCsp->pByte[i]);
		Text += str;
	}
	m_Edit_FormatDisplay.SetWindowText(Text);
}

/// <summary>
/// 保存到文件
/// </summary>
void CAnalysisDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Text;
	m_Edit_FormatDisplay.GetWindowTextW(Text);

	CFileDialog fileDlg(false, _T("txt"), _T("PacketCharsInfo"), 0, _T("文本文件(*.txt)"), this);
	if (IDOK == fileDlg.DoModal())
	{
		CString Path = fileDlg.GetPathName();
		CFile file(Path.GetBuffer(), CFile::modeWrite | CFile::modeCreate);
		file.Write(Text, Text.GetLength() * sizeof(TCHAR));
		file.Close();
	}
}

/// <summary>
/// 清理数据
/// </summary>
void CAnalysisDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Edit_FormatDisplay.SetWindowTextW(L"");
	delete pCsp;

	CDialog::OnClose();
}
