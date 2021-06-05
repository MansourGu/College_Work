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
	printf("请输入文件名\n");
	scanf("%s", filename);
	//读写方式打开，不存在就新建
	umask(0000);
	fd = open(filename, O_RDWR | O_CREAT, 0666);
	pargv[2] = (char*)malloc(50);
	strcpy(pargv[2], filename);
	if (fd < 0) {
		printf("打开失败\n");
	}
	else {
		opened = 1;
		printf("打开成功\n");
	}
}
void write_file() {
	if (opened == 0) {
		printf("首先需要打开文件\n");
		return;
	}
	char buffer[1 << 10];
	printf("请输入文件内容\n");
	scanf("%s", buffer);
	int returnnum = write(fd, buffer, strlen(buffer));
	if (returnnum != -1) {
		printf("写入成功！\n");
	}
	else {
		printf("写入失败！\n");
	}
}
void  mode_file() {
	if (opened == 0) {
		printf("首先需要打开文件\n");
		return;
	}
	int mode;
	printf("输入新的模式\n");
	scanf("%d", &mode);
	int mode_u = mode / 100;
	int mode_g = mode / 10 % 10;
	int mode_o = mode % 10;
	mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;   //八进制转换
	int returnnum = chmod(filename, mode);
	if (returnnum == -1) {
		printf("改变模式失败！\n");
	}
	else {
		printf("改变模式成功！\n");
	}
	//      close(fd);
	//      opened=0;
}
void read_file() {
	if (opened == 0) {
		printf("首先需要打开文件\n");
		return;
	}
	char buffer[1 << 10];
	memset(buffer, 0, sizeof(buffer));
	//lseek() 定位一个已经打开的文件
	lseek(fd, 0, SEEK_SET);
	int returnnum = read(fd, buffer, 1024);
	if (returnnum != -1) {
		printf("文件内容为：\n");
		printf("%s\n", buffer);
	}
	else {
		printf("读取失败\n");
	}
	//      close(fd);
	//      opened=0;
}
void view_mode() {
	if (opened == 0) {
		printf("首先需要打开文件\n");
		return;
	}
	printf("%文件权限为");//execv会停止执行当前的进程
	int returnnum = execv("/bin/ls", pargv);
	if (returnnum == -1) {
		printf("查看失败\n");
	}
	else {
		printf("文件权限为：\n");
	}
	//      close(fd);
	//      opened=0;
}
int main()
{
	printf("**********文件系统调用程序*********\n");
	int choice;
	while (1) {
		printf("\n请选择您的选项\n");
		printf("1.新建（不存在）或者打开文件\n");
		printf("2.读文件\n");
		printf("3.写文件\n");
		printf("4.给文件权限修改\n");
		printf("5.查看文件权限\n");
		printf("6.关闭文件\n");
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