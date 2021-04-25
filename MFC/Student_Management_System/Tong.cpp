// Tong.cpp: 实现文件
//

#include "pch.h"
#include "studentmanageA.h"
#include "Tong.h"
#include "afxdialogex.h"


// Tong 对话框

IMPLEMENT_DYNAMIC(Tong, CDialogEx)

Tong::Tong(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

Tong::~Tong()
{
}

void Tong::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list2);
}


BEGIN_MESSAGE_MAP(Tong, CDialogEx)
END_MESSAGE_MAP()


// Tong 消息处理程序

BOOL Tong::OnInitDialog() {
	CDialogEx::OnInitDialog();

	DWORD dwStyle = m_list2.GetExtendedStyle();                    //添加列表框的网格线！！！
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_list2.SetExtendedStyle(dwStyle);
	m_list2.InsertColumn(0, _T(""), LVCFMT_CENTER, 90);                //使用该函数的时候一定要在列名前加上_T，例如  _T("编号")，不然提示失败还找不到原因
	m_list2.InsertColumn(1, _T("平均值"), LVCFMT_CENTER, 140);
	m_list2.InsertColumn(2, _T("合格率"), LVCFMT_CENTER, 140);
	m_list2.InsertColumn(3, _T("标准差"), LVCFMT_CENTER, 140);
	m_list2.InsertItem(0, _T("高数"));
	m_list2.InsertItem(1, _T("大英"));
	m_list2.InsertItem(2, _T("大物"));
	m_list2.InsertItem(3, _T("C++"));
	m_list2.InsertItem(4, _T("总成绩"));

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	return 0;
}
