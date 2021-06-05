#include<iostream>
#include<string>
#include<queue>
#include<fstream>
#include<iomanip>
using namespace std;
#define max 0x3f3f3f3f

struct pcb
{
	string name; //����
	int need;    //����ʱ��
	int turn;    //����ʱ��
	int arrive;  //����ʱ��
	float xyb;   //��Ӧ��
	int zz;      //��תʱ��
	float xzz;   //��Ȩ��תʱ��
	pcb *next;
};
pcb *pcb1 = new pcb;

int clock1 = 0;  //ʱ��1
int clock2 = 0;  //ʱ��2
int azz = 0;     //ƽ����תʱ��
float axzz = 0;    //ƽ����Ȩ��תʱ��


void init()
{
	ifstream ifile;
	ifile.open("��ҵ����.txt");

	pcb1->next = NULL;
	pcb *t = new pcb;
	t->next = NULL;
	ifile >> t->name >> t->arrive >> t->need;
	//  t->xyb=t->arrive/(t->need*1.0)+1;
	t->xyb = 1;
	t->next = pcb1->next;
	pcb1 = t;
	for (int i = 0; i < 9; i++)
	{
		pcb *s = new pcb;
		s->next = NULL;
		ifile >> s->name >> s->arrive >> s->need;
		s->xyb = max;
		if (i == 0) s->xyb = 1;
		pcb *t = pcb1;
		while (t->next != NULL) t = t->next;
		s->next = t->next;
		t->next = s;
	}

	ifile.close();
}

void prioritygo()
{
	clock1 = 0;
	clock2 = 0;
	azz = 0;
	axzz = 0;
	cout << " ����     ����ʱ��   ��תʱ��    ��Ȩ��תʱ�� " << endl;
	bool non;
	for (int i = 0; i < 10; i++)
	{
		non = false;
		pcb *p = new pcb;
		pcb *q = new pcb;
		p = pcb1;
		q->need = max;
		q->next = NULL;
		while (p != NULL)
		{
			if (clock1 <= clock2 && p->arrive <= clock1)
			{
				if (p->need != 0 && p->need <= q->need)
				{
					q = p;
					//   cout<<endl<<q->name<<" "<<q->arrive<<" "<<q->need<<"  "<<clock1<<"  "<<clock2<<endl;
					non = true;
				}
			}
			if (clock1 > clock2&&p->arrive <= clock2)
			{
				if (p->need != 0 && p->need <= q->need)
				{
					q = p;
					//   cout<<endl<<q->name<<" "<<q->arrive<<" "<<q->need<<"  "<<clock1<<"  "<<clock2<<endl;
					non = true;
				}
			}
			p = p->next;
		}

		if (!non)
		{
			q->arrive = max;
			q->next = NULL;
			p = pcb1;
			while (p != NULL)
			{
				if (p->need != 0 && p->arrive <= q->arrive)
				{
					q = p;
					//         cout<<endl<<q->name<<" "<<q->arrive<<" "<<q->need<<"  "<<clock1<<"  "<<clock2<<endl;
				}

				p = p->next;
			}
		}
		if (clock1 <= clock2)
		{
			if (i == 0) clock1 = q->arrive;
			if (!non) clock1 = q->arrive;
			clock1 += q->need;
			q->turn = clock1;
			q->zz = q->turn - q->arrive;      azz += q->zz;
			q->xzz = q->zz / (q->need*1.0);   axzz += q->xzz;
			q->need = 0;
			cout << setw(5) << q->name << setw(10) << q->turn << setw(10) << q->zz << setw(15) << q->xzz << endl;
		}
		else
		{
			if (i == 1)
			{
				pcb *k = pcb1;
				k = pcb1->next;
				clock2 = k->arrive;
				clock2 += k->need;
				k->turn = clock2;
				k->zz = k->turn - k->arrive;    azz += k->zz;
				k->xzz = k->zz / (k->need*1.0); axzz += k->xzz;
				k->need = 0;
				cout << setw(5) << k->name << setw(10) << k->turn << setw(10) << k->zz << setw(15) << k->xzz << endl;
				continue;
			}
			if (!non) clock2 = q->arrive;
			clock2 += q->need;
			q->turn = clock2;
			q->zz = q->turn - q->arrive;      azz += q->zz;
			q->xzz = q->zz / (q->need*1.0);   axzz += q->xzz;
			q->need = 0;
			cout << setw(5) << q->name << setw(10) << q->turn << setw(10) << q->zz << setw(15) << q->xzz << endl;
		}
	}
	cout << "ƽ����תʱ�䣺     " << azz / 10.0 << endl;
	cout << "ƽ����Ȩ��תʱ�䣺 " << axzz / 10.0 << endl;
}

void firstgo()
{
	clock1 = 0;
	clock2 = 0;
	azz = 0;
	axzz = 0;
	cout << " ����     ����ʱ��   ��תʱ��    ��Ȩ��תʱ�� " << endl;
	bool non;
	for (int i = 0; i < 10; i++)
	{
		non = false;
		pcb *p = new pcb;
		pcb *q = new pcb;
		p = pcb1;
		q->arrive = max;
		q->next = NULL;
		while (p != NULL)
		{
			if (p->need != 0 && p->arrive <= q->arrive && (p->arrive <= clock1 || p->arrive <= clock2))
			{
				q = p;
				non = true;
			}
			p = p->next;
		}
		if (!non)
		{
			q->arrive = max;
			q->next = NULL;
			p = pcb1;
			while (p != NULL)
			{
				if (p->need != 0 && p->arrive <= q->arrive)
				{
					q = p;
				}

				p = p->next;
			}
		}
		if (clock1 <= clock2)
		{
			if (i == 0) clock1 = q->arrive;
			if (!non) clock1 = q->arrive;
			clock1 += q->need;
			q->turn = clock1;
			q->zz = q->turn - q->arrive;      azz += q->zz;
			q->xzz = q->zz / (q->need*1.0);   axzz += q->xzz;
			q->need = 0;
			cout << setw(5) << q->name << setw(10) << q->turn << setw(10) << q->zz << setw(15) << q->xzz << endl;
		}
		else
		{
			if (i == 1)
			{
				pcb *k = pcb1;
				k = pcb1->next;
				clock2 = k->arrive;
				clock2 += k->need;
				k->turn = clock2;
				k->zz = k->turn - k->arrive;    azz += k->zz;
				k->xzz = k->zz / (k->need*1.0); axzz += k->xzz;
				k->need = 0;
				cout << setw(5) << k->name << setw(10) << k->turn << setw(10) << k->zz << setw(15) << k->xzz << endl;
				continue;
			}
			if (!non) clock2 = q->arrive;
			clock2 += q->need;
			q->turn = clock2;
			q->zz = q->turn - q->arrive;      azz += q->zz;
			q->xzz = q->zz / (q->need*1.0);   axzz += q->xzz;
			q->need = 0;
			cout << setw(5) << q->name << setw(10) << q->turn << setw(10) << q->zz << setw(15) << q->xzz << endl;
		}
	}
	cout << "ƽ����תʱ�䣺     " << azz / 10.0 << endl;
	cout << "ƽ����Ȩ��תʱ�䣺 " << axzz / 10.0 << endl;
}

void percentgo()
{
	clock1 = 0;
	clock2 = 0;
	azz = 0;
	axzz = 0;
	cout << " ����     ����ʱ��   ��תʱ��    ��Ȩ��תʱ��   ��Ӧ��" << endl;
	bool non;
	for (int i = 0; i < 10; i++)
	{
		non = false;
		pcb *p = new pcb;
		pcb *q = new pcb;
		p = pcb1;
		q->xyb = -1;
		q->next = NULL;
		while (p != NULL)
		{
			if (clock1 <= clock2 && p->arrive <= clock1)
			{
				pcb *t = pcb1;
				while (t != NULL)
				{
					t->xyb = (clock1 - t->arrive) / (t->need*1.0) + 1;
					if (i == 0) t->xyb = 1;
					t = t->next;
				}
				if (p->need != 0 && p->xyb >= q->xyb)
				{
					q = p;
					//  cout<<endl<<q->name<<" "<<q->arrive<<" "<<q->need<<"  "<<clock1<<"  "<<clock2<<endl;
					non = true;
				}
			}

			if (clock1 > clock2&&p->arrive <= clock2)
			{
				pcb *t = pcb1;
				while (t != NULL)
				{
					t->xyb = (clock2 - t->arrive) / (t->need*1.0) + 1;
					if (i == 1) t->xyb = 1;
					t = t->next;
				}
				if (p->need != 0 && p->xyb >= q->xyb)
				{
					q = p;
					//  cout<<endl<<q->name<<" "<<q->arrive<<" "<<q->need<<"  "<<clock1<<"  "<<clock2<<endl;
					non = true;
				}
			}
			p = p->next;
		}
		if (!non)
		{
			q->arrive = max;
			q->next = NULL;
			p = pcb1;
			while (p != NULL)
			{
				if (p->need != 0 && p->arrive <= q->arrive)
				{
					q = p;
					// cout<<endl<<q->name<<" "<<q->arrive<<" "<<q->need<<"  "<<clock1<<"  "<<clock2<<endl;
				}

				p = p->next;
			}
		}
		if (clock1 <= clock2)
		{
			if (i == 0) clock1 = q->arrive;
			if (!non) clock1 = q->arrive;
			clock1 += q->need;
			q->turn = clock1;
			q->zz = q->turn - q->arrive;      azz += q->zz;
			q->xzz = q->zz / (q->need*1.0);   axzz += q->xzz;
			q->need = 0;
			cout << setw(5) << q->name << setw(10) << q->turn << setw(10) << q->zz << setw(15) << q->xzz << setw(13) << q->xyb << endl;

		}
		else
		{
			if (i == 1)
			{
				pcb *k = pcb1;
				k = pcb1->next;
				clock2 = k->arrive;
				clock2 += k->need;
				k->turn = clock2;
				k->zz = k->turn - k->arrive;    azz += k->zz;
				k->xzz = k->zz / (k->need*1.0); axzz += k->xzz;
				k->need = 0;
				cout << setw(5) << k->name << setw(10) << k->turn << setw(10) << k->zz << setw(15) << k->xzz << setw(13) << k->xyb << endl;

				continue;
			}
			if (!non) clock2 = q->arrive;
			clock2 += q->need;
			q->turn = clock2;
			q->zz = q->turn - q->arrive;      azz += q->zz;
			q->xzz = q->zz / (q->need*1.0);   axzz += q->xzz;
			q->need = 0;
			cout << setw(5) << q->name << setw(10) << q->turn << setw(10) << q->zz << setw(15) << q->xzz << setw(13) << q->xyb << endl;
		}
	}
	cout << "ƽ����תʱ�䣺     " << azz / 10.0 << endl;
	cout << "ƽ����Ȩ��תʱ�䣺 " << axzz / 10.0 << endl;
}

void p()
{
	cout << " ����   ����ʱ��   ����ʱ��" << endl;
	pcb *p = pcb1;
	while (p != NULL)
	{
		cout << setw(5) << p->name << setw(10) << p->arrive << setw(10) << p->need << endl;
		p = p->next;
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	cout << "���н��" << endl;
	init();
	p();
	cout << "�����ȷ����㷨��" << endl;
	firstgo();
	cout << endl;

	init();
	cout << "�̽��������㷨��" << endl;
	prioritygo();
	cout << endl;

	init();
	cout << "��Ӧ�������㷨��" << endl;
	percentgo();
	cout << endl;
	system("pause");
	return 0;

}