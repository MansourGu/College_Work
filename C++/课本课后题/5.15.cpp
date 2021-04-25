#include <iostream>
#include <iomanip>

using namespace std;
/*
int main()
{
	int n = 6, m = 6;
	cout << "Please input M:";
	cin >> m;
	cout << "Please input N:";
	cin >> n;

	int num[100][100] = { 0 };
	int count = 1;
	int x = 0, y = 0;
	int dx = 0, dy = 1;

	while (count <= m * n)
	{
		num[x][y] = count;
		x += dx;
		y += dy;
		if (dy == 1 && (y >= n - 1 || num[x][y + 1] != 0))
		{
			dx = 1;
			dy = 0;
		}
		else if (dx == 1 && (x >= m - 1 || num[x + 1][y] != 0))
		{
			dx = 0;
			dy = -1;
		}
		else if (dy == -1 && (y <= 0 || num[x][y - 1] != 0))
		{
			dx = -1;
			dy = 0;
		}
		else if (dx == -1 && (x <= 0 || num[x - 1][y] != 0))
		{
			dx = 0;
			dy = 1;
		}
		count++;
	}
	for (int i = 0; i < m; i++)//输出矩阵
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(4) << num[i][j];
		}
		cout << endl << endl;
	}
	system("pause");
	return 0;
}*/
int main() 
{
	int r, c;
	cout << "请输入外螺旋矩阵的行数(行数与列数相乘为最后一位数字)：";
	cin >> r;
	cout << "请输入外螺旋矩阵的列数：";
	cin >> c;
	int num[100][100] = { 0 };
	int x = r-1, y = c-1;
	int dx = -1, dy = 0;
	int count = 1;
	while (count<=r*c)
	{
		num[x][y] = count;
		x += dx;
		y += dy;
		if (dx==-1&&(num[x-1][y]!=0||x<=0) )
		{
			dx = 0; dy = -1;
		}
		else if (dy == -1 && (y <= 0 || num[x][y - 1] != 0))
		{
			dx = 1; dy = 0;
		}
		else if (dx == 1 && ((x >= r-1) || num[x + 1][y] != 0))
		{
			dx = 0;
			dy = 1;
		}
		else if (dy == 1 && ((y >= c - 1) || num[x][y + 1] != 0))
		{
			dx = -1;
			dy = 0;
		}
		count++;
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << setw(4) << num[i][j];
		}
		cout << endl << endl;
	}
	system("pause");
	return 0;
}