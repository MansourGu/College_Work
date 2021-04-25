// Cadd.cpp: 实现文件
//

#include "pch.h"
#include "studentmanageA.h"
#include "Cadd.h"
#include "afxdialogex.h"


// Cadd 对话框

IMPLEMENT_DYNAMIC(Cadd, CDialogEx)

Cadd::Cadd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_name(_T(""))
	, m_id(_T(""))
	, m_math(0)
	, m_wuli(0)
	, m_Eng(0)
	, m_Cjj(0)
{

}

Cadd::~Cadd()
{
}

void Cadd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_id);
	DDX_Text(pDX, IDC_EDIT3, m_math);
	DDX_Text(pDX, IDC_EDIT4, m_wuli);
	DDX_Text(pDX, IDC_EDIT5, m_Eng);
	DDX_Text(pDX, IDC_EDIT6, m_Cjj);
}


BEGIN_MESSAGE_MAP(Cadd, CDialogEx)
END_MESSAGE_MAP()


// Cadd 消息处理程序
