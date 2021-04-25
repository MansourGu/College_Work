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
	cout << "������Բ����İ뾶��߶�:";
	cin >> radius >> height;
	a1.get_radius(radius);
	a1.get_height(height);
	cout<<"Բ��������Ϊ"<<a1.get_area()<<endl;
	cout<<"Բ��������Ϊ"<<a1.get_volume()<<endl;
	cout << "��Ҫ�޸�Բ����İ뾶������1����Ҫ�޸�Բ����߶�������2��Ҫ�ȱ�����������3������0�˳���������ֵ����ѭ��";
	while (cin>>count)
	{
		if (count == 0)
			break;
		else if (count == 1)
		{
			cout << "�������µ�Բ����뾶:";
			cin >> radius;
			a1.get_radius(radius);
			cout << "Բ��������Ϊ" << a1.get_area() << endl;
			cout << "Բ��������Ϊ" << a1.get_volume() << endl;
			cout << "��Ҫ�޸�Բ����İ뾶������1����Ҫ�޸�Բ����߶�������2��Ҫ�ȱ�����������3������0�˳���������ֵ����ѭ��";
			continue;
		}
		else if (count == 2)
		{
			cout << "�������µ�Բ����߶�:";
			cin >> height;
			a1.get_height(height);
			cout << "Բ��������Ϊ" << a1.get_area() << endl;
			cout << "Բ��������Ϊ" << a1.get_volume() << endl;
			cout << "��Ҫ�޸�Բ����İ뾶������1����Ҫ�޸�Բ����߶�������2��Ҫ�ȱ�����������3������0�˳���������ֵ����ѭ��";
			continue;
		}
		else if (count == 3)
		{
			cout << "������ȱ����ŵı�����";
			cin >> times;
			a1 = a1 * times;
			cout << "���ź�Բ��������Ϊ" << a1.get_area() << endl;
			cout << "���ź�Բ��������Ϊ" << a1.get_volume() << endl;
			cout << "��Ҫ�޸�Բ����İ뾶������1����Ҫ�޸�Բ����߶�������2��Ҫ�ȱ�����������3������0�˳���������ֵ����ѭ��";
			continue;
		}
		else
		{
			cout << "��Ҫ�޸�Բ����İ뾶������1����Ҫ�޸�Բ����߶�������2��Ҫ�ȱ�����������3������0�˳���������ֵ����ѭ��";
			continue;
		}
	}
	system("pause");
	return 0;
}