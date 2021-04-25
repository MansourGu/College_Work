#include<iostream>
using namespace std;
int main()
{
	int count = 0;
	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j <=20; j++)
		{
			for (int k = 0; k <= 100; k++)
			{
				if (i * 10 + j * 5 + k * 1 == 100)
				{
					cout << i << "张十元" << j << "张五元" << k << "张一元" << endl;
					count++;
				}
			}
		}
	}
	cout<<endl << "共有" << count << "种换算方法";
	system("pause");
	return 0;
}