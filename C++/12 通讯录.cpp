#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct Student //建立一个结构体 存放一个人的姓名，性别，电话，地址，电子邮箱。
{
	int ID;
	string name;
	string sex;
	string phone_number;
	string address;
	string e_mail;
};
vector<Student>s;//将所有添加的联系人 放入student 类型的容器中
void display(Student &a);//显示一个人的信息
void menu();//显示菜单
void paixu();//对通讯录按字母排序
void get_information(Student &a)//获取联系人的各种信息
{
	cout << "请输入要添加联系人的信息：" << endl;
	cout << "姓名 ：";
	cin >> a.name;
	if ((a.name[0]) >= 97 &&a.name[0] <= 122)//将小写统一转化为大写 方便排序
	{
		a.name[0] -= 32;
	}
	for (int i = 0; i < s.size(); i++)
	{
		if (a.name == s[i].name)//检测该联系人以前是否录入
		{
			cout << "该联系人已存在";
			display(s[i]);
			system("pause");
			menu();
		}
	}
	cout << "性别 ： ";
	cin >> a.sex;
	cout << "电话号码 ：";
	cin >> a.phone_number;
	cout << "住址 : ";
	cin >> a.address;
	cout << "电子邮箱 ： ";
	cin >> a.e_mail;
	a.ID = s.size() + 1;
}

void add()//添加联系人
{
	Student s1;//新建结构体变量 
	get_information(s1);//获取信息
	s.push_back(s1);//将该联系人放入通讯录
	paixu();//对通讯进行排序
}
void delete_relitives(int i)//删除联系人
{
	s.erase(s.begin() + (s[i].ID - 1));//删除指定位置的联系人
	for (int m = s[i].ID - 2; m < s.size(); m++)//所删除的联系人后面的人 编号减一
	{
		s[m].ID-=1;
	}
	cout << "该联系人已删除";
}
void display(Student &a)//显示某个联系人的信息
{
	cout << a.ID << "、 姓名：" << a.name << endl;
	cout << "  性别 ：" << a.sex << endl;
	cout << "  电话号码 ：" << a.phone_number << endl;
	cout << "  住址 ：" << a.address << endl;
	cout << "  电子邮箱 ：" << a.e_mail << endl;
}
void Search()//查找
{
	cout << "请选择查找方式：" << endl;
	cout << "①按照名字查找" << endl;
	cout << "②按照电话号码查找" << endl;
	int tem;
	cin >> tem;
	if (tem == 1)//判断查找方式
	{
	mark1:
		string name;
		cout << "请输入要查找的姓名 ：" << endl;
		cin >> name;
		if (name[0] >= 97 && name[0] <= 122)//将输入的名字首字母大写 方便与通讯录统一
		{
			name[0] -= 32;
		}
		for (int i = 0; i < s.size(); i++)
		{
			if (name == s[i].name)//查找相同人名
			{
				display(s[i]);
				system("pause");
				cout << "是否要删除该联系人？ Y/N" << endl;
				char judge;
				cin >> judge;
				if (judge == 'Y')
				{
					delete_relitives(i);
					system("pause");
				}
				return;
			}
			cout << "查无此人 请重新输入：";
			system("pause");
			goto mark1;
		}
	}
	if (tem == 2)
	{
	mark2:
		string number;
		cout << "请输入要查找人的电话号码 ：" << endl;
		cin >> number;
		for (int i = 0; i < s.size(); i++)
		{
			if (number == s[i].phone_number)
			{
				display(s[i]);
				system("pause");
				cout << "是否要删除该联系人？ Y/N" << endl;
				char judge;
				cin >> judge;
				if (judge == 'Y')
				{
					delete_relitives(i);
					system("pause");
				}
				return;
			}
			cout << "查无此人 请重新输入：";
			system("pause");
			goto mark2;
		}
	}
}
void paixu()
{
	for (int i = 0; i < s.size() - 1; i++)
	{
		for (int j = i + 1; j < s.size(); j++)
		{
			if ((s[j].name[0] < (s[i].name)[0]))//按照每个联系人的姓名首字母排序
			{
				Student tem;//交换
				tem = s[j];
				s[j] = s[i];
				s[i] = tem;
				int tem_id1;//编号交换
				tem_id1 = s[i].ID;
				s[i].ID = s[j].ID;
				s[j].ID = tem_id1;
			}
		}
	}
}
void menu()
{
	system("cls");
	cout << "******************************************************************************" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                            欢迎使用通讯录                                  *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                          制作人  ：谷曼苏                  *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*          请选择功能 ①查看所有联系人                                       *" << endl;
	cout << "*                     ②查找联系人                                           *" << endl;
	cout << "*                     ③添加联系人                                           *" << endl;
	cout << "*                     ④退出                                                 *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "******************************************************************************" << endl;
	int judge;
	cin >> judge;
	if (judge == 1)
	{
		system("cls");
		for (int i = 0; i < s.size(); i++)
		{
			display(s[i]);
		}
		cout << "共 " << s.size() << "条记录" << endl;
		cout << "按回车键返回主菜单";
		system("pause");
		menu();
	}
	if (judge == 2)
	{
		system("cls");
		Search();
		menu();
	}
	if (judge == 3)
	{
		system("cls");
		add();
		system("pause");
		menu();
	}
	if (judge == 4)
	{
		exit(0);
	}
}
int main()
{	
	menu();
	return 0;
}
