
// studentmanageADlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "studentmanageA.h"
#include "studentmanageADlg.h"
#include "afxdialogex.h"
#include "student.h"
#include "managestudent.h"
#include <afxdlgs.h>
#include <afxwin.h>
#include <afxcmn.h>
#include "locale.h"
#include <CString>
#include "Cadd.h"
#include "Cchange.h"
#include <stdlib.h>
#include <math.h>
#include "Tong.h"
#include "Find.h"

using namespace std;

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


// CstudentmanageADlg 对话框



CstudentmanageADlg::CstudentmanageADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENTMANAGEA_DIALOG, pParent)
	, m_search(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CstudentmanageADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_search);
}

BEGIN_MESSAGE_MAP(CstudentmanageADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CstudentmanageADlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CstudentmanageADlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CstudentmanageADlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CstudentmanageADlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CstudentmanageADlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CstudentmanageADlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON9, &CstudentmanageADlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &CstudentmanageADlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &CstudentmanageADlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CstudentmanageADlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CstudentmanageADlg 消息处理程序

BOOL CstudentmanageADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD dwStyle = m_list.GetExtendedStyle();                    //添加列表框的网格线！！！
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_list.SetExtendedStyle(dwStyle);
	m_list.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 90);                //使用该函数的时候一定要在列名前加上_T，例如  _T("编号")，不然提示失败还找不到原因
	m_list.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 90);
	m_list.InsertColumn(2, _T("高数成绩"), LVCFMT_CENTER, 90);
	m_list.InsertColumn(3, _T("大物成绩"), LVCFMT_CENTER, 90);
	m_list.InsertColumn(4, _T("大英成绩"), LVCFMT_CENTER, 90);
	m_list.InsertColumn(5, _T("C++成绩"), LVCFMT_CENTER, 90);
	m_list.InsertColumn(6, _T("总分"), LVCFMT_CENTER, 90);


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

void CstudentmanageADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CstudentmanageADlg::OnPaint()
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
HCURSOR CstudentmanageADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CstudentmanageADlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CstudentmanageADlg::OnBnClickedButton1()                 //导入学生信息
{
	// TODO: 在此添加控件通知处理程序代码
	setlocale(LC_CTYPE, "chs");             //处理乱码函数，要加头文件 #include "locale.h"

	CString FilePathName;
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
		FilePathName = dlg.GetPathName();
	else
		return;
	CStdioFile file;
	file.Open(FilePathName, CFile::modeRead);
	CString strLine;
	m_stuArr.RemoveAll();
	while (file.ReadString(strLine))
	{
		CStringArray strarray;
		PartitionStringByCompart(strLine, ' ', strarray);      //声明之后记得定义
		CString Id = strarray.GetAt(0);
		CString name = strarray.GetAt(1);
		double math = _ttof(strarray.GetAt(2));
		double wuli = _ttof(strarray.GetAt(3));
		double English = _ttof(strarray.GetAt(4));
		double Cjj = _ttof(strarray.GetAt(5));
		student temp(Id, name, math, wuli, English, Cjj);
		m_stuArr.Add(temp);
	}
	file.Close();

	CString str;
	int i;
	m_list.DeleteAllItems();
	for (i = 0; i < m_stuArr.GetSize(); i++)
	{
		student stu = m_stuArr.GetAt(i);
		m_list.InsertItem(i, CString(""));
		m_list.SetItemText(i, 0, stu.Id);
		m_list.SetItemText(i, 1, stu.name);

		str.Format(_T("%lf"), stu.math);
		m_list.SetItemText(i, 2, str);

		str.Empty();
		str.Format(_T("%lf"), stu.wuli);
		m_list.SetItemText(i, 3, str);

		str.Empty();
		str.Format(_T("%lf"), stu.Eng);
		m_list.SetItemText(i, 4, str);
		str.Empty();
		str.Format(_T("%lf"), stu.Cjj);
		m_list.SetItemText(i, 5, str);

		str.Empty();
		str.Format(_T("%lf"), stu.wuli + stu.math + stu.Eng + stu.Cjj);
		m_list.SetItemText(i, 6, str);
		str.Empty();
	}
}


BOOL CstudentmanageADlg::PartitionStringByCompart(const CString& sOriginal, char cDivider, CStringArray& saField)            //第一次读取文件失败的原因就是因为没有对这个函数进行定义
{
	saField.RemoveAll();
	int len = sOriginal.GetLength();   //字符串长度 
	CString sTmp("");
	for (int i = 0; i < len; i++)
	{
		if (sOriginal[i] != cDivider)
			sTmp += sOriginal[i];
		else
		{
			saField.Add(sTmp);
			sTmp = _T("");
		}  
	}   
	saField.Add(sTmp);
	if (saField.GetSize() == 1)

		return false;
	return true;
}

void CstudentmanageADlg::OnBnClickedButton2()                    //排序
{
	// TODO: 在此添加控件通知处理程序代码
	int i, j;
	int n = m_stuArr.GetSize();
	student temp;
	for (i = 1; i < n; i++)
		for (j = 0; j < n - i; j++)
		{
			if (
				(
					(m_stuArr[j].math + m_stuArr[j].wuli + m_stuArr[j].Eng + m_stuArr[j].Cjj)
					<
					(m_stuArr[j+1].math + m_stuArr[j+1].wuli + m_stuArr[j+1].Eng + m_stuArr[j+1].Cjj)
					)
				||
				(
					(
						(m_stuArr[j].math + m_stuArr[j].wuli + m_stuArr[j].Eng + m_stuArr[j].Cjj) == (m_stuArr[j + 1].math + m_stuArr[j + 1].wuli + m_stuArr[j + 1].Eng + m_stuArr[j + 1].Cjj)
						)
					&&
					(m_stuArr[j].math < m_stuArr[j + 1].math)
					)
				||
				(
					((m_stuArr[j].math + m_stuArr[j].wuli + m_stuArr[j].Eng + m_stuArr[j].Cjj) == (m_stuArr[j + 1].math + m_stuArr[j + 1].wuli + m_stuArr[j + 1].Eng + m_stuArr[j + 1].Cjj)) && (m_stuArr[j].math == m_stuArr[j + 1].math) && (m_stuArr[j].wuli < m_stuArr[j + 1].wuli)
					)
				||
				(
					((m_stuArr[j].math + m_stuArr[j].wuli + m_stuArr[j].Eng + m_stuArr[j].Cjj) == (m_stuArr[j + 1].math + m_stuArr[j + 1].wuli + m_stuArr[j + 1].Eng + m_stuArr[j + 1].Cjj))
					&& (m_stuArr[j].math == m_stuArr[j + 1].math) && (m_stuArr[j].wuli == m_stuArr[j + 1].wuli) && (m_stuArr[j].Eng < m_stuArr[j + 1].Eng)
					)
				||
				(
					((m_stuArr[j].math + m_stuArr[j].wuli + m_stuArr[j].Eng + m_stuArr[j].Cjj) == (m_stuArr[j + 1].math + m_stuArr[j + 1].wuli + m_stuArr[j + 1].Eng + m_stuArr[j + 1].Cjj)) && (m_stuArr[j].math == m_stuArr[j + 1].math) && (m_stuArr[j].wuli < m_stuArr[j + 1].wuli)
					&&(m_stuArr[j].Eng==m_stuArr[j + 1].Eng)&&(m_stuArr[j].Id < m_stuArr[j + 1].Id)
					)
				)
			{
				temp = m_stuArr[j];
				m_stuArr[j] = m_stuArr[j + 1];
				m_stuArr[j + 1] = temp;
			}

		}
	m_list.DeleteAllItems();
	CString str;
	for (int k = 0; k < m_stuArr.GetSize(); k++)
	{
		student stu = m_stuArr.GetAt(k);
		m_list.InsertItem(k, _T(""));
		m_list.SetItemText(k, 0, stu.Id);
		m_list.SetItemText(k, 1, stu.name);
		str.Format(_T("%lf"), stu.math);
		m_list.SetItemText(k, 2, str);
		str.Empty();
		str.Format(_T("%lf"), stu.wuli);
		m_list.SetItemText(k, 3, str);
		str.Empty();
		str.Format(_T("%lf"), stu.Eng);
		m_list.SetItemText(k, 4, str);
		str.Empty();
		str.Format(_T("%lf"), stu.Cjj);
		m_list.SetItemText(k, 5, str);
		str.Empty();
		str.Format(_T("%lf"), stu.wuli + stu.math + stu.Eng+ stu.Cjj);
		m_list.SetItemText(k, 6, str);
		str.Empty();
	}
}


void CstudentmanageADlg::OnBnClickedButton3()                 //添加学生信息
{
	// TODO: 在此添加控件通知处理程序代码
	Cadd add;
	if (IDOK == add.DoModal())
	{
		//检查是否冲突
		for (int j = 0; j < m_stuArr.GetSize(); j++)
		{
			if (add.m_id == m_stuArr.GetAt(j).Id ||
				add.m_name == m_stuArr.GetAt(j).name)
			{
				MessageBox(_T("学号或姓名重复请重试", "失败"));
				return;
			}
		}
		student stu
		(add.m_id, add.m_name, add.m_math, add.m_wuli, add.m_Eng,add.m_Cjj);
		//在合适的位置插入
		int i;
		for (i = 0; i < m_stuArr.GetSize(); i++)
		{
			if ((stu.math + stu.wuli + stu.Eng + stu.Cjj) > (m_stuArr[i].math + m_stuArr[i].wuli + m_stuArr[i].Eng + m_stuArr[i].Cjj))
				break;
			else if ((stu.math + stu.wuli + stu.Eng + stu.Cjj) == (m_stuArr[i].math + m_stuArr[i].wuli + m_stuArr[i].Eng + m_stuArr[i].Cjj))
			{
				if (stu.math > m_stuArr.GetAt(i).math)
					break;
			}
		}
		m_stuArr.InsertAt(i, stu);
		CString str;
		m_list.InsertItem(i, _T(""));
		m_list.SetItemText(i, 0, stu.Id);
		m_list.SetItemText(i, 1, stu.name);
		str.Format(_T("%lf"), stu.math);
		m_list.SetItemText(i, 2, str);
		str.Empty();
		str.Format(_T("%lf"), stu.wuli);
		m_list.SetItemText(i, 3, str);
		str.Empty();
		str.Format(_T("%lf"), stu.Eng);
		m_list.SetItemText(i, 4, str);
		str.Empty();
		str.Format(_T("%lf"), stu.Cjj);
		m_list.SetItemText(i, 5, str);
		str.Empty();
		str.Format(_T("%lf"), stu.wuli + stu.math + stu.Eng + stu.Cjj);
		m_list.SetItemText(i, 6, str);
		str.Empty();
	}
}


void CstudentmanageADlg::OnBnClickedButton4()          //删除学生信息
{
	// TODO: 在此添加控件通知处理程序代码
	int a = m_list.GetSelectionMark();
	if (a == -1)
	{
		MessageBox(_T("请选中一行信息", "提示"));
		return;
	}
	m_list.DeleteItem(a);  //清除列表框中的元素
	m_stuArr.RemoveAt(a);     //清除数组中的元素
}


void CstudentmanageADlg::OnBnClickedButton5()         //修改学生信息
{
	// TODO: 在此添加控件通知处理程序代码
	int a = m_list.GetSelectionMark();
	if (a == -1)
	{
		MessageBox(_T("请选中一行信息", "提示"));
		return;
	}
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int index = m_list.GetNextSelectedItem(pos);
	Cchange dlg;
	dlg.c_id = m_list.GetItemText(index, 0);
	dlg.c_name = m_list.GetItemText(index, 1);
	double b = _ttof(m_list.GetItemText(index, 2));
	dlg.c_math = b;
	double c = _ttof(m_list.GetItemText(index, 3));
	dlg.c_Eng = c;
	double d = _ttof(m_list.GetItemText(index, 4));
	dlg.c_wuli = d;
	double e = _ttof(m_list.GetItemText(index, 5));
	dlg.c_Cjj = e;


	if (IDOK == dlg.DoModal())
	{
		m_list.DeleteItem(a);            //清除列表框中的元素
		m_stuArr.RemoveAt(a);                  //清除数组中的元素
		student stu
		(dlg.c_id, dlg.c_name, dlg.c_math, dlg.c_Eng, dlg.c_wuli, dlg.c_Cjj);
		//在合适的位置插入
		m_stuArr.InsertAt(a, stu);
		CString str;
		m_list.InsertItem(a, _T(""));
		m_list.SetItemText(a, 0, stu.Id);
		m_list.SetItemText(a, 1, stu.name);
		str.Format(_T("%lf"), stu.math);
		m_list.SetItemText(a, 2, str);
		str.Empty();
		str.Format(_T("%lf"), stu.wuli);
		m_list.SetItemText(a, 3, str);
		str.Empty();
		str.Format(_T("%lf"), stu.Eng);
		m_list.SetItemText(a, 4, str);
		str.Empty();
		str.Format(_T("%lf"), stu.Cjj);
		m_list.SetItemText(a, 5, str);
		str.Format(_T("%lf"), (stu.math + stu.wuli + stu.Eng + stu.Cjj));
		m_list.SetItemText(a, 6, str); int a = m_list.GetSelectionMark();
		if (a == -1)
		{
			MessageBox(_T("请选中一行信息", "提示"));
			return;
		}
		POSITION pos = m_list.GetFirstSelectedItemPosition();
		int index = m_list.GetNextSelectedItem(pos);
		Cchange dlg;
		dlg.c_id = m_list.GetItemText(index, 0);
		dlg.c_name = m_list.GetItemText(index, 1);
		double b = _ttof(m_list.GetItemText(index, 2));
		dlg.c_math = b;
		double c = _ttof(m_list.GetItemText(index, 3));
		dlg.c_Eng = c;
		double d = _ttof(m_list.GetItemText(index, 4));
		dlg.c_wuli = d;
		double e = _ttof(m_list.GetItemText(index, 5));
		dlg.c_Cjj = e;
		str.Empty();

	}
}


void CstudentmanageADlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1, str2, str3;
	UpdateData(TRUE);
	str1 = m_search;
	int i;
	for (i = 0; i < m_stuArr.GetSize(); i++)
	{
		//按姓名查找
		if (str1 == m_stuArr.GetAt(i).name)
		{
			str2 = m_stuArr.GetAt(i).Id + ' ' + m_stuArr.GetAt(i).name
				+ ' ';
			str3.Format(_T("%lf %lf %lf %lf %lf"), m_stuArr.GetAt(i).math, m_stuArr.GetAt(i).wuli,
				m_stuArr.GetAt(i).Eng, m_stuArr.GetAt(i).Cjj,m_stuArr.GetAt(i).wuli + m_stuArr.GetAt(i).math + m_stuArr.GetAt(i).Eng);
			str2 = str2 + str3;
			break;
		}
	}
	if (i != m_stuArr.GetSize()) MessageBox(str2, _T("查找成功"));
	else   MessageBox(_T("系统中没有此人信息"), _T("查找失败"));
}


void CstudentmanageADlg::OnBnClickedButton8()                //统计平均分
{ 
	//Tong dlg;
	//dlg.DoModal();
	 //TODO: 在此添加控件通知处理程序代码
	double PHYave = 0, PHYsum = 0, Eave = 0, Esum = 0, Mave = 0, Msum = 0,Csum=0,Zsum=0,Cave=0;     //平均值
	double Ma = 0, Ph = 0, Cj = 0, En = 0;        //各科方差
	double M, P, C, E;      //各科标准差
	int n = m_stuArr.GetSize();
	for (int i = 0; i < n; i++)
	{
		PHYsum = PHYsum + m_stuArr[i].wuli;
		Esum = Esum + m_stuArr[i].Eng;
		Msum = Msum + m_stuArr[i].math;
		Csum = Csum + m_stuArr[i].Cjj;
	}
	PHYave = PHYsum / n;
	Eave = Esum / n;
	Mave = Msum / n;
	Cave = Csum / n;
	Zsum = (PHYsum + Esum + Msum + Csum) / n;
	for (int k = 0;k < n; k++) {                    //求方差
		Ma = pow(m_stuArr[k].math - Mave, 2);
		En = pow(m_stuArr[k].Eng - Eave, 2);
		Ph = pow(m_stuArr[k].wuli - PHYave, 2);
		Cj = pow(m_stuArr[k].Cjj - Cave, 2);
	}                     
	M = sqrt(Ma);       
	E = sqrt(En);
	P = sqrt(Ph);
	C = sqrt(Cj);

	double Mr = 0, Pr = 0, Er = 0, Cr = 0;

	for (int i = 0; i < n; i++) {                     //求高数合格率
		if (m_stuArr[i].math > 60) {
			Mr = Mr + 1;
		}
	} 
	Mr = Mr / n;
	for (int i = 0; i < n; i++) {                     //求大物合格率
		if (m_stuArr[i].wuli > 60) {
			Pr = Pr + 1;
		}
	}
	Pr = Pr / n;
	for (int i = 0; i < n; i++) {                     //求英语合格率
		if (m_stuArr[i].Eng > 60) {
			Er = Er + 1;
		}
	}
	Er = Er / n;
	for (int i = 0; i < n; i++) {                     //求C++合格率
		if (m_stuArr[i].Cjj > 60) {
			Cr = Cr + 1;
		}
	}
	Cr = Cr / n;

	CString str1;
	str1.Format(_T("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf"), PHYave, Eave, Mave,Csum,Zsum,Pr,P,Er,E,Mr,M,Cr,C);
	MessageBox(str1, _T("物理/英语/数学/C++/三科的平均分，物理/英语/数学/C++的合格率和标准差"));
   
}


void CstudentmanageADlg::OnBnClickedButton7()                //查看全部学生名单
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"C:\\Users\\在下周帅祺呀\\Desktop\\studentmanageA\\学生成绩数据.txt", NULL, NULL, SW_SHOWNORMAL);
}


void CstudentmanageADlg::OnBnClickedButton6()               //分数段内学生查找
{
	// TODO: 在此添加控件通知处理程序代码
	Find Dlg;
	Dlg.DoModal();
}
