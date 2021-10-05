// Send_Mail.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "MFC_SendEmail.h"
#include "Send_Mail.h"
#include "afxdialogex.h"
#include"smtp.h"
// Send_Mail 对话框
CSmtp smtp;
IMPLEMENT_DYNAMIC(Send_Mail, CDialogEx)

Send_Mail::Send_Mail(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, RECVER(_T(""))
	, SUBJECT(_T(""))
	, Content(_T(""))
	, FLIEPATH(_T(""))
{

}

Send_Mail::~Send_Mail()
{
}

void Send_Mail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECVER, RECVER);
	DDX_Text(pDX, IDC_SUBJECT, SUBJECT);
	DDX_Text(pDX, IDC_Content, Content);
	DDX_Text(pDX, IDC_FilePath, FLIEPATH);
}


BEGIN_MESSAGE_MAP(Send_Mail, CDialogEx)
	ON_BN_CLICKED(IDC_SEND, &Send_Mail::OnBnClickedSend)
	ON_BN_CLICKED(IDC_Attachment, &Send_Mail::OnBnClickedAttachment)
	ON_BN_CLICKED(IDC_BUTTON3, &Send_Mail::OnBnClickedButton3)
END_MESSAGE_MAP()


// Send_Mail 消息处理程序


BOOL Send_Mail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData();
	CSmtp smtp_login;
	smtp_login.SetPort(25); /*smtp端口*/
	smtp_login.SetSrvDomain(GetMailServer(username)); /*smtp服务器地址*/
	smtp_login.SetUserName(username);/*你的邮箱地址*/
	smtp_login.SetPass(userkey);  /*邮箱密码*/

	int err;
	if ((err = smtp_login.SendEmail_Ex()) != 0)
	{
		if (err == 1)
			MessageBox("错误1: 由于网络不畅通，发送失败!");
		if (err == 2)
			MessageBox("错误2: 用户名错误,请核对!");
		if (err == 3)
			MessageBox("错误3: 用户密码错误，请核对!");
		if (err == 4)
			MessageBox("错误4: 请检查附件目录是否正确，以及文件是否存在!");
		MessageBox("请重试！");
		EndDialog(0);
	}
	else
	{
		MessageBox("登录成功！");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Send_Mail::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	string content = Content.GetString();/*邮件正文*/
	string subject = SUBJECT.GetString();/*主题*/
	string recver = RECVER.GetString();/*目的邮箱地址,这一部分用空格分割可添加多个收信人*/
	smtp.SetPort(25); /*smtp端口*/
	smtp.SetSrvDomain(GetMailServer(username)); /*smtp服务器地址*/
	smtp.SetUserName(username);/*你的邮箱地址*/
	smtp.SetPass(userkey);  /*邮箱密码*/
	smtp.SetContent(content);
	smtp.SetEmailTitle(subject);
	smtp.SetTargetEmail(recver);
	int err;
	if ((err = smtp.SendEmail_Ex()) != 0)
	{
		if (err == 1)
			MessageBox("错误1: 由于网络不畅通，发送失败!");
		if (err == 2)
			MessageBox("错误2: 用户名错误,请核对!");
		if (err == 3)
			MessageBox("错误3: 用户密码错误，请核对!");
		if (err == 4)
			MessageBox("错误4: 请检查附件目录是否正确，以及文件是否存在!");
		MessageBox("请重试！");
	}
	else
	{
		MessageBox("发送成功！");
	}
	smtp.DeleteAllAttachment();
}


void Send_Mail::OnBnClickedAttachment()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile = _T("");
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.jpg)|*.jpg|All Files (*.*)|*.*||"), NULL);
	 if (dlgFile.DoModal())
	 {
	    strFile = dlgFile.GetPathName();
	 }
	 UpdateData(true);
	 FLIEPATH = strFile;
	 UpdateData(false);
	 string filepath = strFile.GetString();
	 smtp.AddAttachment(filepath);
	 
}


string Send_Mail::GetMailServer(string username)
{
	// TODO: 在此处添加实现代码.
	string result = "smtp.";
	int count = 0;
	for (int i = 0; i < username.size(); i++)
	{
		if (username[i] == '@')
		{
			count = i;
			break;
		}
	}
	result += username.substr(count + 1);
	return result;
}


void Send_Mail::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	smtp.DeleteAllAttachment();
}
