#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct Student //����һ���ṹ�� ���һ���˵��������Ա𣬵绰����ַ���������䡣
{
	int ID;
	string name;
	string sex;
	string phone_number;
	string address;
	string e_mail;
};
vector<Student>s;//��������ӵ���ϵ�� ����student ���͵�������
void display(Student &a);//��ʾһ���˵���Ϣ
void menu();//��ʾ�˵�
void paixu();//��ͨѶ¼����ĸ����
void get_information(Student &a)//��ȡ��ϵ�˵ĸ�����Ϣ
{
	cout << "������Ҫ�����ϵ�˵���Ϣ��" << endl;
	cout << "���� ��";
	cin >> a.name;
	if ((a.name[0]) >= 97 &&a.name[0] <= 122)//��Сдͳһת��Ϊ��д ��������
	{
		a.name[0] -= 32;
	}
	for (int i = 0; i < s.size(); i++)
	{
		if (a.name == s[i].name)//������ϵ����ǰ�Ƿ�¼��
		{
			cout << "����ϵ���Ѵ���";
			display(s[i]);
			system("pause");
			menu();
		}
	}
	cout << "�Ա� �� ";
	cin >> a.sex;
	cout << "�绰���� ��";
	cin >> a.phone_number;
	cout << "סַ : ";
	cin >> a.address;
	cout << "�������� �� ";
	cin >> a.e_mail;
	a.ID = s.size() + 1;
}

void add()//�����ϵ��
{
	Student s1;//�½��ṹ����� 
	get_information(s1);//��ȡ��Ϣ
	s.push_back(s1);//������ϵ�˷���ͨѶ¼
	paixu();//��ͨѶ��������
}
void delete_relitives(int i)//ɾ����ϵ��
{
	s.erase(s.begin() + (s[i].ID - 1));//ɾ��ָ��λ�õ���ϵ��
	for (int m = s[i].ID - 2; m < s.size(); m++)//��ɾ������ϵ�˺������ ��ż�һ
	{
		s[m].ID-=1;
	}
	cout << "����ϵ����ɾ��";
}
void display(Student &a)//��ʾĳ����ϵ�˵���Ϣ
{
	cout << a.ID << "�� ������" << a.name << endl;
	cout << "  �Ա� ��" << a.sex << endl;
	cout << "  �绰���� ��" << a.phone_number << endl;
	cout << "  סַ ��" << a.address << endl;
	cout << "  �������� ��" << a.e_mail << endl;
}
void Search()//����
{
	cout << "��ѡ����ҷ�ʽ��" << endl;
	cout << "�ٰ������ֲ���" << endl;
	cout << "�ڰ��յ绰�������" << endl;
	int tem;
	cin >> tem;
	if (tem == 1)//�жϲ��ҷ�ʽ
	{
	mark1:
		string name;
		cout << "������Ҫ���ҵ����� ��" << endl;
		cin >> name;
		if (name[0] >= 97 && name[0] <= 122)//���������������ĸ��д ������ͨѶ¼ͳһ
		{
			name[0] -= 32;
		}
		for (int i = 0; i < s.size(); i++)
		{
			if (name == s[i].name)//������ͬ����
			{
				display(s[i]);
				system("pause");
				cout << "�Ƿ�Ҫɾ������ϵ�ˣ� Y/N" << endl;
				char judge;
				cin >> judge;
				if (judge == 'Y')
				{
					delete_relitives(i);
					system("pause");
				}
				return;
			}
			cout << "���޴��� ���������룺";
			system("pause");
			goto mark1;
		}
	}
	if (tem == 2)
	{
	mark2:
		string number;
		cout << "������Ҫ�����˵ĵ绰���� ��" << endl;
		cin >> number;
		for (int i = 0; i < s.size(); i++)
		{
			if (number == s[i].phone_number)
			{
				display(s[i]);
				system("pause");
				cout << "�Ƿ�Ҫɾ������ϵ�ˣ� Y/N" << endl;
				char judge;
				cin >> judge;
				if (judge == 'Y')
				{
					delete_relitives(i);
					system("pause");
				}
				return;
			}
			cout << "���޴��� ���������룺";
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
			if ((s[j].name[0] < (s[i].name)[0]))//����ÿ����ϵ�˵���������ĸ����
			{
				Student tem;//����
				tem = s[j];
				s[j] = s[i];
				s[i] = tem;
				int tem_id1;//��Ž���
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
	cout << "*                            ��ӭʹ��ͨѶ¼                                  *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                          ������  ��������                  *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*                                                                            *" << endl;
	cout << "*          ��ѡ���� �ٲ鿴������ϵ��                                       *" << endl;
	cout << "*                     �ڲ�����ϵ��                                           *" << endl;
	cout << "*                     �������ϵ��                                           *" << endl;
	cout << "*                     ���˳�                                                 *" << endl;
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
		cout << "�� " << s.size() << "����¼" << endl;
		cout << "���س����������˵�";
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
