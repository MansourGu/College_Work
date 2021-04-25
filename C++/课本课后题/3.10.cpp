#include<iostream>
using namespace std;
int main()
{
	for (int i = 1; i <= 500; i++)
	{
		int m = i % 3;//除以三的余数
		int n = i % 5;//除以五的余数
		int j = i % 7;//除以七的余数
		if (m==2&&n==3&&j==2)
		{
			cout << i << " ";
		}
	}
	system("pause");
	return 0;
}