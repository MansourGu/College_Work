// Delete.cpp: 实现文件
//

#include "stdafx.h"
#include "List.h"
#include "Delete.h"
#include "afxdialogex.h"


// Delete 对话框

IMPLEMENT_DYNAMIC(Delete, CDialogEx)

Delete::Delete(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIST_DIALOG, pParent)
{

}

Delete::~Delete()
{
}

void Delete::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Delete, CDialogEx)
END_MESSAGE_MAP()


// Delete 消息处理程序
