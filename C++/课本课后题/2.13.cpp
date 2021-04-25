#include<iostream>
using namespace std;
int main()
{
	double length, height, width, volume;
	cout << "请输入长方体的长宽高" << endl;
	cin >> length >> width >> height;
	volume = length * width*height;
	cout << "长方体体积为：" << volume;
	system("pause");
	return 0;
}