#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n1, n2;
	cout << "�������һ������ʽ�Ĵ�����";
	cin >> n1;
	int *a1 = new int[n1+1];//�½���̬����洢 ����������ϵ��
	cout << "������ڶ�������ʽ�Ĵ�����";
	cin >> n2;
	int *a2 = new int[n2+1];
	cout << "���������������һ������ʽ��ϵ���������ɵ͵��ߣ���";
	for (int i = 0; i <= n1; i++)
	{
		cin >> a1[i];
	}
	cout << "���������������һ������ʽ��ϵ���������ɵ͵��ߣ���";
	for (int i = 0; i <= n2; i++)
	{
		cin >> a2[i];
	}
	int *a3 = new int[n1 + n2 + 1];//�½������������Ľ��
	for (int i = 0; i <= n1+n2+1; i++)
	{
		a3[i] = 0;//��ʼ��
	}
	for (int i = 0; i <=n1 ; i++)
	{
		for (int j = 0; j <=n2; j++)
		{
			a3[i + j] += (a1[i] * a2[j]);//������������ϵ����� ������ͬ������ϵ�����
		}
	}
	cout << "��������ʽ�ĳ˻�Ϊ��";
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