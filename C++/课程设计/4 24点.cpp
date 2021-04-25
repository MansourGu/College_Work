#include<cstdlib>
#include <iostream>
#include<string>
#include <cmath> 
using namespace std;
const double ErrorThreshold = 1E-6;//由于舍入误差，需要加入一个误差阈值，误差在一定范围之内为，判断相等
const int ResultValue = 24; //目标值
#define N 4	//卡片个数
bool PointsGame(int n, string result[4], double number[4]);
void permutation(double * a, int k, int m)//全排列
{
	int i, j;
	if (k == m)
	{
		double tem[N];
		for (i = 0; i <= m; i++)
		{
			tem[i] = a[i];
		}
		string tem1[N];
		for (int i = 0; i < N; i++)
		{
			tem1[i] = to_string(int(tem[i]));//将全排列的数字转为字符串
		}
		PointsGame(4, tem1, tem);
	}
	else
	{
		for (j = k; j < m; j++)
		{
			swap(a[j], a[k]);
			permutation(a, k + 1, m);
			swap(a[j], a[k]);
		}
	}
}
bool PointsGame(int n,string result[4],double number[4])//找全排列
{
	if (n == 1)
	{
		//如果结果为24
		//由于舍入误差，应允许一定范围内的误差

		if (fabs(number[0] - ResultValue) < ErrorThreshold)
		{
			cout << result[0] << endl;
			return true;
		}
		else
		{
			return false;
		}

	}					//将数组第一位与第二位运算的结果放入第一位当中
						//下一次递归运算时 n减去1 会导致数组的最后一位可能缺失
			int i = 0;	//所以将最后一位移到第二位 保证每个数字都不会缺失
			int j = 1;
			double a, b;
			string expa, expb;
			a = number[i];
			b = number[j];
			number[j] = number[n - 1];
			expa = result[i];
			expb = result[j];
			result[j] = result[n - 1];
			result[i] = '(' + expa + '+' + expb + ')';//加法
			number[i] = a + b;
			if (PointsGame(n - 1,result,number))
				return true;
			result[i] = '(' + expa + '-' + expb + ')';//减法
			number[i] = a - b;
			if (PointsGame(n - 1,result,number))
				return true;
			result[i] = '(' + expa + '*' + expb + ')';//乘法
			number[i] = a * b;
			if (PointsGame(n - 1,result,number))
				return true;
			if (b != 0)//除法 除数不能为零
			{
				result[i] = '(' + expa + '/' + expb + ')';
				number[i] = a / b;
				if (PointsGame(n - 1,result,number))
					return true;

			}
			//要是没有找到还原数组；返回false
			number[i] = a;
			number[j] = b;
			result[i] = expa;
			result[j] = expb;
	
	return false;
}
int main()
{
	double number[N];
	cout << "请输入4个数"<<endl;
	for (int i = 0; i < N; i++)
	{
		cin >> number[i];
	}
	permutation(number, 0, 4);
	system("pause");
	return 0;
}