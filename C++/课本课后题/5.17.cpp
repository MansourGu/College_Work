#include<iostream>
#include<vector>
#include<cmath>
#include<string>
using namespace std;
int main()
{
	char C[36] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	vector<string>innum ;//������������
	vector<int>middle;//ת��Ϊʮ���ƺ�ĸ���λ�ϵ�����
	vector<int>trans;//ת��ΪĿ����ƺ����λ�ϵ�����
	vector<char>outnum;//������������
	string num;//�������ֵ��м���
	int innumform=0, outnumform=0;//�������ֵĽ��ƣ�������ֵĽ���
	int sum = 0,reside;//ת��Ϊʮ���ƺ��ֵ,����
	cout << "���������� ����end����" << endl;
	while (cin >> num)
	{
		if (num=="end")
		{
			break;
		}
		innum.push_back(num);
	}
	
	for (int i = 0; i < 36; i++)
	{
		for (auto &c : innum)
		{
			for (auto &d : c)
			{
				if (d==C[i])
				{
					middle.push_back(i);
				}
			}
		}
	}
	cout << "�����ֵĽ����Լ�Ҫת���Ľ���" << endl;
	cin >> innumform >> outnumform;
	for (unsigned int i = 0; i < middle.size(); i++)
	{
		middle[i] = middle[i]*(pow(innumform, (middle.size() - i - 1)));
		sum += middle[i];
	}
	while (sum>0)
	{
		reside = sum % outnumform;
		sum /= outnumform;
		trans.push_back(reside);
	}
	for (unsigned int i = 0; i<(trans.size()/2); i++)
	{
		int tem = trans[i];
		trans[i] = trans[trans.size() - i - 1];
		trans[trans.size() - i - 1] = tem;
	}
	for (unsigned int i = 0; i < (trans.size()); i++)
	{  
		for (int j = 0; j < 36; j++)
		{
			if (trans[i]==j)
			{
				outnum.push_back(C[j]);
			}
		}
	}
	cout << "ת���������Ϊ:";
	for (auto c : outnum)
	{
		cout << c;
	}
	system("pause");
	return 0;
}
