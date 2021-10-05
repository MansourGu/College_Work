// Test_Console.cpp : �������̨Ӧ�ó������ڵ㡣
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
#pragma region ȫ�ֱ���

SOCKET server;				// �����׽���
sockaddr_in sai_server;		// ��ŷ�����IP���˿�

// ��Ϣ��ʽ
struct umsg {
	int type;				// Э�飨1����¼��2���˳���3������Ϣ��
	char name[64];			// �û�����
	char text[512];			// �ı���Ϣ
};

// �ͻ�����Ϣ
struct clientInfo {
	SOCKET client;
	sockaddr_in saddr;
	umsg msg;
};

// �ͻ�������
typedef struct ucnode {
	clientInfo cInfo;
	ucnode* next;
} *ucnode_t;

ucnode* listHead;		// �ͻ�������ͷ
ucnode* lp;				// �ͻ�������ָ��

#pragma endregion

#pragma region ��������

// �����������
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

// ����ɾ������
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

// ���տͻ�����Ϣ��ĳ����
void recvMessage(PVOID pParam) {
	clientInfo* cInfo = (clientInfo*)pParam;
	
	while (1) {
		// �������Կͻ��˵���Ϣ
	
		umsg msg;
		int len_client = sizeof(sockaddr);
		int ret_recv = recv(
			cInfo->client,	// �����׽���	
			(char*)&msg,	// ��Ž��յ���Ϣ
			sizeof(msg),	// ��Ϣ��С
			0				// ���޸ĺ���������Ϊ
		);
		if (ret_recv <= 0) { break; }
		cInfo->msg = msg;
		time_t time_seconds;
		struct tm now_time;
		string clinet_time;
		char arr_ip[20];
		inet_ntop(AF_INET, &cInfo->saddr.sin_addr, arr_ip, 16);
		//�޸����ʱ��
		//string temp11 = cInfo->msg.text;
		//string text11 = clinet_time + temp11;
		//char Temp_text[512];
		//for (int i = 0; i < 512; i++)
		//{
		//	Temp_text[i] = ' ';
		//}
		//strcpy_s(Temp_text, text11.data());
		// ������Ϣ��1����¼��2���˳���3���Ự��
		string temp;
		switch (cInfo->msg.type) {
		
		case 1:
			// �������ݵ�����
			time_seconds = time(0);
			localtime_s(&now_time, &time_seconds);
			clinet_time = to_string(now_time.tm_year + 1900) + "-" + to_string(now_time.tm_mon + 1) + "-" + to_string(now_time.tm_mday) + " " + to_string(now_time.tm_hour) + ":" + to_string(now_time.tm_min) + ":" + to_string(now_time.tm_sec);
			cout << clinet_time << " ";
			insertNode(listHead, cInfo->client, cInfo->saddr, cInfo->msg);
			// ��ӡ��Ϣ
			cout << /*"[" << arr_ip << ":" << ntohs(cInfo->saddr.sin_port) << "] " << */msg.name << ":" << "����������" << endl;
			// �������ͻ��˹㲥�����Լ�֮�⣩
			break;
		case 2:
			// ������ɾ������
			deleteNode(listHead, /*cInfo->msg*/cInfo->client);
			// ��ӡ��Ϣ
			cout << /*"[" << arr_ip << ":" << ntohs(cInfo->saddr.sin_port) << "] " <<*/ msg.name << ":" << "�˳�������" << endl;
			break;
		case 3:
			// ��ӡ��Ϣ
			//cout <</* "[" << arr_ip << ":" << ntohs(cInfo->saddr.sin_port) << "] " <<*/ msg.name << ":" << cInfo->msg.text << endl;
			// �������ͻ��˹㲥�����Լ�֮�⣩
			lp = listHead;
			while (lp) {
				if (strcmp(lp->cInfo.msg.name, "") != 0 && strcmp(lp->cInfo.msg.name, cInfo->msg.name) != 0) {
					send(
						lp->cInfo.client,		// �����׽���
						(char*)&cInfo->msg,		// ���͵���Ϣ
						sizeof(cInfo->msg),		// ��Ϣ��С
						0						// ��ָ�����÷�ʽ
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
	cout << "�����Һ�̨������" << endl;

	// ��ʼ�� WSA ������ socket
	WSADATA wsaData;
	if (WSAStartup(
		MAKEWORD(2, 2), 		// �涨 socket �汾Ϊ 2.2
		&wsaData				// ���չ����׽��ֵĸ�����Ϣ
	)) {
		cout << "WSA��ʼ��ʧ�ܣ�" << GetLastError() << endl;
	}

	// ��ʼ�� socket����������Ϣ
	server = socket(
		AF_INET, 		// IPV4
		SOCK_STREAM,	// TCP
		0				// ��ָ��Э��
	);
	sai_server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// IP��ַ
	sai_server.sin_family = AF_INET;		// IPV4
	sai_server.sin_port = htons(7777);		// ����Э��˿�

	// ���ص�ַ�����׽���
	if (bind(
		server, 					// Ҫ�뱾�ص�ַ�󶨵��׽���
		(sockaddr*)&sai_server, 	// �������տͻ�����Ϣ�� sockaddr_in �ṹ��ָ��
		sizeof(sai_server)
	)) {
		cout << "��ʧ�ܣ�" << GetLastError() << endl;
		WSACleanup();
	}

	// �׽��ֽ������״̬
	listen(
		server,		// �����׽���
		SOMAXCONN	// �������Ӷ��е���󳤶ȣ�SOMAXCONN��������ֵ
	);

	// ��ʼ���ͻ�������
	listHead = new ucnode();
	listHead->next = nullptr;
	lp = listHead;

	// ������Ϣ
	while (1) {
		// ���յ�¼��Ϣ���״������Ǵ�����֮������Ϣ��������
		clientInfo* cInfo = new clientInfo();
		int len_client = sizeof(sockaddr);
		cInfo->client = accept(server, (sockaddr*)&cInfo->saddr, &len_client);
		if (GetLastError() != 0) { continue; }

		// ���յ�¼�ߵ���Ϣ��ÿ���ͻ��˶�Ӧһ���̣߳�
		HANDLE h_recvMes = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)recvMessage, cInfo, 0, 0);
		if (!h_recvMes) { cout << "�����߳�ʧ�ܣ�" << GetLastError() << endl; }
	}

	// ���� socket
	WSACleanup();

	getchar();
	return 0;
}

