#include<iostream>
#define PI 3.14
using namespace std;
int main()
{
	double radius, height, volume;
	cout << "������뾶���" << endl;
	cin >> radius >> height;
	volume = radius * radius*PI*height;
	cout << "Բ�������Ϊ��" << volume<<endl;
	system("pause");
	return 0;
}