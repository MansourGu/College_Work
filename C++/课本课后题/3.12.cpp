#include<iostream>
#include<string>
using namespace std;
int main()
{
	string letters;
	int count = 0;
	cout << "������һ�λ�" << endl;
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
	cout << "��λ�Ԫ����ĸ�У�" << count << "��";
	system("pause");
	return 0;
}