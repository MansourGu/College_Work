#include<iostream>
using namespace std;
int main()
{	
	int n;//����
	cout << "������׳˵����֣�";
	cin >> n;
	int a[3000] = { 0 };//����һ��3000λ����
	a[2999] = 1;//��λ��һ
	for (int i = 1; i <=n; i++)
	{
		for (int j = 0; j <3000; j++)
		{
			a[j] *= i;//ÿһλȥ��
		}
		for (int k = 2999; k >0; k--)
		{
			if (a[k] >= 10)
			{
				a[k - 1] += (a[k] / 10);//����ʮǰһλ��һ
				a[k] = a[k] % 10;//���³���ʮ������
			}
		}
	}
	for (int i = 0; i < 3000; i++)
	{
		if (a[i] != 0)//�Ӳ�������ĵ�һλ��ʼ���
		{
			for (int j = i; j < 3000; j++)
			{
				cout << a[j];//���ÿһλ
			}
			break;
		}
	}
	system("pause");
	return 0;
}