#include <graphics.h>      // ������Ҫ�������ͼ�ο�
#include <conio.h>
#include<easyx.h>
#include<string>
#include<time.h>
#include<iostream>
char c1[] = "2Ԫ";
char c2[] = "����";
char c3[] = "��";
char c4[] = "��ƿ";
char c5[] = "�̵�";
char c6[] = "�Ѻȿ���ƿ�� ��";//������Ҫ������ַ�
char c7[] = "ƿ��";
char c8[] = "Ǯ";
int money=5, crust=0, coke=0, bottle=0;//��ʼ����Ϣ
using namespace std;
char c9[10] = { '0','1','2','3','4', '5','6','7','8','9' };
void clean()//Ĩ����һ�ε�����
{
	setcolor(BLACK);
	char x[] = "   ";
	outtextxy(220 , 60, x);
}
void output(int x)//����ַ� ��Ϊֻ��һλһλ���
{
	setcolor(WHITE);
	int count = 0;
	while (x > 0)
	{
		{
			int tem = x % 10;//������һλ��
			for (int i = 0; i < 10; i++)
			{
				if (tem == i)
				{
					outtextxy(230 - 10 * count, 60, c9[i]);//�������
					count++;
					break;
				}
			}
			x /= 10;
		}
	}
}
void show_money(int x ,int y)//��ʾǮ��ͼ��
{
	outtextxy(x-12, y-7, c1);
	circle(x, y, 20);
}
void show_crust(int x, int y)//��ʾƿ�ǵ�ͼ��
{
	outtextxy(x - 8, y - 8, c3);
	circle(x, y, 20);
	circle(x, y, 17);
}
void show_coke(int left, int top)//��ʾ���ֵ�ͼ��
{
	rectangle(left, top, left+40, top+100);
	outtextxy(left + 5, top + 45, c2);
}
void show_empty(int left, int top)//��ʾ��ƿ��ͼ��
{
	rectangle(left, top, left + 40, top + 100);
	outtextxy(left + 5, top + 45, c4);
}
void show_shop()//��ʾ�̵��ͼ��
{
	rectangle(780, 200, 1180, 500);
	rectangle(915, 230, 1045, 300);
	outtextxy(958, 255, c5);
	int x = 810, y = 350;
	for (int i = 0; i < 7; i++)
	{
		show_coke((x + (i * 50)), y);
	}
}
int main()
{


	initgraph(1280,720);   //��ʼ��ͼ�ν��� �ֱ��� 1280 X 720
	outtextxy(70, 60, c6);//��ʾ�Ѻȿ���ƿ��
	outtextxy(100, 160, c4);//��ʾ��ƿ
	outtextxy(100, 360, c7);//��ʾƿ��
	outtextxy(100, 510, c8);//��ʾǮ
	show_shop();
	for (int i = 0; i < money; i++)
	{
		show_money(20 + i * 50, 580);
	}
	for (int i = 0; i < money; i++)
	{
		for (int j = (220 - 50 * i); j < 750; j += 20)//ʵ��Ǯ���ƶ�
		{
			setcolor(WHITE);//��ɫ���� 
			show_money(j, 580);
			Sleep(250);
			setcolor(BLACK);//��ɫ�ڻ�һ�β���ʵ���ƶ���Ч��
			show_money(j, 580);
		}
		for (int k = 700-i*50; k >150; k-=50)//����ƿ���ƶ�
		{
			setcolor(WHITE);
			show_coke(k,300);
			Sleep(250);
			setcolor(BLACK);
			show_coke(k, 300);
		}
		coke++;//�Ѻȿ���������һ
		bottle++;//��ƿ����һ
		crust++;//ƿ�Ǽ�һ
		setcolor(WHITE);
		show_crust(20 + i * 50, 410);//����ƿ��
		show_empty(i * 50, 200);//��������ƿ
		clean();
		output(coke);//����Ѻȿ���ƿ��
	}
	while (crust>=4||bottle>=2)//ƿ�����ƿ֮���ת��
	{
		for (;bottle>=2;)//��ƿ������
		{
			for (int i = (bottle-2)*50; i < 700;i+=50)
			{
				setcolor(WHITE);
				show_empty(i, 200);
				show_empty(i+50, 200);
				Sleep(250);
				setcolor(BLACK);
				show_empty(i, 200);
				show_empty(i+50, 200);
			}
			for (int k = 700 ; k > 250; k -= 50)
			{
				setcolor(WHITE);
				show_coke(k, 300);
				Sleep(250);
				setcolor(BLACK);
				show_coke(k, 300);
			}
			setcolor(WHITE);
			bottle -= 2;
			bottle++;
			coke++;
			crust++;
			show_crust((crust-1)*50+20, 410);
			show_empty((bottle - 1) * 50, 200);
			clean();
			output(coke);
			Sleep(500);
		}
		for (; crust >= 4;)//ƿ�ǻ�����
		{
			for (int i = (crust - 4) * 50+20; i < 550; i += 20)
			{
				setcolor(WHITE);
				show_crust(i, 410);
				show_crust(i+50, 410);
				show_crust(i+100, 410);
				show_crust(i+150, 410);
				Sleep(250);
				setcolor(BLACK);
				show_crust(i, 410);
				show_crust(i + 50, 410);
				show_crust(i + 100, 410);
				show_crust(i + 150, 410);
			}
			for (int k = 700; k > 250; k -= 50)
			{
				setcolor(WHITE);
				show_coke(k, 300);
				Sleep(250);
				setcolor(BLACK);
				show_coke(k, 300);
			}
			crust -= 4;
			setcolor(WHITE);
			bottle++;
			coke++;
			crust++;
			show_crust((crust - 1) * 50 + 20, 410);
			show_empty((bottle-1) * 50, 200);
			clean();
			output(coke);
			Sleep(500);
		}
	}
	system("pause");          
	closegraph();          // �ر�ͼ�ν���
	return 0;
}