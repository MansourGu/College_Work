#pragma once
#include "BaseList.h"
#include<iostream>
using namespace std;
struct LinkNode
{
	int data;
	LinkNode* link;
	LinkNode(LinkNode*ptr = NULL)
	{
		link = ptr;
	}
	LinkNode(int item, LinkNode*ptr = NULL)
	{
		data = item;
		link = ptr;
	}
};
class LinkList :
	public BaseList
{
protected:
	LinkNode*First;
	LinkNode*Last;
public:
	LinkList();
	~LinkList();
	void Insert(int x,int y);
	void Delete(int x);
	bool IsEmpty();
	CString Show();
	void Add(int x);
	void Reverse();

};

