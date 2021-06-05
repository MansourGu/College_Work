#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
using namespace std;
#define MAX_SIZE 512//最大分区大小
class PD//分区描述器

{
public:
	int m_flag;//标志
	int m_size;//分区大小
	PD* next;//下一块地址
public:
	PD(PD* n = NULL, int flag = 0, int size = 0)//复制构造函数
	{
		m_flag = flag;
		m_size = size;
		next = n;
	}
	friend class Manage;
};

class PCB//进程结点,存放分配成功的进程
{
private:
	string m_name;	//进程名
	int m_size;	//进程大小
	int m_begin;	//进程起始地址
public:
	PCB(string n = "无", int s = 0, int b = 0)//复制构造函数
	{
		m_name = n;
		m_size = s;
		m_begin = b;
	}
	friend class Manage;
};
class Manage
{
public:
	PD* head;//头节点
	vector<PCB>m_list;
public:
	Manage(PD* p = NULL)
	{
		head = p;
	}

	void first_time();//首次适应算法
	void best();//最佳适应算法
	void worst();//最坏适应算法

	void release();//回收

	void Display();//显示

	friend class PCB;
	friend class PD;
};

//首次适应算法
void Manage::first_time()
{
	string name;
	int size, addr = 0;
	cout << "请输入进程名和大小：";
	cin >> name >> size;
	PD* p(head->next);

	while (p != NULL)
	{
		addr += (p->m_size + 1);
		if (p->m_flag == 0)
		{
			if (p->m_size > size)
			{
				p->m_size -= (size + 1);
				PD* temp = new PD(p->next, 1, size);
				p->next = temp;
				addr -= (size + 1);
				break;
			}
			else if (p->m_size == size)
			{
				p->m_flag = 1;
				addr -= (size + 1);
				break;
			}
			else p = p->next;
		}
		else p = p->next;
	}
	if (p == NULL)cout << "分配失败！" << endl;
	else
	{
		PCB temp(name, size, addr);
		m_list.push_back(temp);
	}
}

//最佳
void Manage::best()
{
	cout << "输入进程名和大小:";
	string name; int size, addr1(0), addr2(0);
	cin >> name >> size;
	PD* p(head->next), * q(NULL);
	int Error(512);

	while (p != NULL) {
		addr1 += (p->m_size + 1);
		if (p->m_flag == 0) {
			if (p->m_size > size) {
				if (p->m_size - size < Error) {
					Error = p->m_size - size;
					q = p;
					addr2 = addr1 - size - 1;
					p = p->next;
				}
				else p = p->next;
			}
			else if (p->m_size == size) {
				q = p;
				addr2 = addr1 - size - 1;
				Error = 0;
				break;
			}
			else p = p->next;
		}
		else p = p->next;
	}
	if (Error == 512)cout << "分配失败" << endl;
	else {
		if (Error == 0)q->m_flag = true;
		else {
			q->m_size -= (size + 1);
			PD* temp = new PD(q->next, 1, size);
			q->next = temp;
		}
		PCB temp(name, size, addr2);
		m_list.push_back(temp);
	}
}

//最坏
void Manage::worst() {
	cout << "输入进程名和大小:";
	string name; int size, addr1(0), addr2(0);
	cin >> name >> size;
	PD* p(head->next), * q(NULL);
	int Error(0);
	while (p != nullptr) {
		addr1 += (p->m_size + 1);
		if (p->m_flag == false) {
			if (p->m_size >= size) {
				if (p->m_size - size >= Error) {
					Error = p->m_size - size;
					q = p;
					addr2 = addr1 - size - 1;
					p = p->next;
				}
				else p = p->next;
			}
			else p = p->next;
		}
		else p = p->next;
	}
	if (Error == 0)cout << "分配失败" << endl;
	else {
		q->m_size -= (size + 1);
		PD* temp = new PD(q->next, 1, size);
		q->next = temp;
		PCB temp1(name, size, addr2);
		m_list.push_back(temp1);
	}
}

void Manage::release()
{
	string name;
	cout << "请输入回收的进程名：";
	cin >> name;

	//查找m_list中是否存在该进程
	vector<PCB>::iterator it = m_list.begin();
	while (it != m_list.end())
	{
		if ((*it).m_name == name) break;
		else it++;
	}
	//该进程不存在
	if (it == m_list.end())
	{
		cout << "该进程不存在！" << endl;
		return;
	}
	//进程存在
	else
	{
		int addr = 0;
		PD* p(head->next);
		while (p != NULL)
		{
			if ((*it).m_begin == addr)break;
			addr += (p->m_size + 1);
			p = p->next;
		}
		if (p == NULL)
			cout << "未在内存中找到该进程" << endl;
		else
		{
			p->m_flag = 0;//该内存块状态置0
			m_list.erase(it);//进程库中删除该进程

			//回收的内存块后面存在空闲区
			if (p->next != NULL && p->next->m_flag == 0)
			{
				p->m_size += (p->next->m_size);
				PD* temp(p->next);
				p->next = p->next->next;
				delete temp;
			}
			//回收的内存块前面存在空闲区
			PD* q(head->next);
			while (q != NULL)
			{
				if (q->next == p && q->m_flag == 0)
				{
					q->m_size += (p->m_size + 1);
					q->next = p->next;
					delete p;
					break;
				}
				q = q->next;
			}
		}
	}
}

void Manage::Display()//显示模块
{
	cout << "内存分区情况：" << endl;
	int i = 1;
	PD* p = head->next;
	int addr = 0;
	while (p != NULL)
	{
		//addr += p->m_size+1;
		cout << "第" << setw(2) << i << "块:" << "  起始地址：" << setw(3) << addr;
		if (p->m_flag == 0)
		{
			cout << "  未占用";
			//cout << "  大小：" << setw(3) << p->next->m_size << endl;
		}
		else
		{
			cout << "  已占用";
			//cout << "  大小：" << setw(3) << p->next->m_size+1 << endl;
		}
		cout << "  大小：" << setw(3) << p->m_size << endl;
		addr += p->m_size + 1;
		p = p->next;
		i++;
	}
}

int main()
{
	////初始化自由主存队列
	Manage m1;
	m1.head = new PD;
	PD* head1 = m1.head;
	head1->next = new PD;
	PD* p1 = head1->next;
	p1->m_flag = 0;
	p1->m_size = MAX_SIZE;

	cout << "-------------------动态分区式存贮区管理-------------------\n";
	cout << "1.首次    2.最佳    3.最坏\n";
	int choice, op;
	cout << "请选择放置策略：";
	cin >> choice;
	switch (choice)
	{
	case 1:
		while (1)
		{
			cout << "1.添加进程    2.结束进程    3.退出" << endl;
			cin >> op;
			if (op == 1)
			{
				m1.first_time();
				m1.Display();
			}
			else if (op == 2)
			{
				m1.release();
				m1.Display();
			}
			else if (op == 3)
			{
				break;
			}
			else
			{
				cout << "输入错误，请重新选择！" << endl;
			}
		}
		break;
	case 2:
		while (1)
		{
			cout << "1.添加进程    2.结束进程    3.退出" << endl;
			cin >> op;
			if (op == 1)
			{
				m1.best();
				m1.Display();
			}
			else if (op == 2)
			{
				m1.release();
				m1.Display();
			}
			else if (op == 3)
			{
				break;
			}
			else
			{
				cout << "输入错误，请重新选择！" << endl;
			}
		}
		break;
	case 3:
		while (1)
		{
			cout << "1.添加进程    2.结束进程    3.退出" << endl;
			cin >> op;
			if (op == 1)
			{
				m1.worst();
				m1.Display();
			}
			else if (op == 2)
			{
				m1.release();
				m1.Display();
			}
			else if (op == 3)
			{
				break;
			}
			else
			{
				cout << "输入错误，请重新选择！" << endl;
			}
		}
		break;
	}

	return 0;
	system("pause");
}