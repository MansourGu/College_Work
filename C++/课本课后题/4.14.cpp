#include<iostream>
#include<string>

using namespace std;
int main()
{   
	string s1;
	cout << "请输入一行由英文组成的字符串" << endl;
	getline(cin, s1);
	for (int i = 0; i <s1.size(); i++)
	{
		if (isspace(s1[i]))
		continue;
		for (auto &c : s1)
		{
			if (isspace(c))
				continue;
			if (c>s1[i])
			{
				char tem;
				tem = s1[i];
				s1[i] = c;
				c = tem;
			}
		}
	}
	cout << s1;
	system("pause");
	return 0;
}