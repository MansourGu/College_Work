#include<iostream>
#include<iomanip>
#include<cstdlib>
using namespace std;
#define range 10//棋盘大小
char a[range][range];//棋盘
int out(int x, int y)//判断是否出界
{
	if (x>range-1||x<0||y>range - 1 ||y<0)
	{
		return 1;
	}
	return 0;
}
void test_right(int x,int y,char c)//右对角线的检测（左下到右上）
{
	int sum , i, j,row,col;
	for (i = x + 4, j = y - 4;i<=x,j<=y;i--,j++)//从左下到落子位依次检测
	{
		sum = 0;
		if (out(i,j)==1)
		{
			continue;
		}
		for (row = i,col = j; sum<=5; row--,col++)//行号减一 列号加一
		{
			if (a[row][col] != c)//检测子的个数 若有不连续直接退出
			{
				break;
			}
			else
			{
				sum++;
			}
		}
		if (sum==5)
		{
			cout << "执" << c << "棋者获胜!!!";
			system("pause");
			exit(0);
		}
	}
}
void test_left(int x, int y, char c)//左对角线的检测 （左上到右下）
{
	int sum, i, j,row,col;
	for (i = x - 4, j = y - 4; i <= x, j <= y; i++, j++)
	{
		sum = 0;
		if (out(i, j) == 1)
		{
			continue;
		}
		for ( row = i, col = j; sum <= 5; row++, col++)
		{
			if (a[row][col] != c)
			{
				break;
			}
			else
			{
				sum++;
			}
		}
		if (sum == 5)
		{
			cout << "执" << c << "棋者获胜!!!";
			system("pause");
			exit(0);
		}
	}
}
void test_left_to_right(int x, int y, char c)//从左到右的检测
{
	int sum, i,col;
	for (i=y-4; i <= y; i++)//行号不变列号依次加一
	{
		sum = 0;
		if (out(x,i) == 1)
		{
			continue;
		}
		for ( col = i; sum <= 5; col++)
		{
			if (a[x][col] != c)
			{
				break;
			}
			else
			{
				sum++;
			}
		}
		if (sum == 5)
		{
			cout << "执" << c << "棋者获胜!!!";
			system("pause");
			exit(0);
		}
	}
}
void test_down_to_up(int x, int y, char c)//从下到上的检测
{
	int sum, i,row;
	for (i = x-4; i <= x; i++)//列号不变行号依次加一
	{
		sum = 0;
		if (out(i, y) == 1)
		{
			continue;
		}
		for (row = i; sum <= 5; row++)
		{
			if (a[row][y] != c)
			{
				break;
			}
			else
			{
				sum++;
			}
		}
		if (sum == 5)
		{
			cout << "执" << c << "棋者获胜!!!";
			system("pause");
			exit(0);
		}
	}
}
void test(int x, int y, char c)//总检测
{
	if (a[x+1][y-1]==c||a[x-1][y+1]==c)//检测右对角线
	{
		test_right(x, y, c);
	}
	if (a[x-1][y-1]==c||a[x+1][y+1]==c)//检测左对角线
	{
		test_left(x, y, c);
	}
	if (a[x-1][y]==c||a[x+1][y]==c)//检测列
	{
		test_down_to_up(x, y, c);
	}
	if (a[x][y-1]==c||a[x][y+1]==c)//检测行
	{
		
		test_left_to_right(x, y, c);
	}
}

void put_chess(char c)//下棋
{
part1:
	int x = ' ', y = ' ';
	cout << "请执" << c << "棋的选手下棋 （输入坐标）：";
	cin >> x >> y;
	if (out(x, y) == 1)
	{
		cout << "此棋超出范围请重输！";
		goto part1;
	}
	if (a[x][y] != ' ')
	{
		cout << "此位置已被占用！ 请重输！";
		goto part1;
	}
	a[x][y] = c;
	test(x, y, c);
}
void print()//打印棋盘
{
	cout << " 丨";
	for (int j = 0; j < range; j++)
	{
			cout<< setw(1) << j << "丨";
	}
	cout << endl;
	for (int i = 0; i < range; i++)
	{
		for (int k = 0; k < (range+1)*3; k++)
		{
			cout << "-";
		}
		cout << endl;
		cout << i << "丨";
		for (int j = 0; j < range; j++)
		{
			cout<<setw(1)<<a[i][j] << "丨";
		}
		cout << endl;
	}
	cout << endl;
}
int main()
{part2:
    print();
	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < range; j++)
		{
			a[i][j] = ' ';
		}
	}
	cout <<setw(3*(range/2)+4)<< "游戏开始" << endl;
	int round = 0;//回合数
	while (round<=(range*range))
	{
		if (round==range*range)
		{
			cout << "平局！" << endl;
			cout << "重新开始！" << endl;
			goto part2;
		}
		put_chess('B');// 黑棋
		system("cls");//通过清屏再打印实现动态变化
		print();
		put_chess('W');//白棋
		system("cls");
		print();
		round++;
	}
	system("pause");
	return 0;
}