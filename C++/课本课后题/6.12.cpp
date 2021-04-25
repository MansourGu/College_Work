#include<iostream>
using namespace std;
class Complex 
{
	double m_real;
	double m_image;
	friend void cin1(Complex &x)
	{
		cout << "�����븴����ʵ�����鲿��" << endl;
	
		cin >> x.m_real >> x.m_image;
	}
	friend void cout1(Complex x)
	{
		cout << "�ø���Ϊ��" << x.m_real << "+" << x.m_image <<"i"<< endl;
	}
public:
	Complex() { m_real = 0; m_image = 0; }
	~Complex ();
	void get_real(double x)
	{
		m_real = x;
	}
	Complex operator=(Complex &y);
	Complex operator+=(Complex &y);
	bool operator==(Complex &y);
	Complex operator+(Complex &y);
	Complex operator-(Complex &y);
};
Complex ::~Complex ()
{
}
Complex Complex::operator=(Complex &y)
{
	this->m_real = y.m_real;
	this->m_image = y.m_image;
	return *this;
}
Complex Complex::operator+=(Complex &y)
{
	this->m_real += y.m_real;
	this->m_image += y.m_image;
	return *this;
}
bool Complex::operator==(Complex &y)
{
	if ((this->m_real==y.m_real)&&(this->m_image==y.m_image))
	{
		return true;
	}
	else  return false;
}
Complex Complex::operator+(Complex &y)
{
	Complex temp;
	temp.m_real = this->m_real + y.m_real;
	temp.m_image = this->m_image + y.m_image;
	return temp;
}
Complex	Complex::operator-(Complex &y)
{
	Complex temp;
	temp.m_real = this->m_real - y.m_real;
	temp.m_image = this->m_image - y.m_image;
	return temp;
}
int main()
{
	Complex a1, a2,a3;
	cin1(a1);
	cin1(a2);
	cout << "a1+a2�ĺͣ�";
	cout1(a1 + a2);
	cout << "a1-a2=:";
	cout1(a1 - a2);
	cout << "a1+=a1:";
	cout1(a1 += a1);
	cout << "a1�Ƿ����a2";
	if (a1==a2)
	{
		cout << "����";
	}
	else
	{
		cout << "������";
	}
	cout << endl;
	a3 = a1;
	cout << "a3��ֵΪ��";
	cout1(a3);
	system("pause");
	return 0;
}