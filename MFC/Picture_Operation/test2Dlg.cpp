
// test2Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "test2.h"
#include "test2Dlg.h"
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


// Ctest2Dlg 对话框



Ctest2Dlg::Ctest2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST2_DIALOG, pParent)
	, m_edit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(Ctest2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Ctest2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Ctest2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Ctest2Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Ctest2Dlg 消息处理程序

BOOL Ctest2Dlg::OnInitDialog()
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

void Ctest2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctest2Dlg::OnPaint()
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
HCURSOR Ctest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest2Dlg::show_image(Mat& imgSrc, HWND hwnd,int judge)//正向
{
	HDC hdc = ::GetDC(hwnd);


	//获取图片控件矩形框

	GetDlgItem(IDC_SHOWIMAGE)->GetClientRect(&rect);

	//缩放Mat，以适应图片控件大小

	cv::resize(imgSrc, imgSrc, cv::Size(rect.Width(), rect.Height()));

	//cv::resize(imgSrc, imgSrc, cv::Size(300, 300));

	// 转换格式 ,便于获取BITMAPINFO

	switch (imgSrc.channels())

	{

	case 1:

		cv::cvtColor(imgSrc, imgSrc, COLOR_GRAY2BGRA);

		break;

	case 3:

		cv::cvtColor(imgSrc, imgSrc, COLOR_BGR2BGRA);

		break;

	default:

		break;

	}

	// 计算一个像素多少个字节

	int pixelBytes = imgSrc.channels()*(imgSrc.depth() + 1);

	// 制作bitmapinfo(数据头)


	bitInfo.bmiHeader.biBitCount = 8 * pixelBytes;

	bitInfo.bmiHeader.biWidth = imgSrc.cols;

	bitInfo.bmiHeader.biHeight = imgSrc.rows * judge;

	bitInfo.bmiHeader.biPlanes = 1;

	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

	bitInfo.bmiHeader.biCompression = BI_RGB;

	bitInfo.bmiHeader.biClrImportant = 0;

	bitInfo.bmiHeader.biClrUsed = 0;

	bitInfo.bmiHeader.biSizeImage = 0;

	bitInfo.bmiHeader.biXPelsPerMeter = 0;

	bitInfo.bmiHeader.biYPelsPerMeter = 0;

	CDC *pDC = GetDlgItem(IDC_SHOWIMAGE)->GetDC();

	//绘图

	::StretchDIBits(

		pDC->GetSafeHdc(),

		0, 0, rect.Width(), rect.Height(),

		0, 0, imgSrc.cols, imgSrc.rows,

		imgSrc.data,

		&bitInfo,

		DIB_RGB_COLORS,

		SRCCOPY

	);

	ReleaseDC(pDC);

}


void Ctest2Dlg::OnBnClickedButton1()
{

	HWND hwnd = GetDlgItem(IDC_SHOWIMAGE)->GetSafeHwnd();
	// 获取显示的图像
	Mat img = imread("C:/Users/hasee/Desktop/1.jpg");
	// 调用显示函数
	show_image(img, hwnd,judge);
	// TODO: 在此添加控件通知处理程序代码
}


void Ctest2Dlg::OnBnClickedButton2()
{
	Mat src;
	CString filter;
	CString path;
	filter = "All Files (*.*)|*.*|JPGtu图片(*.jpg)|*.jpg|BMP图像(*.bmp)|*.bmp|PNG图片(*.png)|*.png||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	if (dlg.DoModal() != IDOK)
	{
		MessageBoxA( "does not chose image", "出错！", IDOK);
		return;
	}
	path = dlg.GetPathName();
	path.Replace(_T("\\"), _T("\\\\"));//转移字符的转换       
	memset(path1, 0, sizeof(path1));
	int k = path.GetAllocLength();
	for (int i = 0; path[i] != 0; i++)
	{
		path1[i] = path[i];
	}

	src = imread(path1);
	m_edit = path1;
	UpdateData(false);
	if (!src.data)
	{
		MessageBoxA( "could not load picture", "出错！", IDOK);
		return;
	}
	HWND hwnd = GetDlgItem(IDC_SHOWIMAGE)->GetSafeHwnd();
	show_image(src, hwnd,judge);
}


void Ctest2Dlg::OnBnClickedButton3()//反转
{
	// TODO: 在此添加控件通知处理程序代码
	Mat src;
	src = imread(path1);
	HWND hwnd = GetDlgItem(IDC_SHOWIMAGE)->GetSafeHwnd();
	judge *= (-1);
	show_image(src, hwnd, judge);

}


//void Ctest2Dlg::show_image_reverse(Mat& imgSrc, HWND hwnd)
//{
//	// TODO: 在此处添加实现代码.
//	HDC hdc = ::GetDC(hwnd);
//
//
//	//获取图片控件矩形框
//
//	GetDlgItem(IDC_SHOWIMAGE)->GetClientRect(&rect);
//
//	//缩放Mat，以适应图片控件大小
//
//	cv::resize(imgSrc, imgSrc, cv::Size(rect.Width(), rect.Height()));
//
//	//cv::resize(imgSrc, imgSrc, cv::Size(300, 300));
//
//	// 转换格式 ,便于获取BITMAPINFO
//
//	switch (imgSrc.channels())
//
//	{
//
//	case 1:
//
//		cv::cvtColor(imgSrc, imgSrc, COLOR_GRAY2BGRA);
//
//		break;
//
//	case 3:
//
//		cv::cvtColor(imgSrc, imgSrc, COLOR_BGR2BGRA);
//
//		break;
//
//	default:
//
//		break;
//
//	}
//
//	// 计算一个像素多少个字节
//
//	int pixelBytes = imgSrc.channels()*(imgSrc.depth() + 1);
//
//	// 制作bitmapinfo(数据头)
//
//
//	bitInfo.bmiHeader.biBitCount = 8 * pixelBytes;
//
//	bitInfo.bmiHeader.biWidth = imgSrc.cols;
//
//	bitInfo.bmiHeader.biHeight = imgSrc.rows;
//
//	bitInfo.bmiHeader.biPlanes = 1;
//
//	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//
//	bitInfo.bmiHeader.biCompression = BI_RGB;
//
//	bitInfo.bmiHeader.biClrImportant = 0;
//
//	bitInfo.bmiHeader.biClrUsed = 0;
//
//	bitInfo.bmiHeader.biSizeImage = 0;
//
//	bitInfo.bmiHeader.biXPelsPerMeter = 0;
//
//	bitInfo.bmiHeader.biYPelsPerMeter = 0;
//
//	CDC *pDC = GetDlgItem(IDC_SHOWIMAGE)->GetDC();
//
//	//绘图
//
//	::StretchDIBits(
//
//		pDC->GetSafeHdc(),
//
//		0, 0, rect.Width(), rect.Height(),
//
//		0, 0, imgSrc.cols, imgSrc.rows,
//
//		imgSrc.data,
//
//		&bitInfo,
//
//		DIB_RGB_COLORS,
//
//		SRCCOPY
//
//	);
//
//	ReleaseDC(pDC);
//}
