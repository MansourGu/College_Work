#include<iostream>
using namespace std;
int main()
{
	double a, tem,x;
	cout << "������Ҫ�����ƽ��������" << endl;
	cin >> a;
	x = a;
	do
	{
		tem = x;
		x = (x + a / x) / 2;
	} while ((tem-x)>1e-5);
	cout << "����ƽ����Ϊ��" << x;
	system("pause");
	return 0;
}