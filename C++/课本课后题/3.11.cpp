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
					cout << i << "��ʮԪ" << j << "����Ԫ" << k << "��һԪ" << endl;
					count++;
				}
			}
		}
	}
	cout<<endl << "����" << count << "�ֻ��㷽��";
	system("pause");
	return 0;
}