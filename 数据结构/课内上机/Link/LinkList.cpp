#include "stdafx.h"
#include "LinkList.h"
#include<vector>

LinkList::LinkList()
{
	First = new LinkNode;
	Last = First;
}
LinkList::~LinkList()
{

}
void LinkList::Add(int x)
{
	if (IsEmpty())
	{
		LinkNode* temp = new LinkNode;
		temp->data = x;
		First->link = temp;
		Last = temp;
		return;
	}
	LinkNode* temp = new LinkNode;
	temp->data = x;
	temp->link = Last->link;
	Last->link = temp;
	Last = temp;
}
void  LinkList::Insert(int x,int y)
{
	if (First->link==NULL)
	{
		cout << "�������Ϊ�գ�" << endl;
	}
	LinkNode*current = First;
	while (current!=NULL)
	{
		if (current->data==y)
		{
			LinkNode* temp = new LinkNode;
			temp->data = x;
			temp->link = current->link;
			current->link = temp;
			AfxMessageBox("����ɹ���");
			return;
		}
		if (current->link == NULL)
		{
			AfxMessageBox("δ�ҵ���");
			return;
		}
		current = current->link;
	}


}
void  LinkList::Delete(int x)
{
	int count = 0;
	if (First->link == NULL)
	{
		cout << "�������Ϊ�գ�" << endl;
	}
	LinkNode*current = First;
	LinkNode*del;
	while (current != NULL)
	{
		if (current->link == NULL)
		{
			if (current->data == x)
			{
				del = current->link;
				current->link = del->link;
				delete del;
				AfxMessageBox("ɾ���ɹ���");
				count++;
			}
			if (count==0)
			{
				AfxMessageBox("δ�ҵ�ָ��Ԫ�أ�");
			}
			return;
		}
		if (current->link->data == x)
		{
		    del = current->link;
			current->link = del->link;
			delete del;
			count++;
			AfxMessageBox("ɾ���ɹ���");
			continue;
		}
		current = current->link;
	}
}
CString  LinkList::Show()
{
	if (First->link==NULL)
	{
		AfxMessageBox("����Ϊ�գ�");
		return"";
	}
	LinkNode*current = First->link;
	CString output = "";
	while (current!=NULL)
	{
		CString temp;
		temp.Format(_T("%d"), current->data);
		output += ( temp + "->");
		current = current->link;
	}
	return output.Left(output.GetLength()-2);
}
bool  LinkList::IsEmpty()
{
	if (First->link == NULL)
	{
		return true;
	}
	return false;
}
void LinkList::Reverse()
{
	if (First->link == NULL)
	{
		AfxMessageBox("����Ϊ�� �޷����棡");
		return;
	}
	vector<LinkNode*>address;
	LinkNode* current = First->link;
	while (current!=NULL)
	{
		address.push_back(current);
		current = current->link;
	}
	for (int i = address.size()-1; i > 0; i--)
	{
		address[i]->link = address[i - 1];
	}
	address[0]->link = NULL;
	Last = address[0];
	First->link = address[address.size() - 1];
}