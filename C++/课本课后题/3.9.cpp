#include<iostream>
using namespace std;
int main()
{
	int big, small,r;
	r = 1;
	cout << "������Ҫ�����Լ����������" << endl;
	cin >> big >> small;
	if (big<small)
	{
		int tem=big;
		big = small;
		small = tem;
	}
	while (r!=0)
	{
		r = big % small;
		if (r!=0)
		{
			big = small;
			small = r;
		}
	}
	cout << "�������Լ��Ϊ��" << small << endl;
	system("pause");
	return 0;
}