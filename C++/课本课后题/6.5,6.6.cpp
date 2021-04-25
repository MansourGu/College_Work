#include<iostream>
#include<string>
using namespace std;
class Person
{
	string name,address;
public:
	Person(Person & x);
	Person();
	~Person();
	void get_name(string &s)
	{
		name = s;
	}
	void get_address(string &s)
	{
		address = s;
	}
	void print()
	{
		cout << name<<"   "<<address<<endl;
	}
	Person operator=(Person &y);

private:
	

};
Person::Person(Person&x)
{
	name = x.name;
	address = x.address;
}
Person Person:: operator=(Person &y)
{
	this->name = y.name;
	this->address = y.address;
	return *this;
}
Person::Person()
{

}
Person::~Person()
{

}
int main()
{
	string name, address;
	cout << "请输入您的姓名：";
	getline(cin, name);
	cout << "请输入您的地址";
	getline(cin, address);
	Person a;
	a.get_name(name);
	a.get_address(address);
	Person b(a);
	Person c;
	c = b;
	a.print();
	b.print();
	c.print();
	system("pause");
	return 0;
}