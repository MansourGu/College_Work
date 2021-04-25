#include<iostream>
using namespace std;
int main()
{	
	int n;//阶数
	cout << "请输入阶乘的数字：";
	cin >> n;
	int a[3000] = { 0 };//代表一个3000位的数
	a[2999] = 1;//个位置一
	for (int i = 1; i <=n; i++)
	{
		for (int j = 0; j <3000; j++)
		{
			a[j] *= i;//每一位去乘
		}
		for (int k = 2999; k >0; k--)
		{
			if (a[k] >= 10)
			{
				a[k - 1] += (a[k] / 10);//大于十前一位加一
				a[k] = a[k] % 10;//留下除以十的余数
			}
		}
	}
	for (int i = 0; i < 3000; i++)
	{
		if (a[i] != 0)//从不等于零的第一位开始输出
		{
			for (int j = i; j < 3000; j++)
			{
				cout << a[j];//输出每一位
			}
			break;
		}
	}
	system("pause");
	return 0;
}