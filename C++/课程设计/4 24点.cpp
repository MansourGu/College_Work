#include<cstdlib>
#include <iostream>
#include<string>
#include <cmath> 
using namespace std;
const double ErrorThreshold = 1E-6;//������������Ҫ����һ�������ֵ�������һ����Χ֮��Ϊ���ж����
const int ResultValue = 24; //Ŀ��ֵ
#define N 4	//��Ƭ����
bool PointsGame(int n, string result[4], double number[4]);
void permutation(double * a, int k, int m)//ȫ����
{
	int i, j;
	if (k == m)
	{
		double tem[N];
		for (i = 0; i <= m; i++)
		{
			tem[i] = a[i];
		}
		string tem1[N];
		for (int i = 0; i < N; i++)
		{
			tem1[i] = to_string(int(tem[i]));//��ȫ���е�����תΪ�ַ���
		}
		PointsGame(4, tem1, tem);
	}
	else
	{
		for (j = k; j < m; j++)
		{
			swap(a[j], a[k]);
			permutation(a, k + 1, m);
			swap(a[j], a[k]);
		}
	}
}
bool PointsGame(int n,string result[4],double number[4])//��ȫ����
{
	if (n == 1)
	{
		//������Ϊ24
		//����������Ӧ����һ����Χ�ڵ����

		if (fabs(number[0] - ResultValue) < ErrorThreshold)
		{
			cout << result[0] << endl;
			return true;
		}
		else
		{
			return false;
		}

	}					//�������һλ��ڶ�λ����Ľ�������һλ����
						//��һ�εݹ�����ʱ n��ȥ1 �ᵼ����������һλ����ȱʧ
			int i = 0;	//���Խ����һλ�Ƶ��ڶ�λ ��֤ÿ�����ֶ�����ȱʧ
			int j = 1;
			double a, b;
			string expa, expb;
			a = number[i];
			b = number[j];
			number[j] = number[n - 1];
			expa = result[i];
			expb = result[j];
			result[j] = result[n - 1];
			result[i] = '(' + expa + '+' + expb + ')';//�ӷ�
			number[i] = a + b;
			if (PointsGame(n - 1,result,number))
				return true;
			result[i] = '(' + expa + '-' + expb + ')';//����
			number[i] = a - b;
			if (PointsGame(n - 1,result,number))
				return true;
			result[i] = '(' + expa + '*' + expb + ')';//�˷�
			number[i] = a * b;
			if (PointsGame(n - 1,result,number))
				return true;
			if (b != 0)//���� ��������Ϊ��
			{
				result[i] = '(' + expa + '/' + expb + ')';
				number[i] = a / b;
				if (PointsGame(n - 1,result,number))
					return true;

			}
			//Ҫ��û���ҵ���ԭ���飻����false
			number[i] = a;
			number[j] = b;
			result[i] = expa;
			result[j] = expb;
	
	return false;
}
int main()
{
	double number[N];
	cout << "������4����"<<endl;
	for (int i = 0; i < N; i++)
	{
		cin >> number[i];
	}
	permutation(number, 0, 4);
	system("pause");
	return 0;
}