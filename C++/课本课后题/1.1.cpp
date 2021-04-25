#include<iostream>
#define PI 3.14
using namespace std;
int main()
{
	double radius, height, volume;
	cout << "请输入半径与高" << endl;
	cin >> radius >> height;
	volume = radius * radius*PI*height;
	cout << "圆柱的体积为：" << volume<<endl;
	system("pause");
	return 0;
}