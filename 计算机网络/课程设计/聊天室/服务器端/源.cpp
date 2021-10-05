// Test_Console.cpp : 定义控制台应用程序的入口点。
//
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <thread>
#include <cstdio>
#include<ctime>
#include<string>
using namespace std;
#pragma region 全局变量

SOCKET server;				// 本地套接字
sockaddr_in sai_server;		// 存放服务器IP、端口

// 消息格式
struct umsg {
	int type;				// 协议（1：登录，2：退出，3：发消息）
	char name[64];			// 用户名字
	char text[512];			// 文本信息
};

// 客户端信息
struct clientInfo {
	SOCKET client;
	sockaddr_in saddr;
	umsg msg;
};

// 客户端链表
typedef struct ucnode {
	clientInfo cInfo;
	ucnode* next;
} *ucnode_t;

ucnode* listHead;		// 客户端链表头
ucnode* lp;				// 客户端链表指针

#pragma endregion

#pragma region 依赖函数

// 链表插入数据
ucnode* insertNode(ucnode* head, SOCKET client, sockaddr_in addr, umsg msg) {
	ucnode* newNode = new ucnode();
	newNode->cInfo.client = client;
	newNode->cInfo.saddr = addr;
	newNode->cInfo.msg = msg;
	ucnode* p = head;
	if (p == nullptr) {
		head = newNode;
	}
	else {
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = newNode;
	}
	return head;
}

// 链表删除数据
ucnode* deleteNode(ucnode* head, SOCKET client) {
	ucnode* p = head;
	if (p == nullptr) {
		return head;
	}
	if (p->cInfo.client == client) {
		head = p->next;
		delete p;
		return head;
	}
	while (p->next != nullptr && p->next->cInfo.client != client) {
		p = p->next;
	}
	if (p->next == nullptr) {
		return head;
	}
	ucnode* deleteNode = p->next;
	p->next = deleteNode->next;
	delete deleteNode;
	return head;
}

// 接收客户端消息（某个）
void recvMessage(PVOID pParam) {
	clientInfo* cInfo = (clientInfo*)pParam;
	
	while (1) {
		// 接收来自客户端的消息
	
		umsg msg;
		int len_client = sizeof(sockaddr);
		int ret_recv = recv(
			cInfo->client,	// 本地套接字	
			(char*)&msg,	// 存放接收的消息
			sizeof(msg),	// 消息大小
			0				// 不修改函数调用行为
		);
		if (ret_recv <= 0) { break; }
		cInfo->msg = msg;
		time_t time_seconds;
		struct tm now_time;
		string clinet_time;
		char arr_ip[20];
		inet_ntop(AF_INET, &cInfo->saddr.sin_addr, arr_ip, 16);
		//修改输出时间
		//string temp11 = cInfo->msg.text;
		//string text11 = clinet_time + temp11;
		//char Temp_text[512];
		//for (int i = 0; i < 512; i++)
		//{
		//	Temp_text[i] = ' ';
		//}
		//strcpy_s(Temp_text, text11.data());
		// 处理消息（1：登录，2：退出，3：会话）
		string temp;
		switch (cInfo->msg.type) {
		
		case 1:
			// 插入数据到链表
			time_seconds = time(0);
			localtime_s(&now_time, &time_seconds);
			clinet_time = to_string(now_time.tm_year + 1900) + "-" + to_string(now_time.tm_mon + 1) + "-" + to_string(now_time.tm_mday) + " " + to_string(now_time.tm_hour) + ":" + to_string(now_time.tm_min) + ":" + to_string(now_time.tm_sec);
			cout << clinet_time << " ";
			insertNode(listHead, cInfo->client, cInfo->saddr, cInfo->msg);
			// 打印消息
			cout << /*"[" << arr_ip << ":" << ntohs(cInfo->saddr.sin_port) << "] " << */msg.name << ":" << "进入聊天室" << endl;
			// 向其他客户端广播（除自己之外）
			break;
		case 2:
			// 从链表删除数据
			deleteNode(listHead, /*cInfo->msg*/cInfo->client);
			// 打印消息
			cout << /*"[" << arr_ip << ":" << ntohs(cInfo->saddr.sin_port) << "] " <<*/ msg.name << ":" << "退出聊天室" << endl;
			break;
		case 3:
			// 打印消息
			//cout <</* "[" << arr_ip << ":" << ntohs(cInfo->saddr.sin_port) << "] " <<*/ msg.name << ":" << cInfo->msg.text << endl;
			// 向其他客户端广播（除自己之外）
			lp = listHead;
			while (lp) {
				if (strcmp(lp->cInfo.msg.name, "") != 0 && strcmp(lp->cInfo.msg.name, cInfo->msg.name) != 0) {
					send(
						lp->cInfo.client,		// 本地套接字
						(char*)&cInfo->msg,		// 发送的消息
						sizeof(cInfo->msg),		// 消息大小
						0						// 不指定调用方式
					);
					int error_send = GetLastError();
					//if (error_send != 0) { cout << "send failed:" << error_send << endl; }
				}
				lp = lp->next;
			}
			break;
		}
	}
}

#pragma endregion

int main()
{
	cout << "聊天室后台服务器" << endl;

	// 初始化 WSA ，激活 socket
	WSADATA wsaData;
	if (WSAStartup(
		MAKEWORD(2, 2), 		// 规定 socket 版本为 2.2
		&wsaData				// 接收关于套接字的更多信息
	)) {
		cout << "WSA初始化失败！" << GetLastError() << endl;
	}

	// 初始化 socket、服务器信息
	server = socket(
		AF_INET, 		// IPV4
		SOCK_STREAM,	// TCP
		0				// 不指定协议
	);
	sai_server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// IP地址
	sai_server.sin_family = AF_INET;		// IPV4
	sai_server.sin_port = htons(7777);		// 传输协议端口

	// 本地地址关联套接字
	if (bind(
		server, 					// 要与本地地址绑定的套接字
		(sockaddr*)&sai_server, 	// 用来接收客户端消息的 sockaddr_in 结构体指针
		sizeof(sai_server)
	)) {
		cout << "绑定失败！" << GetLastError() << endl;
		WSACleanup();
	}

	// 套接字进入监听状态
	listen(
		server,		// 本地套接字
		SOMAXCONN	// 挂起连接队列的最大长度，SOMAXCONN：最大合理值
	);

	// 初始化客户端链表
	listHead = new ucnode();
	listHead->next = nullptr;
	lp = listHead;

	// 接收消息
	while (1) {
		// 接收登录消息（首次连接是触发，之后发送消息不触发）
		clientInfo* cInfo = new clientInfo();
		int len_client = sizeof(sockaddr);
		cInfo->client = accept(server, (sockaddr*)&cInfo->saddr, &len_client);
		if (GetLastError() != 0) { continue; }

		// 接收登录者的消息（每个客户端对应一个线程）
		HANDLE h_recvMes = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)recvMessage, cInfo, 0, 0);
		if (!h_recvMes) { cout << "创建线程失败！" << GetLastError() << endl; }
	}

	// 禁用 socket
	WSACleanup();

	getchar();
	return 0;
}

