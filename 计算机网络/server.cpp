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
	cout << "------------------������------------------" << endl;
	
	int servicesocket = socket(AF_INET, SOCK_STREAM, 0);//socket(Э���壬socket���ݴ��䷽ʽ��TCP),ĳ��Э�飩
	if(SOCKET_ERROR == servicesocket)
	{
		cout << "SOCKET ����ʧ�ܣ�" << endl;
	}
	else
	{
		cout << "SOCKET �����ɹ���" << endl;
	}
	// 3 ���׽��� ָ���󶨵�IP��ַ�Ͷ˿ں�
	struct sockaddr_in socketAddr;
	memset(&socketAddr,0,sizeof(socketAddr))
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.S_un.S_addr = inet_addr("172.27.230.244");
	socketAddr.sin_port = htons(2000);
	int bRes = bind(servicesocket, (struct sockaddr_in*)&socketAddr, sizeof(socketAddr));
	if (SOCKET_ERROR == bRes)
	{
		cout << "��ʧ�ܣ�" << endl;
	}
	else
	{
		cout << "�󶨳ɹ���" << endl;
	}
	//����������
	int lLen = listen(servicesocket, 5);//�ڶ����������ܴ�Ŷ��ٸ��ͻ�������
	if (SOCKET_ERROR == lLen)
	{
		cout << "����ʧ�ܣ�" << endl;
	}
	else
	{
		cout << "�����ɹ���" << endl;
	}
	// 5 ��������
	struct sockaddr_in recvClientAddr;
	SOCKET recvClientSocket = INVALID_SOCKET; //��ʼ��һ���ܽ��ܵĿͻ���socket
	int _recvsize = sizeof(sockaddr_in);
	recvClientSocket = accept(servicesocket, (SOCKADDR*)&recvClientAddr, &_recvsize);
	if (INVALID_SOCKET == recvClientSocket)
	{
		cout << "����˽�������ʧ�ܣ�" << endl;
	}
	else
	{
		cout << "����˽�������ɹ���" << endl;
	}

	// 6 ����/���� ����
	char recvBuf[1024] = {};
	int relen = recv(recvClientSocket, recvBuf, 1024, 0);
	int slen = send(recvClientSocket, recvBuf, relen, 0);
	if (SOCKET_ERROR == relen)
	{
		cout << "����˷�������ʧ�ܣ�" << endl;
	}
	else
	{
		cout << "����˽��յ����ݣ�  " << recvBuf << endl << endl;
	}

	// 7 �ر�SOCKET
	closesocket(recvClientSocket);
	closesocket(servicesocket);
	// 8 ��ֹ
	WSACleanup();

	cout << "������ֹͣ" << endl;
	cin.get();
	return 0;
}