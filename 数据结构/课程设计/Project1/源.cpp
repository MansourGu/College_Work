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
			cout << "两个链表不相交！";
			return 0;
		}
		if (lastsize == lis1.size())
		{
			system("cls");
			cout << "两个链表相交！";
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
	cout << "还原后中间结点为" << temp->data << "其地址为" << temp << endl;
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
		cout << "环起止位置为：" << endl;
		cout << "起地址为" << start << endl;
		cout << "止地址为" << end << endl;
		system("pause");
		system("cls");
		dellp(start,end);
	}
	else
	{
		cout << "无环" << endl;
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
	cout << "寻找循环起始点..." << endl;
	Sleep(3000);
	flp();
}
int main()
{
	head = new link;
	int m, n;
	cout << "初始化链表:";
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
	cout << "输入m" << endl;
	cin >> m;
	cout << "输入n" << endl;
	cin >> n;
	makelp(m,n);
	system("cls");
	system("pause");
}