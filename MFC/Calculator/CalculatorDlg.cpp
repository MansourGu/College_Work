
// CalculatorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

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


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	,m_input(0)
	, m_output(0)
	, m_strinput(_T(""))
	, m_stroutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_judge = 0;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_INPUT, m_input);
	//  DDX_Text(pDX, IDC_OUTPUT, m_output);
	DDX_Control(pDX, IDC_INPUT, m_editin);
	DDX_Text(pDX, IDC_INPUT, m_strinput);
	DDX_Text(pDX, IDC_OUTPUT, m_stroutput);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SUBTRACT, &CCalculatorDlg::OnBnClickedSubtract)
	ON_BN_CLICKED(IDC_ADD, &CCalculatorDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DIVIDE, &CCalculatorDlg::OnBnClickedDivide)
	ON_BN_CLICKED(IDC_MULTIPLE, &CCalculatorDlg::OnBnClickedMultiple)
	ON_BN_CLICKED(IDC_EQUAL, &CCalculatorDlg::OnBnClickedEqual)
//	ON_WM_KEYDOWN()
//	ON_BN_CLICKED(IDC_NUM1, &CCalculatorDlg::OnBnClickedNum1)
ON_WM_CHAR()
ON_BN_CLICKED(IDOK, &CCalculatorDlg::OnBnClickedOk)
ON_BN_CLICKED(IDOK, &CCalculatorDlg::OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, &CCalculatorDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
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

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnBnClickedSubtract()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_input == 0&&m_judge!=0)
	{
		m_judge = 1;
		return;
	}

	switch (m_judge)
	{
	case 0:UpdateData(false); m_output = m_input;
		break;
	case 1:m_output -= m_input;
		break;
	case 2:m_output += m_input;
		break;
	case 3:
		if (m_output != 0 && m_input != 0)
			m_output /= m_input;
		else
		{
			AfxMessageBox("除数不能为0请重新输入");
			m_judge = 3;
			m_input = 0;
			m_strinput.Empty();
			UpdateData(false);
			return;
		}
		break;
	case 4:m_output *= m_input;
		break;
	}
	m_judge = 1;
	m_input = 0;
	m_strinput.Empty();
	m_stroutput.Format("%.2f", m_output);
	UpdateData(false);
}


void CCalculatorDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_input == 0 && m_judge != 0)
	{
		m_judge = 2;
		return;
	}
	switch (m_judge)
	{
	case 0:UpdateData(false); m_output = m_input;
		break;
	case 1:m_output -= m_input;
		break;
	case 2:m_output += m_input;
		break;
	case 3:
		if (m_output != 0 && m_input != 0)
			m_output /= m_input;
		else
		{
			AfxMessageBox("除数不能为0请重新输入");
			m_judge = 3;
			m_input = 0;
			m_strinput.Empty();
			UpdateData(false);
			return;
		}
		break;
	case 4:m_output *= m_input;
		break;
	}
	m_input = 0;
	m_judge = 2;
	m_strinput.Empty();
	m_stroutput.Format("%.2f", m_output);
	UpdateData(false);
}


void CCalculatorDlg::OnBnClickedDivide()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_input == 0 && m_judge != 0)
	{
		m_judge = 3;
		return;
	}
	switch (m_judge)
	{
	case 0:UpdateData(false); m_output = m_input;
		break;
	case 1:m_output -= m_input;
		break;
	case 2:m_output += m_input;
		break;
	case 3:
		if (m_output != 0 && m_input != 0)
			m_output /= m_input;
		else
		{
			AfxMessageBox("除数不能为0请重新输入");
		m_judge = 3;
		m_input = 0;
		m_strinput.Empty();
		UpdateData(false);
		return;
		}
		break;
	case 4:m_output *= m_input;
		break;
	}
	m_input = 0;
	m_judge = 3;
	m_strinput.Empty();
	m_stroutput.Format("%.2f", m_output);
	UpdateData(false);
}


void CCalculatorDlg::OnBnClickedMultiple()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_input == 0 && m_judge != 0)
	{
		m_judge = 4;
		return;
	}
	switch (m_judge)
	{
	case 0:UpdateData(false); m_output = m_input;
		break;
	case 1:m_output -= m_input;
		break;
	case 2:m_output += m_input;
		break;
	case 3:
		if (m_output != 0 && m_input != 0)
			m_output /= m_input;
		else 
		{
			AfxMessageBox("除数不能为0请重新输入");
			m_judge = 3;
			m_input = 0;
			m_strinput.Empty();
			UpdateData(false);
			return;
		}
		break;
	case 4:m_output *= m_input;
		break;
	}
	m_input = 0;
	m_judge = 4;
	m_strinput.Empty();
	UpdateData(false);
}


void CCalculatorDlg::OnBnClickedEqual()
{
	UpdateData();
	switch (m_judge)
	{
	case 0:UpdateData(false); m_output = m_input;
		break;
	case 1:m_output -= m_input;
		break;
	case 2:m_output += m_input;
		break;
	case 3:
		if (m_output != 0 && m_input != 0)
			m_output /= m_input;
		else
		{
			AfxMessageBox("除数不能为0请重新输入");
			m_judge = 3;
			m_input = 0;
			m_strinput.Empty();
			UpdateData(false);
			return;
		}
		break;
	case 4:m_output *= m_input;
		break;
	}
	m_input = 0;
	m_judge = 0;
	m_strinput.Empty();
	m_stroutput.Format("%.2f", m_output);
	UpdateData(false);
	m_output = 0;
	m_stroutput.Empty();
	
	// TODO: 在此添加控件通知处理程序代码
}

void CCalculatorDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case '+':GetDlgItem(IDC_ADD)->SetFocus();
		m_input = _ttof((TCHAR *)(LPTSTR)(LPCTSTR)m_strinput);
		OnBnClickedAdd();
		break;
	case '-':GetDlgItem(IDC_SUBTRACT)->SetFocus();
		m_input = _ttof((TCHAR *)(LPTSTR)(LPCTSTR)m_strinput);
		OnBnClickedSubtract();
		break;
	case '*':GetDlgItem(IDC_MULTIPLE)->SetFocus();
		m_input = _ttof((TCHAR *)(LPTSTR)(LPCTSTR)m_strinput);
		OnBnClickedMultiple();
		break;
	case '/':GetDlgItem(IDC_DIVIDE)->SetFocus();
		m_input = _ttof((TCHAR *)(LPTSTR)(LPCTSTR)m_strinput);
		OnBnClickedDivide();
		break;
	case '1':GetDlgItem(IDC_NUM1)->SetFocus();
		m_strinput += '1';
		UpdateData(false);
		break;
	case'2':GetDlgItem(IDC_NUM2)->SetFocus();
		m_strinput += '2';
		UpdateData(false);
		break;
	case'3':GetDlgItem(IDC_NUM3)->SetFocus();
		m_strinput += '3';
		UpdateData(false);
		break;
	case'4':GetDlgItem(IDC_NUM4)->SetFocus();
		m_strinput += '4';
		UpdateData(false);
		break;
	case'5':GetDlgItem(IDC_NUM5)->SetFocus();
		m_strinput += '5';
		UpdateData(false);
		break;
	case'6':GetDlgItem(IDC_NUM6)->SetFocus();
		m_strinput += '6';
		UpdateData(false);
		break;
	case'7':GetDlgItem(IDC_NUM7)->SetFocus();
		m_strinput += '7';
		UpdateData(false);
		break;
	case'8':GetDlgItem(IDC_NUM8)->SetFocus();
		m_strinput += '8';
		UpdateData(false);
		break;
	case'9':GetDlgItem(IDC_NUM9)->SetFocus();
		m_strinput += '9';
		UpdateData(false);
		break;
	case'0':GetDlgItem(IDC_NUM0)->SetFocus();
		m_strinput += '0';
		UpdateData(false);
		break;
	case'=':GetDlgItem(IDC_EQUAL)->SetFocus();
		m_input = _ttof((TCHAR *)(LPTSTR)(LPCTSTR)m_strinput);
		OnBnClickedEqual();
		break;
	case'.':m_strinput+='.';
		UpdateData(false);
		break;
	case 8:m_strinput = m_strinput.Left(m_strinput.GetLength() - 1);
		UpdateData(false);
		break;
	case 13:GetDlgItem(IDC_EQUAL)->SetFocus();
		m_input = _ttof((TCHAR *)(LPTSTR)(LPCTSTR)m_strinput);
		OnBnClickedEqual();
		break;
	case 27:
		OnBnClickedCancel();
		break;
	}
	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	return 0;
	//return CDialog::PreTranslateMessage(pMsg);
}


//void CCalculatorDlg::OnBnClickedOk()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	GetDlgItem(IDC_EQUAL)->SetFocus();
//	OnBnClickedEqual();
//};


void CCalculatorDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}


void CCalculatorDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


//void CCalculatorDlg::OnEnChangeInput()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
