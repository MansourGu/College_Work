#include<iostream>
#include<cmath>
#include<iomanip>
#define N 3 //����ʽ����
using namespace std;
double record[N][N];//�������
double reverse1[N][N];//�����
double det = 0.0;//����ʽ��ֵ
double cal_det(double a[N][N], int n)//������ʽ����չ����������ʽ��ֵ
{
	if (n == 1)//������ʽ��ֻ��һ��Ԫ�ص�ʱ�����
	return a[0][0];
	double temp[N][N] = { 0.0 };
	double result=0.0;
	for (int i = 0; i < n; i++)//��¼ԭ����ʽ�к�
	{
		for (int j = 0; j < n - 1; j++)//��¼������ʽ�к�
		{
			for (int k = 0; k < n - 1; k++)//��¼�µ�����ʽ�к�
			{
				temp[j][k] = a[j + 1][k >= i ? k + 1 : k];//�����յ�һ�е�i��Ԫ��չ���������ʽ�����µ�����ʽ��ȥ��
			}
		}
		double t = cal_det(temp, n - 1);
		if (i % 2 == 0)//�жϷ��� ������֮����ż����չ����ķ���������
		{
			result += a[0][i] * t;
		}
		else
		{
			result -= a[0][i] * t;
		}
	}
	return result;
}
double cal_det1(double a[N-1][N-1], int n)//������ʽ����չ����������ʽ��ֵ
{
	if (n== 1)//������ʽ��ֻ��һ��Ԫ�ص�ʱ�����
		return a[0][0];
	double temp[N-1][N-1] = { 0.0 };
	double result = 0.0;
	for (int i = 0; i < n; i++)//��¼ԭ����ʽ�к�
	{
		for (int j = 0; j < n - 1; j++)//��¼������ʽ�к�
		{
			for (int k = 0; k < n - 1; k++)//��¼�µ�����ʽ�к�
			{
				temp[j][k] = a[j + 1][k >= i ? k + 1 : k];//�����յ�һ�е�i��Ԫ��չ���������ʽ�����µ�����ʽ��ȥ��
			}
		}
		double t = cal_det1(temp, n - 1);
		if (i % 2 == 0)//�жϷ��� ������֮����ż����չ����ķ���������
		{
			result += a[0][i] * t;
		}
		else
		{
			result -= a[0][i] * t;
		}
	}
	return result;
}
void cal_A(double a[N][N],int n)//��������
{
	for (int i = 0; i < n; i++)//ԭ����ʽ�к�
	{
		for (int j = 0; j < n; j++)//ԭ����ʽ�к�
		{
			double temp[N - 1][N - 1] = { 0.0 };//����ÿһ��չ��������ʽ
			for (int m = 0; m < n-1; m++)//������ʽ�к�
			{
				for (int k = 0; k < n-1; k++)//������ʽ�к�
				{
					temp[m][k] = a[m >= i ? m + 1 : m][k >= j ? k + 1 : k];//����ѡԪ�ص��������л������Ԫ�ط����¾���
				}
			}
			record[j][i] = pow(-1,(i+j))*cal_det1(temp, n - 1);
		}
	}
}
void cal_reverse(double a[N][N], int n)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			reverse1[i][j] = float(record[i][j]/det);
		}
	}
}
int main()
{
	double a[N][N]= { {1,2,3},{0,4,4},{0,0,3} };
	/*cout << "������" << N << "�׾����Ԫ�أ��������룩��";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> a[i][j];
		}

	}*/
	det = cal_det(a, 3);
	cout<<"���������ʽ��ֵΪ��" <<det<<endl;
	cal_A(a, 3);
	cout << "�������Ϊ��" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout<<setw(4) << record[i][j];
		}
		cout << endl;
	}
	cal_reverse(a, 3);
	cout << "���������Ϊ:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout<<setw(10) << reverse1[i][j];
		}
		cout << endl;
	}
	system("pause");
	return 0;
}