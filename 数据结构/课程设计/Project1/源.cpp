#include<iostream>
#include<set>
#include<ctime>
#include<cstdlib>
#include<windows.h>
using namespace std;
struct link
{
	int data = -1;
	link* next = NULL;
};
link* head, *head1;
bool iscs(link *node1, link*node2)
{
	bool result = 0;
	set<link*> lis1, lis;
	link* temp = node1;
	int lastsize = 0, lastsize1 = 0;
	while (temp != NULL)
	{
		lastsize = lis1.size();
		lis1.insert(temp);
		if (lastsize == lis1.size())
		{
			break;
		}
		temp = temp->next;
	}
	temp = node2;
	while (temp != NULL)
	{
		lastsize = lis1.size();
		lastsize1 = lis.size();
		lis1.insert(temp);
		lis.insert(temp);
		if (lastsize1 == lis.size())
		{
			system("cls");
			cout << "���������ཻ��";
			return 0;
		}
		if (lastsize == lis1.size())
		{
			system("cls");
			cout << "���������ཻ��";
			return  1;
		}

		temp = temp->next;
	}
	return 0;
}
link* dellp(link* start, link* end)
{
	link* temp = head1;
	while (temp->next != start)
	{
		temp = temp->next;
	}
	temp->next = NULL;
	end->next = head1;
	temp = head;
	int  count1 = 0;
	while (temp != NULL)
	{
		count1++;
		temp = temp->next;
	}
	temp = head;
	for (int i = 0; i < count1 / 2; i++)
	{
		temp = temp->next;
	}
	cout << "��ԭ���м���Ϊ" << temp->data << "���ַΪ" << temp << endl;
	iscs(head,head1);
	system("pause");
	system("cls");
	return temp;
}
void flp()
{
	link* fastpistor = head, *slowpistor = head, *start, *end;
	bool islp = 0;
	do
	{
		if (fastpistor->next == NULL || fastpistor->next->next == NULL)
		{
			break;
		}
		fastpistor = fastpistor->next->next;
		slowpistor = slowpistor->next;
		if (fastpistor == slowpistor)
		{
			islp = 1;
			break;
		}
	} while (slowpistor != NULL && fastpistor != NULL);
	set<link*> getlink;
	int lastsize = -1;
	slowpistor = head;
	while (slowpistor != NULL)
	{
		bool stop = 1;
		lastsize = getlink.size();
		getlink.insert(slowpistor);
		if (getlink.size() == lastsize)
		{
			break;
		}
		slowpistor = slowpistor->next;
	}
	start = slowpistor;
	end = head;
	bool isfirst = 1;
	while (end->next != start || isfirst)
	{
		if (end->next == start)
		{
			isfirst = 0;
		}
		end = end->next;
	}
	if (islp)
	{
		cout << "����ֹλ��Ϊ��" << endl;
		cout << "���ַΪ" << start << endl;
		cout << "ֹ��ַΪ" << end << endl;
		system("pause");
		system("cls");
		dellp(start,end);
	}
	else
	{
		cout << "�޻�" << endl;
	}
	
}
link* findl(int i)
{
	link* currentLink = head;
	while (currentLink!=NULL)
	{
		if (currentLink->data == i)
		{
			return currentLink;
		}
		currentLink = currentLink->next;
	}



}
void makelp(int m, int n)
{
	link  *loc = findl(m), *loc1 =findl(n),*temp = head;
	while (temp->next != NULL) 
	{
		temp = temp->next;
	}
	temp->next = loc;
	head1 = loc1->next;
	loc1->next = loc;
	
	cout << "Done!!!" << endl;
	system("pause");
	cout << "Ѱ��ѭ����ʼ��..." << endl;
	Sleep(3000);
	flp();
}
int main()
{
	head = new link;
	int m, n;
	cout << "��ʼ������:";
	head->data = 0;
	link* currentLink = head;
	srand(time(0));
	for (int i = 0; i < 15; i++)
	{
		int temp = rand()%20;
		if (temp < 0)
		{
			break;
		}
		link* l = new link;
		l->data = temp;
		currentLink->next = l;
		currentLink = currentLink->next;
	}
	currentLink = head;
	while (currentLink!=NULL)
	{
		cout << currentLink->data << " ";
		currentLink = currentLink->next;
	}
	cout << endl;
	system("pause");
	cout << "����m" << endl;
	cin >> m;
	cout << "����n" << endl;
	cin >> n;
	makelp(m,n);
	system("cls");
	system("pause");
}