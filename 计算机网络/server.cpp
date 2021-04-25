#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
using namespace std;

int main()
{
	cout << "------------------服务器------------------" << endl;
	
	int servicesocket = socket(AF_INET, SOCK_STREAM, 0);//socket(协议族，socket数据传输方式（TCP),某个协议）
	if(SOCKET_ERROR == servicesocket)
	{
		cout << "SOCKET 创建失败！" << endl;
	}
	else
	{
		cout << "SOCKET 创建成功！" << endl;
	}
	// 3 绑定套接字 指定绑定的IP地址和端口号
	struct sockaddr_in socketAddr;
	memset(&socketAddr,0,sizeof(socketAddr))
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.S_un.S_addr = inet_addr("172.27.230.244");
	socketAddr.sin_port = htons(2000);
	int bRes = bind(servicesocket, (struct sockaddr_in*)&socketAddr, sizeof(socketAddr));
	if (SOCKET_ERROR == bRes)
	{
		cout << "绑定失败！" << endl;
	}
	else
	{
		cout << "绑定成功！" << endl;
	}
	//服务器监听
	int lLen = listen(servicesocket, 5);//第二个参数，能存放多少个客户端请求
	if (SOCKET_ERROR == lLen)
	{
		cout << "监听失败！" << endl;
	}
	else
	{
		cout << "监听成功！" << endl;
	}
	// 5 接受请求
	struct sockaddr_in recvClientAddr;
	SOCKET recvClientSocket = INVALID_SOCKET; //初始化一个能接受的客户端socket
	int _recvsize = sizeof(sockaddr_in);
	recvClientSocket = accept(servicesocket, (SOCKADDR*)&recvClientAddr, &_recvsize);
	if (INVALID_SOCKET == recvClientSocket)
	{
		cout << "服务端接受请求失败！" << endl;
	}
	else
	{
		cout << "服务端接收请求成功！" << endl;
	}

	// 6 发送/接受 数据
	char recvBuf[1024] = {};
	int relen = recv(recvClientSocket, recvBuf, 1024, 0);
	int slen = send(recvClientSocket, recvBuf, relen, 0);
	if (SOCKET_ERROR == relen)
	{
		cout << "服务端发送数据失败！" << endl;
	}
	else
	{
		cout << "服务端接收到数据：  " << recvBuf << endl << endl;
	}

	// 7 关闭SOCKET
	closesocket(recvClientSocket);
	closesocket(servicesocket);
	// 8 终止
	WSACleanup();

	cout << "服务器停止" << endl;
	cin.get();
	return 0;
}