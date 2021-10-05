#pragma once
#include<string>
#include<iostream>
using namespace std;
// Send_Mail 对话框

class Send_Mail : public CDialogEx
{
	DECLARE_DYNAMIC(Send_Mail)

public:
	Send_Mail(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Send_Mail();
	string username;
	string userkey;
	string mail_server;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 收件人
	CString RECVER;
	// 主题
	CString SUBJECT;
	// 正文内容
	CString Content;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedAttachment();
	string GetMailServer(string username);
	CString FLIEPATH;
	afx_msg void OnBnClickedButton3();
};
