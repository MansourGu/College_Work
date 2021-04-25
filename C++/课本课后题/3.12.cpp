#include<iostream>
#include<string>
using namespace std;
int main()
{
	string letters;
	int count = 0;
	cout << "请输入一段话" << endl;
	getline(cin, letters);
	for (auto c : letters)
	{
		switch (c)
		{
		case'a':count++; break;
		case'e':count++; break;
		case'i':count++; break;
		case'o':count++; break;
		case'u':count++; break;
		default:break;
		}
	}
	cout << "这段话元音字母有：" << count << "个";
	system("pause");
	return 0;
}