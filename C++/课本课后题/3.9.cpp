#include<iostream>
using namespace std;
int main()
{
	int big, small,r;
	r = 1;
	cout << "请输入要求最大公约数的两个数" << endl;
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
	cout << "所求最大公约数为：" << small << endl;
	system("pause");
	return 0;
}