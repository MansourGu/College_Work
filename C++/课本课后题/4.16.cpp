#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
void swap(vector<string>&x)
{
	int ran = rand() % 51;
	string tem = x[0];
	x[0] = x[ran];
	x[ran] = tem;
};
int main()
{
	vector<string>color{ "S","H","D","C" };//��ɫ
	vector<string>num{ "1","2","3","4","5","6","7","8","9","10","J","Q","K" };//����
	vector<string>card;//������
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			card.push_back(color[i] + num[j]);
		}
	}
	cout << "������Ϊ��" << endl;
	for (auto c : card)
	{
		cout <<setw(4)<< c;
	}
	int n;
	cout <<endl<< "���ڿ�ʼϴ�� (������1)" << endl;
	while (cin >> n)
	{
		if (n == 1) 
		{
			for (int i = 0; i < 500; i++)//ϴ��
			{
				swap(card);
			}
			for (int i = 0; i < 4; i++)//����
			{
				cout << "��" << (i + 1) << "���˵����ǣ�";
				for (int j = i * 13; j < (i + 1) * 13; j++)
				{
					cout << setw(4) << card[j];
				}
				cout << endl;
			}
			cout << "�����Ҫ����ϴ��������1������Ҫ������0" << endl;
		}
		else break;
	}

	system("pause");
	return 0;
}