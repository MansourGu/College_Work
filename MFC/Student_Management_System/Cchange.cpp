// Cchange.cpp: 实现文件
//

#include "pch.h"
#include "studentmanageA.h"
#include "Cchange.h"
#include "afxdialogex.h"


// Cchange 对话框

IMPLEMENT_DYNAMIC(Cchange, CDialogEx)

Cchange::Cchange(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, c_name(_T(""))
	, c_id(_T(""))
	, c_math(0)
	, c_wuli(0)
	, c_Eng(0)
	, c_Cjj(0)
{

}

Cchange::~Cchange()
{
}

void Cchange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, c_name);
	DDX_Text(pDX, IDC_EDIT2, c_id);
	DDX_Text(pDX, IDC_EDIT3, c_math);
	DDX_Text(pDX, IDC_EDIT4, c_wuli);
	DDX_Text(pDX, IDC_EDIT5, c_Eng);
	DDX_Text(pDX, IDC_EDIT6, c_Cjj);
}


BEGIN_MESSAGE_MAP(Cchange, CDialogEx)
END_MESSAGE_MAP()


// Cchange 消息处理程序
