#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n1, n2;
	cout << "请输入第一个多项式的次数：";
	cin >> n1;
	int *a1 = new int[n1+1];//新建动态数组存储 各个次数的系数
	cout << "请输入第二个多项式的次数：";
	cin >> n2;
	int *a2 = new int[n2+1];
	cout << "请输入依次输入第一个多项式的系数（次数由低到高）：";
	for (int i = 0; i <= n1; i++)
	{
		cin >> a1[i];
	}
	cout << "请输入依次输入第一个多项式的系数（次数由低到高）：";
	for (int i = 0; i <= n2; i++)
	{
		cin >> a2[i];
	}
	int *a3 = new int[n1 + n2 + 1];//新建数组存放输出后的结果
	for (int i = 0; i <= n1+n2+1; i++)
	{
		a3[i] = 0;//初始化
	}
	for (int i = 0; i <=n1 ; i++)
	{
		for (int j = 0; j <=n2; j++)
		{
			a3[i + j] += (a1[i] * a2[j]);//将各个次数的系数相乘 并将相同次数的系数相加
		}
	}
	cout << "两个多项式的乘积为：";
	for (int i = 0; i <=n1+n2+1; i++)
	{
		if (i==0)
		{
			cout << a3[i] << "+";
			continue;
		}
		if (a3[i]==0)
		{
			continue;
		}
		if (a3[i]==1)
		{
			cout<< "X\""<<i<<"\""<<" ";
			continue;
		}
		if (i==n1+n2)
		{
			cout << a3[i] << "X\""<<i<<"\"";
			continue;
		}
		cout << a3[i] << "X \""<<i<<"\""<<"+";
	}
	cout << endl;
	system("pause");
	return 0;
}