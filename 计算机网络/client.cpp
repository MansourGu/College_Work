#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���ξ���

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<cstring>
#include<WS2tcpip.h>
#include<WinSock2.h>
#include<Windows.h>
#pragma comment(lib,"ws2_32.lib") //��ʾ	���� ws2_32.dll
using namespace std;

int main()
{// 1 ��ʼ��
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	// 2 �����������׽���
	SOCKET clientsocket = {};
	cout << "------------------�ͻ���------------------" << endl;
	// 4  ��������
	while (1)
	{
		clientsocket = socket(PF_INET, SOCK_STREAM, 0);//socket(Э���壬socket���ݴ��䷽ʽ��TCP),ĳ��Э�飩
		if (SOCKET_ERROR == clientsocket)
		{
			cout << "SOCKET ����ʧ�ܣ�" << endl;
			continue;
		}
		// 3 ���׽��� ָ���󶨵�IP��ַ�Ͷ˿ں�
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
		// 5 ����/���� ����
		char recvBuf[1024] = {};
		int recvflg = recv(clientsocket, recvBuf, 1024, 0);
		if (recvflg < 0)
		{
			cout << "Recieve Error ! Please re-try " << endl;
		}
		cout << recvBuf;
	}
	// 6 �ر�SOCKET
	closesocket(clientsocket);
	// 8 ��ֹ
	WSACleanup();

	cout << "�ͻ����˳�" << endl;
	cin.get();
	return 0;
}