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
	if (pid == 0)//子
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
	msgqid = msgget(SVKEY, 0777);  //打开 75#消息队列
	pid = getpid();  //获取client进程标识符
	pint = (int *)msg.mtext;  //把正文的内容传给 pint，并强制转换类型
	*pint = pid;  //pint指针指向client进程标识符
	msg.mtype = 1;  //消息类型为 1
	msgsnd(msgqid, &msg, sizeof(int), 0);  //发送消息msg入msgqid消息队列
	msgrcv(msgqid, &msg, 250, pid, 0);  //从队列msgqid接收消息msg
	printf("client:receive reply from pid of  %d\n", *pint);  //显示 server进程标识数
	exit(0);
}
void server()
{
	msgqid = msgget(SVKEY, 0777 | IPC_CREAT);  //创建 75#消息队列
	msgrcv(msgqid, &msg, 250, 1, 0);  //接收client进程标识数消息
	pint = (int *)msg.mtext;  //把正文的内容传给 pint，并强制转换类型
	pid = *pint;  //获得 cilent 进程标识数
	printf("server::serving for client  pid  of %d\n", pid);
	msg.mtype = pid;  //消息类型为 client 进程标识数
	*pint = getpid();  //获取 server 进程标识数
	msgsnd(msgqid, &msg, sizeof(int), 0);  //发送消息
	exit(0);
}
void msgQueueComm()
{
	i = fork();  //创建进程 1
	if (!i)server();
	i = fork(); //创建进程 2
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
	cout << "        进程通信程序        " << endl;
	int choice;
	while (1)
	{
		cout << "\n选择操作" << endl;
		cout << "1.管道通信" << endl;
		cout << "2.消息队列" << endl;
		cout << "3.共享储存区\n" << endl;
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
