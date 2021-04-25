#include<iostream>
#define PI 3.14
using namespace std;

class Cylinder
{
	double m_radius, m_height;
public:
	double volume()
	{
		return m_radius * m_radius*m_height*PI;

	}

	Cylinder(double i = 0, double h = 0) :m_radius(i), m_height(h) {}
};
int main()
{
	Cylinder object(1.0, 1.0);
	double vol = object.volume();
	cout << vol << endl;
	system("pause");
	return 0;
}