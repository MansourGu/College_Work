#include <iostream>
#include <string>//�˴�����Դ������
using namespace std;
void swap(char &a, char &b)
{
	char tem = a;
	a = b;	
	b = tem;
}
void permute(string str, int k)
{
	if (k == str.size() - 1)
	{
		cout << str << endl;
	}
	else if (k >= str.size()) return;
	for (int i = k; i < str.size(); i++) 
	{
		swap(str[i], str[k]);
		permute(str, k + 1);
		swap(str[i], str[k]);
	}
}

void perm(string str) 
{
	if (str.empty())
		return;
	permute(str, 0);
}

int main()
{
	string str;
	cout << "������ȫ���е�����"<<endl;
	cin >> str;
	perm(str);
	system("pause");
	return 0;
}
