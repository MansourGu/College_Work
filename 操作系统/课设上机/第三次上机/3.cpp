#include <iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
char filename[50];
int fd;
bool opened = false;
char* pargv[4] = { "ls", "-l", NULL, NULL };
void create_open_file() {
	printf("�������ļ���\n");
	scanf("%s", filename);
	//��д��ʽ�򿪣������ھ��½�
	umask(0000);
	fd = open(filename, O_RDWR | O_CREAT, 0666);
	pargv[2] = (char*)malloc(50);
	strcpy(pargv[2], filename);
	if (fd < 0) {
		printf("��ʧ��\n");
	}
	else {
		opened = 1;
		printf("�򿪳ɹ�\n");
	}
}
void write_file() {
	if (opened == 0) {
		printf("������Ҫ���ļ�\n");
		return;
	}
	char buffer[1 << 10];
	printf("�������ļ�����\n");
	scanf("%s", buffer);
	int returnnum = write(fd, buffer, strlen(buffer));
	if (returnnum != -1) {
		printf("д��ɹ���\n");
	}
	else {
		printf("д��ʧ�ܣ�\n");
	}
}
void  mode_file() {
	if (opened == 0) {
		printf("������Ҫ���ļ�\n");
		return;
	}
	int mode;
	printf("�����µ�ģʽ\n");
	scanf("%d", &mode);
	int mode_u = mode / 100;
	int mode_g = mode / 10 % 10;
	int mode_o = mode % 10;
	mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;   //�˽���ת��
	int returnnum = chmod(filename, mode);
	if (returnnum == -1) {
		printf("�ı�ģʽʧ�ܣ�\n");
	}
	else {
		printf("�ı�ģʽ�ɹ���\n");
	}
	//      close(fd);
	//      opened=0;
}
void read_file() {
	if (opened == 0) {
		printf("������Ҫ���ļ�\n");
		return;
	}
	char buffer[1 << 10];
	memset(buffer, 0, sizeof(buffer));
	//lseek() ��λһ���Ѿ��򿪵��ļ�
	lseek(fd, 0, SEEK_SET);
	int returnnum = read(fd, buffer, 1024);
	if (returnnum != -1) {
		printf("�ļ�����Ϊ��\n");
		printf("%s\n", buffer);
	}
	else {
		printf("��ȡʧ��\n");
	}
	//      close(fd);
	//      opened=0;
}
void view_mode() {
	if (opened == 0) {
		printf("������Ҫ���ļ�\n");
		return;
	}
	printf("%�ļ�Ȩ��Ϊ");//execv��ִֹͣ�е�ǰ�Ľ���
	int returnnum = execv("/bin/ls", pargv);
	if (returnnum == -1) {
		printf("�鿴ʧ��\n");
	}
	else {
		printf("�ļ�Ȩ��Ϊ��\n");
	}
	//      close(fd);
	//      opened=0;
}
int main()
{
	printf("**********�ļ�ϵͳ���ó���*********\n");
	int choice;
	while (1) {
		printf("\n��ѡ������ѡ��\n");
		printf("1.�½��������ڣ����ߴ��ļ�\n");
		printf("2.���ļ�\n");
		printf("3.д�ļ�\n");
		printf("4.���ļ�Ȩ���޸�\n");
		printf("5.�鿴�ļ�Ȩ��\n");
		printf("6.�ر��ļ�\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:create_open_file();
			break;
		case 2:read_file();
			break;
		case 3:write_file();
			break;
		case 4:mode_file();
			break;
		case 5:view_mode();
			break;
		case 6:close(fd);
			opened = 0;
			break;
		default:
			printf("input error!!");
			break;

		}
	}
	return 0;
}