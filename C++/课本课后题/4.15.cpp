#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int>v1;
	int num;
	cout << "������һ������ ������ĸ����" << endl;
	while (cin>>num)
	{
		v1.push_back(num);
	}
	cout << "����������������Ϊ��" << endl;
	for (int i = 0; i < v1.size(); )
	{
		if (i+1==v1.size())
		{
			cout << "���һ��Ԫ��û�в���������� �������" << v1[i];
			break;
		}
		cout << v1[i] + v1[i + 1]<<"  ";
		i += 2;
	}
	cout <<endl<< "��ͷβԪ������������Ϊ��" << endl;
	for (int i = 0; i < v1.size()/2+1; i++)
	{
		if (i == (v1.size()-i-1))
		{
			cout << "�������������������м������û�в�����Ը����ǣ�" << v1[i];
			break;
	    }
		cout << v1[i] + v1[v1.size() - i - 1]<<"  ";
	}
	system("pause");
	return 0;
}