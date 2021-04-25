#include<iostream>
#define PI 3.14
using namespace std;
int main()
{
	double radius,area;
	cout << "请输入圆的半径：" << endl;
	cin >> radius;
	area = radius * radius*PI;
	cout << "圆的面积是：" << area << endl;
	system("pause");
	return 0;
}