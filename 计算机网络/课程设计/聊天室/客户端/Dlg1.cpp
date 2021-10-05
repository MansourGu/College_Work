// Dlg1.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "MFC_Chatroom.h"
#include "Dlg1.h"
#include "afxdialogex.h"
// Dlg1 对话框
SOCKET client;					// 本地套接字
sockaddr_in sai_client;	// 存放客户端IP地址、端口
vector<CString> Recv_msg;//接受消息所有接收的消息
Dlg1* dlg_pointer = new Dlg1;
// 消息格式
struct umsg {
	int type;					// 协议（1：登录，2：退出，3：发消息）
	char name[64];				// 用户名字
	char text[512];				// 文本
};
IMPLEMENT_DYNAMIC(Dlg1, CDialogEx)
Dlg1::Dlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, INPUT(_T(""))
	, OUTPUT(_T(""))
{
}

Dlg1::~Dlg1()
{
}

void Dlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_OUTPUT, OUTPUT);
	DDX_Text(pDX, IDC_INPUT, INPUT);
	//  DDX_Control(pDX, IDC_OUTPUT, OUTPUT);
	DDX_Text(pDX, IDC_OUTPUT, OUTPUT);
}


BEGIN_MESSAGE_MAP(Dlg1, CDialogEx)
	ON_MESSAGE(WM_UPDATEDATA, &Dlg1::OnUpdateData)
	ON_BN_CLICKED(IDC_BUTTON1, &Dlg1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SEND, &Dlg1::OnBnClickedSend)
	ON_BN_CLICKED(IDOK, &Dlg1::OnBnClickedOk)
END_MESSAGE_MAP()


// Dlg1 消息处理程序


void Dlg1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	OUTPUT = "";
	UpdateData(false);
}


BOOL Dlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 初始化 WSA ，激活 socket
	dlg_pointer = this;
	WSADATA wsaData;
	if (WSAStartup(
		MAKEWORD(2, 2), 	// 规定 socket 版本
		&wsaData			// 接收 socket 的更多信息
	)) {

		MessageBox("WSAS初始化失败！");
	}
	// 初始化 socket、客户端信息
	client = socket(
		AF_INET,		// IPV4
		SOCK_STREAM,	// TCP
		0				// 不指定协议
	);
	sai_client.sin_family = AF_INET;									// IPV4
	inet_pton(AF_INET, "127.0.0.1", &sai_client.sin_addr);			// 服务器 IP地址
	sai_client.sin_port = htons(7777);									// 端口
flag1:// 连接服务器
	int ret_connect = connect(
		client, 					// 本地套接字
		(sockaddr*)&sai_client, 	// 目标
		sizeof(sai_client)
	); 
	if (ret_connect != 0) 
	{ 
		MessageBox ("连接失败! \n正在重连···");
		goto flag1;

	}
	// 输入用户名
	umsg msg;
	msg.type = 1;
	string name;
	name = username_value;
	strncpy_s(msg.name, sizeof(msg.name), name.c_str(), 64);
	strncpy_s(msg.text, sizeof(msg.text), "", 512);
	// 发送登录消息
	send(
		client,			// 本地套接字
		(char*)&msg,	// 发送的消息
		sizeof(msg),	// 消息大小
		0				// 不指定调用方式
	);
	int error_send = GetLastError();
	if (error_send != 0) 
	{ MessageBox("登录失败！") ; }

	// 接收服务器消息
	HANDLE h_recvMes = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)recvMessage, 0, 0, 0);
	if (!h_recvMes) { MessageBox("创建线程失败！"); }
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void Dlg1::recvMessage()
{
	// TODO: 在此处添加实现代码.
	
	while (1) 
	{
		CString output;
		umsg msg;
		int ret_recv = recv(
			client, 		// 本地套接字
			(char*)&msg,	// 存放接收的消息
			sizeof(msg),	// 消息大小
			0				// 不指定调用方式
		);
		if (ret_recv <= 0) 
		{
			AfxMessageBox("接收失败！");
			break;
		}

		// 打印消息
		string name(msg.name);
		string text(msg.text);
		name += "：";
		name += text;
		Recv_msg.push_back(name.c_str());
		for (int i = 0; i < Recv_msg.size(); i++)
		{
			output += Recv_msg[i];
			output += "\r\n";
			if (i == Recv_msg.size()-1)
			{
				continue;
			}
		}
		dlg_pointer->OUTPUT += output;
		dlg_pointer->SendMessage(WM_UPDATEDATA, FALSE);
		Recv_msg.clear();
	} 
}
LRESULT Dlg1::OnUpdateData(WPARAM wParam, LPARAM lParam)
{
	UpdateData(wParam);
	return 0;
}
void Dlg1::OnBnClickedSend()//发送消息
{
	// TODO: 在此添加控件通知处理程序代码
	string content;
	UpdateData(true);
	content = INPUT;
	umsg msg;
	int error_send;
	// 会话消息
	msg.type = 3;
	strncpy_s(msg.name, sizeof(msg.name), username_value, 64);
	strncpy_s(msg.text, sizeof(msg.text), content.c_str(), 512);
	send(
		client,			// 本体套接字
		(char*)&msg,	// 发送的消息
		sizeof(msg),	// 消息大小
		0				// 不指定调用方式
	);
	error_send = GetLastError();
	if (error_send != 0) 
	{ 
		MessageBox("发送失败！"); 
	}
	else
	{
		OUTPUT += username_value;
		OUTPUT += "：";
		OUTPUT += INPUT;
		OUTPUT += "\r\n";
		INPUT = "";
		UpdateData(false);
	}
}
void Dlg1::OnBnClickedOk()//退出
{
	// TODO: 在此添加控件通知处理程序代码
	umsg msg;
	int error_send;
	msg.type = 2;
	string content = "退出";
	strncpy_s(msg.name, sizeof(msg.name), username_value, 64);
	strncpy_s(msg.text, sizeof(msg.text), content.c_str(), 512);
	send(
		client,			// 本地套接字
		(char*)&msg,	// 发送的消息
		sizeof(msg),	// 消息大小
		0				// 不指定调用方式
	);
	error_send = GetLastError();
	if (error_send != 0)
	{
		MessageBox("发送失败！");
	}
	closesocket(client);
	WSACleanup();
	CDialogEx::OnOK();
}
