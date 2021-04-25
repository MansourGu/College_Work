#include<iostream>
using namespace std;
int main()
{
	double a, tem,x;
	cout << "请输入要求近似平方根的数" << endl;
	cin >> a;
	x = a;
	do
	{
		tem = x;
		x = (x + a / x) / 2;
	} while ((tem-x)>1e-5);
	cout << "所求平方根为：" << x;
	system("pause");
	return 0;
}