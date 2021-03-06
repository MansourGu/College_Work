
// ListDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "List.h"
#include "ListDlg.h"
#include "afxdialogex.h"
#include"BaseList.h"
#include"LinkList.h"
#include"SeqList.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CListDlg 对话框



CListDlg::CListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIST_DIALOG, pParent)
	, OUTPUT(_T(""))
	, Tips(_T(""))
	, INPUT(_T(""))
	, Object(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OUTPUT, OUTPUT);
	DDX_Text(pDX, IDC_Tips, Tips);
	DDX_Text(pDX, IDC_INPUT, INPUT);
	DDX_Text(pDX, IDC_EDIT4, Object);
}

BEGIN_MESSAGE_MAP(CListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SWITCH, &CListDlg::OnBnClickedSwitch)
	ON_BN_CLICKED(IDC_ADD, &CListDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CListDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_INSERT, &CListDlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_REVERSE, &CListDlg::OnBnClickedReverse)
END_MESSAGE_MAP()


// CListDlg 消息处理程序

BOOL CListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CListDlg::OnPaint()
{
	Tips = "添加： 输入一串数从后插入链表/顺序表 '\n' 删除（插入）操作 ：输入两个数 第一个数是要找的元素值 第二个数是要插入的值";
	switch (judge)
	{
	case 1:Object = "顺序表"; break;
	case -1:Object = "单链表"; break;
	}
	UpdateData(false);
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListDlg::OnBnClickedSwitch()
{
	judge = -judge;
	Display();
}


void CListDlg::OnBnClickedAdd()
{
	if (judge == 1)
	{
		UpdateData();
		CString temp ="";
		for (int i = 0; i < INPUT.GetLength(); i++)
		{
			if (INPUT[i]==' ')
			{
				input_get.push_back(temp);
				temp = "";
				continue;
			}
			temp += INPUT[i];
			if (INPUT.GetLength()-1 == i)
			{
				input_get.push_back(temp);
			}
		}
		for (int i = 0; i < input_get.size(); i++)
		{
			if (input_get[i]=="")
			{
				continue;
			}
			int tem = _ttoi(input_get[i]);
			sl_vec.push_back(tem);
		}
		for (int i = 0; i < sl_vec.size(); i++)
		{
			sl.Add(sl_vec[i]);
		}
		input_get.clear();
		sl_vec.clear();
		INPUT = "";
		UpdateData(false);
	}
	if (judge == -1)
	{
		UpdateData();
		CString temp = "";
		for (int i = 0; i < INPUT.GetLength(); i++)
		{
			if (INPUT[i] == ' ')
			{
				input_get.push_back(temp);
				temp = "";
				continue;
			}
			temp += INPUT[i];
			if (INPUT.GetLength() - 1 == i)
			{

				input_get.push_back(temp);
			}
		}
		for (int i = 0; i < input_get.size(); i++)
		{
			if (input_get[i] == "")
			{
				continue;
			}
			int tem = _ttoi(input_get[i]);
			ll_vec.push_back(tem);
		}
		for (int i = 0; i < ll_vec.size(); i++)
		{
			ll.Add(ll_vec[i]);
		}
		input_get.clear();
		ll_vec.clear();
		INPUT = "";
		UpdateData(false);
	}
	Display();
}




void CListDlg::Display()
{
	if (judge ==1 )
	{
		if (sl.IsEmpty())
		{
			OUTPUT = "";
			Object = "顺序表";
			UpdateData(false);
			return;
		}
		Object = "顺序表";
		OUTPUT = sl.Show();
		UpdateData(false);

	}
	if (judge == -1)
	{
		if (ll.IsEmpty())
		{
			OUTPUT = "";
			Object = "单链表";
			UpdateData(false);
			return;
		}
		OUTPUT = ll.Show();
		Object = "单链表";
		UpdateData(false);
	}
	return;
}


void CListDlg::OnBnClickedDelete()
{
	if (judge == 1)
	{
		UpdateData();
		CString temp = "";
		for (int i = 0; i < INPUT.GetLength(); i++)
		{
			if (INPUT[i] == ' ')
			{
				input_get.push_back(temp);
				temp = "";
				continue;
			}
			temp += INPUT[i];
			if (INPUT.GetLength() - 1 == i)
			{
				input_get.push_back(temp);
			}
		}
		for (int i = 0; i < input_get.size(); i++)
		{
			if (input_get[i] == "")
			{
				continue;
			}
			int tem = _ttoi(input_get[i]);
			sl_vec.push_back(tem);
		}
		for (int i = 0; i < sl_vec.size(); i++)
		{
			sl.Delete(sl_vec[i]);
		}
		input_get.clear();
		sl_vec.clear();
		INPUT = "";
		UpdateData(false);
	}
	if (judge == -1)
	{
		UpdateData();
		CString temp = "";
		for (int i = 0; i < INPUT.GetLength(); i++)
		{
			if (INPUT[i] == ' ')
			{
				input_get.push_back(temp);
				temp = "";
				continue;
			}
			temp += INPUT[i];
			if (INPUT.GetLength() - 1 == i)
			{
				input_get.push_back(temp);
			}
		}
		for (int i = 0; i < input_get.size(); i++)
		{
			if (input_get[i] == "")
			{
				continue;
			}
			int tem = _ttoi(input_get[i]);
			ll_vec.push_back(tem);
		}
		for (int i = 0; i < ll_vec.size(); i++)
		{
			ll.Delete(ll_vec[i]);
		}
		input_get.clear();
		ll_vec.clear();
		INPUT = "";
		UpdateData(false);
	}
	Display();
}


void CListDlg::OnBnClickedInsert()
{
	if (judge == 1)
	{
		UpdateData();
		CString temp = "";
		for (int i = 0; i < INPUT.GetLength(); i++)
		{
			if (INPUT[i] == ' ')
			{
				input_get.push_back(temp);
				temp = "";
					continue;
			}
			temp += INPUT[i];
			if (INPUT.GetLength() - 1 == i)
			{
				input_get.push_back(temp);
			}
		}
		for (int i = 0; i < input_get.size(); i++)
		{
			if (input_get[i] == "")
			{
				continue;
			}
			int tem = _ttoi(input_get[i]);
			sl_vec.push_back(tem);
		}
		for (int i = sl_vec.size() - 2; i >= 0; i--)
		{
			sl.Insert(sl_vec[i],sl_vec[sl_vec.size()-1]);
		}
		input_get.clear();
		sl_vec.clear();
		INPUT = "";
		UpdateData(false);
	}
	if (judge == -1)
	{
		UpdateData();
		CString temp = "";
		for (int i = 0; i < INPUT.GetLength(); i++)
		{
			if (INPUT[i] == ' ')
			{
				input_get.push_back(temp);
				temp = "";
				continue;
			}
			temp += INPUT[i];
			if (INPUT.GetLength() - 1 == i)
			{
				input_get.push_back(temp);
			}
		}
		for (int i = 0; i < input_get.size(); i++)
		{
			if (input_get[i] == "")
			{
				continue;
			}
			int tem = _ttoi(input_get[i]);
			ll_vec.push_back(tem);
		}
		for (int i = ll_vec.size() - 2; i >= 0; i--)
		{
			ll.Insert(ll_vec[i], ll_vec[ll_vec.size() - 1]);
		}
		input_get.clear();
		ll_vec.clear();
		INPUT = "";
		UpdateData(false);
	}
	Display();
}


void CListDlg::OnBnClickedReverse()
{
	if (judge ==1)
	{
		sl.Reverse();
	}
	if (judge == -1)
	{
		ll.Reverse();
	}
	Display();
}
