#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
	vector<char>v1;
	char s1;
	cout << "请输入一段话 输入* 结束" << endl;
	while (cin >> s1)
	{
		if (s1 == '*')
			break;
		v1.push_back(s1);
	}
	for (auto c : v1)
	{
		if (c == '\32')
		{
			continue;
		}
		cout << c;
	}
	system("pause");
	return 0;
}