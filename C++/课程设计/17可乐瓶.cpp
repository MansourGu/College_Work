#include <graphics.h>      // 就是需要引用这个图形库
#include <conio.h>
#include<easyx.h>
#include<string>
#include<time.h>
#include<iostream>
char c1[] = "2元";
char c2[] = "可乐";
char c3[] = "盖";
char c4[] = "空瓶";
char c5[] = "商店";
char c6[] = "已喝可乐瓶数 ：";//各种需要输出的字符
char c7[] = "瓶盖";
char c8[] = "钱";
int money=5, crust=0, coke=0, bottle=0;//初始的信息
using namespace std;
char c9[10] = { '0','1','2','3','4', '5','6','7','8','9' };
void clean()//抹除上一次的数字
{
	setcolor(BLACK);
	char x[] = "   ";
	outtextxy(220 , 60, x);
}
void output(int x)//输出字符 因为只能一位一位输出
{
	setcolor(WHITE);
	int count = 0;
	while (x > 0)
	{
		{
			int tem = x % 10;//求出最后一位数
			for (int i = 0; i < 10; i++)
			{
				if (tem == i)
				{
					outtextxy(230 - 10 * count, 60, c9[i]);//依次输出
					count++;
					break;
				}
			}
			x /= 10;
		}
	}
}
void show_money(int x ,int y)//显示钱的图样
{
	outtextxy(x-12, y-7, c1);
	circle(x, y, 20);
}
void show_crust(int x, int y)//显示瓶盖的图样
{
	outtextxy(x - 8, y - 8, c3);
	circle(x, y, 20);
	circle(x, y, 17);
}
void show_coke(int left, int top)//显示可乐的图样
{
	rectangle(left, top, left+40, top+100);
	outtextxy(left + 5, top + 45, c2);
}
void show_empty(int left, int top)//显示空瓶的图样
{
	rectangle(left, top, left + 40, top + 100);
	outtextxy(left + 5, top + 45, c4);
}
void show_shop()//显示商店的图样
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


	initgraph(1280,720);   //初始化图形界面 分辨率 1280 X 720
	outtextxy(70, 60, c6);//显示已喝可乐瓶数
	outtextxy(100, 160, c4);//显示空瓶
	outtextxy(100, 360, c7);//显示瓶盖
	outtextxy(100, 510, c8);//显示钱
	show_shop();
	for (int i = 0; i < money; i++)
	{
		show_money(20 + i * 50, 580);
	}
	for (int i = 0; i < money; i++)
	{
		for (int j = (220 - 50 * i); j < 750; j += 20)//实现钱的移动
		{
			setcolor(WHITE);//白色画出 
			show_money(j, 580);
			Sleep(250);
			setcolor(BLACK);//黑色在画一次擦除实现移动的效果
			show_money(j, 580);
		}
		for (int k = 700-i*50; k >150; k-=50)//可乐瓶的移动
		{
			setcolor(WHITE);
			show_coke(k,300);
			Sleep(250);
			setcolor(BLACK);
			show_coke(k, 300);
		}
		coke++;//已喝可乐总数加一
		bottle++;//空瓶数加一
		crust++;//瓶盖加一
		setcolor(WHITE);
		show_crust(20 + i * 50, 410);//画出瓶盖
		show_empty(i * 50, 200);//画出可乐瓶
		clean();
		output(coke);//输出已喝可乐瓶数
	}
	while (crust>=4||bottle>=2)//瓶盖与空瓶之间的转化
	{
		for (;bottle>=2;)//空瓶换可乐
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
		for (; crust >= 4;)//瓶盖换可乐
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
	closegraph();          // 关闭图形界面
	return 0;
}