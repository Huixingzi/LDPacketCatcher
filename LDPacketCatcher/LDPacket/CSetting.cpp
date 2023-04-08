// CSetting.cpp: 实现文件
//

#include "pch.h"
#include "LDAssist.h"
#include "CSetting.h"
#include "afxdialogex.h"

//文件保存默认文件夹
CString SavePath = _T(".\\Packet\\");

// CSetting 对话框

IMPLEMENT_DYNAMIC(CSetting, CDialog)

CSetting::CSetting(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG5, pParent)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditSavePath);
}


BEGIN_MESSAGE_MAP(CSetting, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetting::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSetting::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSetting::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CSetting::OnBnClickedButton5)
END_MESSAGE_MAP()


// CSetting 消息处理程序

//问价夹选择器
void CSetting::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFolderPickerDialog Dlg_fp;
	Dlg_fp.DoModal();
	CString str = Dlg_fp.GetFolderPath();
	m_EditSavePath.SetWindowTextW(str);
}

//应用
void CSetting::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	SavePath = SavePath + _T('\\');
	m_EditSavePath.GetWindowTextW(SavePath);
}

//保存
void CSetting::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

//初始化
void CSetting::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

}


BOOL CSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString folderPath = _T("./Packet");

	if (!PathIsDirectory(folderPath.GetBuffer()))::CreateDirectory(folderPath.GetBuffer(), 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
