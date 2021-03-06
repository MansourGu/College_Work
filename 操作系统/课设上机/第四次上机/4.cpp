#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
pid_t pid1, pid2;//进程类型定义
int fd[2];
int cnt = 0;
void handler(int signo) {
	if (signo == SIGINT) {
		kill(pid1, SIGUSR1);//发出信号
		kill(pid2, SIGUSR2);
	}
	if (pid1 == 0 && signo == SIGUSR1) {
		printf("\nChild Process 1 is killed by Parent!\n");
		exit(0);
	}
	if (pid2 == 0 && signo == SIGUSR2) {
		printf("\nChild Process 2 is killed by Parent!\n");
		exit(0);
	}

}
int main()
{
	char buffer[1 << 8];
	char msg[1 << 8];
	memset(buffer, 0, sizeof(buffer));
	memset(msg, 0, sizeof(msg));
	if (pipe(fd) < 0) {
		perror("pipe");//perror(s) 用来将上一个函数发生错误的原因输出到标准设备(stderr)
		exit(1);
	}
	signal(SIGINT, handler);//当接收到一个类型为sig的信号时，就执行handler 所指定的函数
	pid1 = fork();
	if (pid1 == 0) {
		//子进程
		signal(SIGINT, SIG_IGN);//屏蔽结束
		signal(SIGUSR1, handler);
		while (1) {
			close(fd[0]);//关闭读
			sprintf(msg, "I send message %d times\n", ++cnt);
			write(fd[1], msg, strlen(msg));
			sleep(1);
		}
	}
	else if (pid1 > 0) {
		pid2 = fork();
		if (pid2 == 0) {
			signal(SIGINT, SIG_IGN);
			signal(SIGUSR2, handler);
			while (1) {
				close(fd[1]);//关闭写
				read(fd[0], buffer, sizeof(buffer));
				printf("%s\n", buffer);
			}
		}
		//等两个子进程结束
		waitpid(pid2, NULL, 0);
		waitpid(pid1, NULL, 0);
		close(fd[0]);
		close(fd[1]);
		printf("Parent Process is killed!\n");
	}
	else {
		perror("fork");
		exit(1);//不正常退出
	}
	return 0;
}