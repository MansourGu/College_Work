#include <iostream>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;
const int SIZE = 1 << 8;
struct msgp {
	long long mtype;
	char mtext[250];
}msg;
const int SVKEY = 75;
int msgqid, pid, *pint, i;
void pipeComm()
{
	pid_t pid;
	int fd[2];
	char buf[SIZE];
	char msg[SIZE];
	memset(buf, 0, SIZE);
	memset(msg, 0, SIZE);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == 0)//��
	{
		close(fd[0]);
		sprintf(msg, "%d is sending a message to parent %d by PIPE\n", getpid(), getppid());
		write(fd[1], msg, strlen(msg));

		exit(0);
	}
	else if (pid > 0)
	{
		close(fd[1]);

		sleep(0);

		read(fd[0], buf, SIZE);
		printf("%s", buf);
	}
	else
	{
		perror("fork");
		exit(1);
	}
}
void client()
{
	msgqid = msgget(SVKEY, 0777);  //�� 75#��Ϣ����
	pid = getpid();  //��ȡclient���̱�ʶ��
	pint = (int *)msg.mtext;  //�����ĵ����ݴ��� pint����ǿ��ת������
	*pint = pid;  //pintָ��ָ��client���̱�ʶ��
	msg.mtype = 1;  //��Ϣ����Ϊ 1
	msgsnd(msgqid, &msg, sizeof(int), 0);  //������Ϣmsg��msgqid��Ϣ����
	msgrcv(msgqid, &msg, 250, pid, 0);  //�Ӷ���msgqid������Ϣmsg
	printf("client:receive reply from pid of  %d\n", *pint);  //��ʾ server���̱�ʶ��
	exit(0);
}
void server()
{
	msgqid = msgget(SVKEY, 0777 | IPC_CREAT);  //���� 75#��Ϣ����
	msgrcv(msgqid, &msg, 250, 1, 0);  //����client���̱�ʶ����Ϣ
	pint = (int *)msg.mtext;  //�����ĵ����ݴ��� pint����ǿ��ת������
	pid = *pint;  //��� cilent ���̱�ʶ��
	printf("server::serving for client  pid  of %d\n", pid);
	msg.mtype = pid;  //��Ϣ����Ϊ client ���̱�ʶ��
	*pint = getpid();  //��ȡ server ���̱�ʶ��
	msgsnd(msgqid, &msg, sizeof(int), 0);  //������Ϣ
	exit(0);
}
void msgQueueComm()
{
	i = fork();  //�������� 1
	if (!i)server();
	i = fork(); //�������� 2
	if (!i) client();
	sleep(1);
}
void sharedMemComm() {
	int id;
	char *addr;
	char message[512];
	id = shmget(75, 512, 0777 | IPC_CREAT);
	if (fork() == 0) {
		sprintf(message, "%d is sending message to parent", getpid());
		printf("%s\n", message);
		addr = (char*)shmat(id, 0, 0);
		strcpy(addr, message);
		shmdt(addr);
	}
	else {
		//wait(0);
		addr = (char*)shmat(id, 0, 0);
		printf("%s\n", addr);
		shmdt(addr);
		shmctl(id, IPC_RMID, 0);
	}
}
int main()
{
	cout << "        ����ͨ�ų���        " << endl;
	int choice;
	while (1)
	{
		cout << "\nѡ�����" << endl;
		cout << "1.�ܵ�ͨ��" << endl;
		cout << "2.��Ϣ����" << endl;
		cout << "3.��������\n" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			pipeComm();
			break;
		case 2:
			msgQueueComm();
			//wait(0);
			break;
		case 3:
			sharedMemComm();
			break;
		default:
			printf("INPUT ERROR!\n");
			break;
		}
		sleep(1);
	}
	return 0;
}
