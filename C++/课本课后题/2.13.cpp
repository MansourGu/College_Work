#include<iostream>
using namespace std;
int main()
{
	double length, height, width, volume;
	cout << "�����볤����ĳ����" << endl;
	cin >> length >> width >> height;
	volume = length * width*height;
	cout << "���������Ϊ��" << volume;
	system("pause");
	return 0;
}