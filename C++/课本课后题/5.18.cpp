#include<iostream>
using namespace std;
int fun(int x, int y)
{
	
	if (x<y)
	{
		int tem = y;
		y = x;
		x = tem;
	}
	int reside = x % y;
	while (reside!=0)
	{
		x = y;
		y = reside;
		reside = x % y;
	}
	return y;
}
int main()
{
	int num1, num2;
	cout << "������Ҫ�����Լ������������" << endl;
	cin >> num1 >> num2;
	cout<<fun(num1, num2);
	system("pause");
	return 0;
}