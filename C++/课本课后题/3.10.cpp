#include<iostream>
using namespace std;
int main()
{
	for (int i = 1; i <= 500; i++)
	{
		int m = i % 3;//������������
		int n = i % 5;//�����������
		int j = i % 7;//�����ߵ�����
		if (m==2&&n==3&&j==2)
		{
			cout << i << " ";
		}
	}
	system("pause");
	return 0;
}