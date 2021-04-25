#include<iostream>
#include<cmath>
#include<iomanip>
#define N 3 //行列式阶数
using namespace std;
double record[N][N];//伴随矩阵
double reverse1[N][N];//逆矩阵
double det = 0.0;//行列式的值
double cal_det(double a[N][N], int n)//将行列式按行展开计算行列式的值
{
	if (n == 1)//当行列式中只有一个元素的时候输出
	return a[0][0];
	double temp[N][N] = { 0.0 };
	double result=0.0;
	for (int i = 0; i < n; i++)//记录原行列式行号
	{
		for (int j = 0; j < n - 1; j++)//记录新行列式行号
		{
			for (int k = 0; k < n - 1; k++)//记录新的行列式列号
			{
				temp[j][k] = a[j + 1][k >= i ? k + 1 : k];//将按照第一行第i个元素展开后的余子式放入新的行列式中去。
			}
		}
		double t = cal_det(temp, n - 1);
		if (i % 2 == 0)//判断符号 当行列之和是偶数是展开后的符号是正数
		{
			result += a[0][i] * t;
		}
		else
		{
			result -= a[0][i] * t;
		}
	}
	return result;
}
double cal_det1(double a[N-1][N-1], int n)//将行列式按行展开计算余子式的值
{
	if (n== 1)//当行列式中只有一个元素的时候输出
		return a[0][0];
	double temp[N-1][N-1] = { 0.0 };
	double result = 0.0;
	for (int i = 0; i < n; i++)//记录原行列式行号
	{
		for (int j = 0; j < n - 1; j++)//记录新行列式行号
		{
			for (int k = 0; k < n - 1; k++)//记录新的行列式列号
			{
				temp[j][k] = a[j + 1][k >= i ? k + 1 : k];//将按照第一行第i个元素展开后的余子式放入新的行列式中去。
			}
		}
		double t = cal_det1(temp, n - 1);
		if (i % 2 == 0)//判断符号 当行列之和是偶数是展开后的符号是正数
		{
			result += a[0][i] * t;
		}
		else
		{
			result -= a[0][i] * t;
		}
	}
	return result;
}
void cal_A(double a[N][N],int n)//求伴随矩阵
{
	for (int i = 0; i < n; i++)//原行列式行号
	{
		for (int j = 0; j < n; j++)//原行列式行号
		{
			double temp[N - 1][N - 1] = { 0.0 };//按照每一项展开的余子式
			for (int m = 0; m < n-1; m++)//新行列式行号
			{
				for (int k = 0; k < n-1; k++)//新行列式列号
				{
					temp[m][k] = a[m >= i ? m + 1 : m][k >= j ? k + 1 : k];//将所选元素的所在行列划掉后的元素放入新矩阵
				}
			}
			record[j][i] = pow(-1,(i+j))*cal_det1(temp, n - 1);
		}
	}
}
void cal_reverse(double a[N][N], int n)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			reverse1[i][j] = float(record[i][j]/det);
		}
	}
}
int main()
{
	double a[N][N]= { {1,2,3},{0,4,4},{0,0,3} };
	/*cout << "请输入" << N << "阶矩阵的元素（按行输入）：";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> a[i][j];
		}

	}*/
	det = cal_det(a, 3);
	cout<<"矩阵的行列式的值为：" <<det<<endl;
	cal_A(a, 3);
	cout << "伴随矩阵为：" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout<<setw(4) << record[i][j];
		}
		cout << endl;
	}
	cal_reverse(a, 3);
	cout << "所求逆矩阵为:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout<<setw(10) << reverse1[i][j];
		}
		cout << endl;
	}
	system("pause");
	return 0;
}