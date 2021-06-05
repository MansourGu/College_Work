#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
using namespace std;
#define MAX_SIZE 512//��������С
class PD//����������

{
public:
	int m_flag;//��־
	int m_size;//������С
	PD* next;//��һ���ַ
public:
	PD(PD* n = NULL, int flag = 0, int size = 0)//���ƹ��캯��
	{
		m_flag = flag;
		m_size = size;
		next = n;
	}
	friend class Manage;
};

class PCB//���̽��,��ŷ���ɹ��Ľ���
{
private:
	string m_name;	//������
	int m_size;	//���̴�С
	int m_begin;	//������ʼ��ַ
public:
	PCB(string n = "��", int s = 0, int b = 0)//���ƹ��캯��
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
	PD* head;//ͷ�ڵ�
	vector<PCB>m_list;
public:
	Manage(PD* p = NULL)
	{
		head = p;
	}

	void first_time();//�״���Ӧ�㷨
	void best();//�����Ӧ�㷨
	void worst();//���Ӧ�㷨

	void release();//����

	void Display();//��ʾ

	friend class PCB;
	friend class PD;
};

//�״���Ӧ�㷨
void Manage::first_time()
{
	string name;
	int size, addr = 0;
	cout << "������������ʹ�С��";
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
	if (p == NULL)cout << "����ʧ�ܣ�" << endl;
	else
	{
		PCB temp(name, size, addr);
		m_list.push_back(temp);
	}
}

//���
void Manage::best()
{
	cout << "����������ʹ�С:";
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
	if (Error == 512)cout << "����ʧ��" << endl;
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

//�
void Manage::worst() {
	cout << "����������ʹ�С:";
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
	if (Error == 0)cout << "����ʧ��" << endl;
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
	cout << "��������յĽ�������";
	cin >> name;

	//����m_list���Ƿ���ڸý���
	vector<PCB>::iterator it = m_list.begin();
	while (it != m_list.end())
	{
		if ((*it).m_name == name) break;
		else it++;
	}
	//�ý��̲�����
	if (it == m_list.end())
	{
		cout << "�ý��̲����ڣ�" << endl;
		return;
	}
	//���̴���
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
			cout << "δ���ڴ����ҵ��ý���" << endl;
		else
		{
			p->m_flag = 0;//���ڴ��״̬��0
			m_list.erase(it);//���̿���ɾ���ý���

			//���յ��ڴ�������ڿ�����
			if (p->next != NULL && p->next->m_flag == 0)
			{
				p->m_size += (p->next->m_size);
				PD* temp(p->next);
				p->next = p->next->next;
				delete temp;
			}
			//���յ��ڴ��ǰ����ڿ�����
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

void Manage::Display()//��ʾģ��
{
	cout << "�ڴ���������" << endl;
	int i = 1;
	PD* p = head->next;
	int addr = 0;
	while (p != NULL)
	{
		//addr += p->m_size+1;
		cout << "��" << setw(2) << i << "��:" << "  ��ʼ��ַ��" << setw(3) << addr;
		if (p->m_flag == 0)
		{
			cout << "  δռ��";
			//cout << "  ��С��" << setw(3) << p->next->m_size << endl;
		}
		else
		{
			cout << "  ��ռ��";
			//cout << "  ��С��" << setw(3) << p->next->m_size+1 << endl;
		}
		cout << "  ��С��" << setw(3) << p->m_size << endl;
		addr += p->m_size + 1;
		p = p->next;
		i++;
	}
}

int main()
{
	////��ʼ�������������
	Manage m1;
	m1.head = new PD;
	PD* head1 = m1.head;
	head1->next = new PD;
	PD* p1 = head1->next;
	p1->m_flag = 0;
	p1->m_size = MAX_SIZE;

	cout << "-------------------��̬����ʽ����������-------------------\n";
	cout << "1.�״�    2.���    3.�\n";
	int choice, op;
	cout << "��ѡ����ò��ԣ�";
	cin >> choice;
	switch (choice)
	{
	case 1:
		while (1)
		{
			cout << "1.��ӽ���    2.��������    3.�˳�" << endl;
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
				cout << "�������������ѡ��" << endl;
			}
		}
		break;
	case 2:
		while (1)
		{
			cout << "1.��ӽ���    2.��������    3.�˳�" << endl;
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
				cout << "�������������ѡ��" << endl;
			}
		}
		break;
	case 3:
		while (1)
		{
			cout << "1.��ӽ���    2.��������    3.�˳�" << endl;
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
				cout << "�������������ѡ��" << endl;
			}
		}
		break;
	}

	return 0;
	system("pause");
}