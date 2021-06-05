#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int  Time_Slice = 7;//ʱ��Ƭ
struct PCB
{
	string name;
	int need = 0;
	int turn = 0;
	PCB* next = NULL;
	PCB(string na, int n, int t, PCB* nxt)//���ƹ��캯��
	{
		name = na;
		need = n;
		turn = t;
		next = nxt;
	}
	PCB(PCB * p)
	{
		name = p->name;
		need = p->need;
		turn = p->turn;
		next = p->next;
	}
	PCB() {};//Ĭ�Ϲ��캯��
};
PCB* RQ1 = new PCB;
PCB* RQ2 = new PCB;
PCB* Finish = new PCB;
int clock = 0;// ʱ�ӳ�ʼ��
PCB* Construt_Queue(PCB* Pre , string s)
{
	string name;
	int need = 0;
	int turn = 0;
	string partition = "";
	int count = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ' && count == 0)
		{
			name = partition;
			partition = "";
			count++;
			continue;
		}
		if (s[i] == ' ' && count == 1)
		{
			need = atoi(partition.c_str());
			partition = "";
			count++;
			continue;
		}
		if (i == s.size()-1 && count == 2)
		{
			partition += s[i];
			turn = atoi(partition.c_str());
			partition = "";
			count++;
			continue;
		}
		partition += s[i];
	}
	PCB *temp = new PCB(name,need,turn,NULL);
	Pre->next = temp;
	return temp;
}
void Read_Process(int judge)
{
	fstream fin;
	if (judge == 1)
	{
		fin.open("RQ1.txt");
		string temp;
		PCB* head = RQ1;
		while (getline(fin, temp))
		{
			head = Construt_Queue(head, temp);
		}
	}
	else
	{
		fin.open("RQ2.txt");
		string temp;
		PCB* head = RQ2;
		while (getline(fin, temp))
		{
			head = Construt_Queue(head, temp);
		}
	}
}
void Delete_Process(PCB * head, PCB *target)
{
	PCB * current = head;
	while (current->next!=NULL)
	{
		if (current->next == target)
		{
			current->next = target->next;//���ó���Ӷ�����ɾ��
			target->next = Finish->next;
			Finish->next = target;
			return;
		}
		current = current->next;
	}
}
void Swap_PCB(PCB* a, PCB * b)
{
	PCB * temp = new PCB(a);
	a->name = b->name;
	a->need = b->need;
	a->turn = b->turn;
	b->name = temp->name;
	b->need = temp->need;
	b->turn = temp->turn;
}
void Sort_Queue(PCB *head)
{
	PCB* current = head->next;
	
	while (current->next!= NULL)
	{
		PCB* move = current->next;
		while (move)
		{
			if (move->need < current->need)
			{
				Swap_PCB(move, current);
			}
			move = move->next;
		}
		current = current->next;
	}
}
int Circle(PCB * P)
{
	PCB * head = P;//����ͷ
	PCB * current = head;
	
	while (head->next)
	{
		current = head->next;
		while (current)
		{
			if (current->need > Time_Slice)
			{
				clock += Time_Slice;
				current->need -= Time_Slice;
				current = current->next;
			}
			else
			{
				clock += current->need;
				current->need = 0;
				current->turn += clock;
				PCB * del = current;
				current = current->next;
				Delete_Process(RQ1, del);
			}
		}
	}
	return clock;
}
int Short_First(PCB* P)
{
	while (P->next)
	{
		PCB * current = P->next;
		while (current->need > 0)
		{
			clock += current->need;
			current->need = 0;
			current->turn += clock;
		}
		Delete_Process(RQ2, current);
	}
	return clock;
}
int main()
{
	Read_Process(1);
	Read_Process(2);
	Sort_Queue(RQ2);
	clock = Circle(RQ1);
	clock = Short_First(RQ2);
	PCB* cur = Finish->next;
	float result = 0;
	while (cur!= nullptr)
	{
		cout << cur->name <<"  " <<cur->turn <<endl;
		result += cur->turn;
		cur = cur->next;
	}
	cout <<"ƽ����תʱ��Ϊ��"<< result / 10<<endl;
	system("pause");
	return 0;
}