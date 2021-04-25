// Find.cpp: 实现文件
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
// Find 对话框

IMPLEMENT_DYNAMIC(Find, CDialogEx)

Find::Find(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_left(0)
	, m_right(0)
{

}

Find::~Find()
{
}

void Find::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_left);
	//  DDX_Text(pDX, IDC_EDIT2, m);
	DDX_Text(pDX, IDC_EDIT2, m_right);
	DDX_Control(pDX, IDC_COMBO2, m_cb);
}


BEGIN_MESSAGE_MAP(Find, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &Find::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Find::OnBnClickedButton3)
END_MESSAGE_MAP()


// Find 消息处理程序

BOOL Find::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_cb.AddString(_T("math"));   //添加字符串  
	m_cb.AddString(_T("Eng"));
	m_cb.AddString(_T("wuli"));
	m_cb.AddString(_T("Cjj"));

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
BOOL PartitionStringByCompart(const CString& sOriginal, char cDivider, CStringArray& saField)     //第一次读取文件失败的原因就是因为没有对这个函数进行定义
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
		}   //end of if() 
	}   //end of for() 
	saField.Add(sTmp);
	if (saField.GetSize() == 1)

		return false;
	return true;
}

void Find::OnBnClickedButton2()                            //分数段内查找学生
{

	// TODO: 在此添加控件通知处理程序代码
	setlocale(LC_CTYPE, "chs");                          //解决文字乱码

	int i = 0;
	int n = m_stuArr.GetSize();         //获得学生人数
	CString strTmp;
	CStringArray  arrStr;    //声明字符串数组,创建CStringArry数组
	CString str;
	//CString m = _T("math"), E = _T("Eng"), C = _T("Cjj"), w = _T("wuli");
	//GetDlgItem(IDC_COMBO2)->GetWindowText(str);



	int nSel = m_cb.GetCurSel();   // 获取组合框控件的列表框中选中项的索引

	m_cb.GetLBText(nSel, str);     // 根据选中项索引获取该项字符串 

	// CString msg;
	 //msg.Format(_T("PageCount:%d\n"), str);
	 //MessageBox(str);


	 //const int num,Mnum,Pnum,Enum,Cnum;
	const int num = _ttoi(str);              //将当前组合框中字符串转化为ASCI值，用于比较
	const int Mnum = _ttoi(_T("math"));               //将“math”单词转化为ASCI值，和组合框中字符串转化的ASCI值比较
	const int Enum = _ttoi(_T("Eng"));               //将“Eng”单词转化为ASCI值，和组合框中字符串转化的ASCI值比较
	const int Pnum = _ttoi(_T("wuli"));               //将“wuli”单词转化为ASCI值，和组合框中字符串转化的ASCI值比较
	const int Cnum = _ttoi(_T("Cjj"));               //将“Cjj”单词转化为ASCI值，和组合框中字符串转化的ASCI值比较


	UpdateData(TRUE);
	double R, L;
	R = m_right;
	L = m_left;
	CString a[30];
	if (num == Mnum) {                                              //高数
		for (int i = 0; i < n; i++) {
			if (L<m_stuArr[i].math && R>m_stuArr[i].math) {
				a[i] = m_stuArr[i].name;
			}
		}
		CString s;
		for (int i = 0;i < n;i++)
		{
			s = s + "\n" + a[i];
		}
		MessageBox(s);
	}

	if (num == Enum) {                                            //大英
		for (int i = 0; i < n; i++) {
			if (L< m_stuArr[i].Eng && R>m_stuArr[i].Eng) {
				a[i] = m_stuArr[i].name;
			}
		}
		CString s;
		for (int i = 0;i < 3;i++)
		{
			s = s + "\n" + a[i];
		}

		MessageBox(s);
	}
	if (num == Pnum) {                                    //大物
		for (int i = 0; i < n; i++) {
			if (L< m_stuArr[i].wuli && R>m_stuArr[i].wuli) {
				a[i] = m_stuArr[i].name;
			}
		}
		CString s;
		for (int i = 0;i < 3;i++)
		{
			s = s + "\n" + a[i];
		}

		MessageBox(s);
	}
	if (num == Cnum) {                                    //C++
		for (int i = 0; i < n; i++) {
			if (L< m_stuArr[i].Cjj && R>m_stuArr[i].Cjj) {
				a[i] = m_stuArr[i].name;
			}
		}
		CString s;
		for (int i = 0;i < 3;i++)
		{
			s = s + "\n" + a[i];
		}

		MessageBox(s);

	}
}



                      


void Find::OnBnClickedButton3()                                  //打开文件
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
}
