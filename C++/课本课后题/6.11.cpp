#include<iostream>
#define PI 3.14
using namespace std;
class Cylinder
{
public:
	Cylinder();
	~Cylinder();
	void get_height(double x);
	void get_radius(double y);
	double get_area()
	{
		return ((2 * PI*radius*height)+(2*PI*radius*radius));
	}
	double get_volume()
	{
		return PI * radius*radius*height;
	}
	void adjust_height(double x)
	{
		height += x;
	}
	void adjust_radius(double x)
	{
		radius += x;
	}
	Cylinder operator*(double x);
private:
	double height, radius;
};
void Cylinder::get_height(double x)
{
	height = x;
}
void Cylinder::get_radius(double y)
{
	radius = y;
}
Cylinder::Cylinder()
{
}
Cylinder::~Cylinder()
{
}
Cylinder Cylinder::operator*(double y)
{
	this->height *= y;
	this->radius *= y;
	return *this;
}
int main()
{
	int height, radius,count;
	Cylinder a1;
	double times;
	cout << "请输入圆柱体的半径与高度:";
	cin >> radius >> height;
	a1.get_radius(radius);
	a1.get_height(height);
	cout<<"圆柱体的面积为"<<a1.get_area()<<endl;
	cout<<"圆柱体的体积为"<<a1.get_volume()<<endl;
	cout << "若要修改圆柱体的半径请输入1，若要修改圆柱体高度请输入2若要等比缩放请输入3，输入0退出输入其他值继续循环";
	while (cin>>count)
	{
		if (count == 0)
			break;
		else if (count == 1)
		{
			cout << "请输入新的圆柱体半径:";
			cin >> radius;
			a1.get_radius(radius);
			cout << "圆柱体的面积为" << a1.get_area() << endl;
			cout << "圆柱体的体积为" << a1.get_volume() << endl;
			cout << "若要修改圆柱体的半径请输入1，若要修改圆柱体高度请输入2若要等比缩放请输入3，输入0退出输入其他值继续循环";
			continue;
		}
		else if (count == 2)
		{
			cout << "请输入新的圆柱体高度:";
			cin >> height;
			a1.get_height(height);
			cout << "圆柱体的面积为" << a1.get_area() << endl;
			cout << "圆柱体的体积为" << a1.get_volume() << endl;
			cout << "若要修改圆柱体的半径请输入1，若要修改圆柱体高度请输入2若要等比缩放请输入3，输入0退出输入其他值继续循环";
			continue;
		}
		else if (count == 3)
		{
			cout << "请输入等比缩放的比例：";
			cin >> times;
			a1 = a1 * times;
			cout << "缩放后圆柱体的面积为" << a1.get_area() << endl;
			cout << "缩放后圆柱体的体积为" << a1.get_volume() << endl;
			cout << "若要修改圆柱体的半径请输入1，若要修改圆柱体高度请输入2若要等比缩放请输入3，输入0退出输入其他值继续循环";
			continue;
		}
		else
		{
			cout << "若要修改圆柱体的半径请输入1，若要修改圆柱体高度请输入2若要等比缩放请输入3，输入0退出输入其他值继续循环";
			continue;
		}
	}
	system("pause");
	return 0;
}