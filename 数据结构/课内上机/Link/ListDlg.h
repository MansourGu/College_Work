
// ListDlg.h: 头文件
//

#pragma once
#include"BaseList.h"
#include"LinkList.h"
#include"SeqList.h"
#include<vector>
#include<cstring>

// CListDlg 对话框
class CListDlg : public CDialogEx
{
// 构造
public:
	CListDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString OUTPUT;
	SeqList sl;
	LinkList ll;
	int judge = 1;
	afx_msg void OnBnClickedSwitch();
	afx_msg void OnBnClickedAdd();
	CString Tips;
	CString INPUT;
	vector<CString> input_get;
	vector<int>sl_vec;
	vector<int>ll_vec;
	void Display();
	CString Object;
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedReverse();
};
