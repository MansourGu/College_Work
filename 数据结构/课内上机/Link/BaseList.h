#pragma once
#include<cstring>
class BaseList
{
public:
	BaseList();
	~BaseList();
	virtual void Insert(int x,int y) = 0;
	virtual void Delete(int x) = 0;
	virtual CString Show() = 0;
	virtual void Add(int x) = 0;
	virtual bool IsEmpty() = 0;
	virtual void Reverse() = 0;
};

