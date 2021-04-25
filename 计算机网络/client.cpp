#define _WINSOCK_DEPRECATED_NO_WARNINGS // 屏蔽警告

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<cstring>
#include<WS2tcpip.h>
#include<WinSock2.h>
#include<Windows.h>
#pragma comment(lib,"ws2_32.lib") //显示	加载 ws2_32.dll
using namespace std;

int main()
{// 1 初始化
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	// 2 创建服务器套接字
	SOCKET clientsocket = {};
	cout << "------------------客户端------------------" << endl;
	// 4  发送请求
	while (1)
	{
		clientsocket = socket(PF_INET, SOCK_STREAM, 0);//socket(协议族，socket数据传输方式（TCP),某个协议）
		if (SOCKET_ERROR == clientsocket)
		{
			cout << "SOCKET 创建失败！" << endl;
			continue;
		}
		// 3 绑定套接字 指定绑定的IP地址和端口号
		sockaddr_in socketAddr;
		socketAddr.sin_family = PF_INET;
		socketAddr.sin_addr.S_un.S_addr = inet_addr("140.143.168.63");
		socketAddr.sin_port = htons(2000);
		while (connect(clientsocket, (SOCKADDR*)&socketAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		{
			cout<<"Connection Error! Now re-try to get connected ... "<<endl;
		}
		char sendBuff[1024] = {};
		cout<<"Input a String you want to send to the Server : ";
		char temp = 'a';
		for (int i = 0; i < 1024; i++)
		{
			scanf_s("%c",&temp);
			if (temp == '\r'||temp == '\n')
				break;
			sendBuff[i] = temp;
		}
		int endflg = send(clientsocket, sendBuff, strlen(sendBuff), 0);	
		if (endflg < 0)
		{
			cout << "Send Error! Please re-try " << endl;
			continue;
		}
		// 5 发送/接受 数据
		char recvBuf[1024] = {};
		int recvflg = recv(clientsocket, recvBuf, 1024, 0);
		if (recvflg < 0)
		{
			cout << "Recieve Error ! Please re-try " << endl;
		}
		cout << recvBuf;
	}
	// 6 关闭SOCKET
	closesocket(clientsocket);
	// 8 终止
	WSACleanup();

	cout << "客户端退出" << endl;
	cin.get();
	return 0;
}