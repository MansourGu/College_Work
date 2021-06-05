#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
pid_t pid1, pid2;//�������Ͷ���
int fd[2];
int cnt = 0;
void handler(int signo) {
	if (signo == SIGINT) {
		kill(pid1, SIGUSR1);//�����ź�
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
		perror("pipe");//perror(s) ��������һ���������������ԭ���������׼�豸(stderr)
		exit(1);
	}
	signal(SIGINT, handler);//�����յ�һ������Ϊsig���ź�ʱ����ִ��handler ��ָ���ĺ���
	pid1 = fork();
	if (pid1 == 0) {
		//�ӽ���
		signal(SIGINT, SIG_IGN);//���ν���
		signal(SIGUSR1, handler);
		while (1) {
			close(fd[0]);//�رն�
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
				close(fd[1]);//�ر�д
				read(fd[0], buffer, sizeof(buffer));
				printf("%s\n", buffer);
			}
		}
		//�������ӽ��̽���
		waitpid(pid2, NULL, 0);
		waitpid(pid1, NULL, 0);
		close(fd[0]);
		close(fd[1]);
		printf("Parent Process is killed!\n");
	}
	else {
		perror("fork");
		exit(1);//�������˳�
	}
	return 0;
}