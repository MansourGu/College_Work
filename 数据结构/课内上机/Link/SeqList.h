#pragma once
#include "BaseList.h"
#include<iostream>
#include <afxwin.h>  
using namespace std;
class SeqList :
	public BaseList
{
protected:
	int * data;
	int maxsize;
	int end;
public:
	SeqList();
	~SeqList();
	void Insert(int x,int y);
	void Delete(int x);
	CString Show();
	int Locate(int x);
	void Add(int x);
	bool IsEmpty();
	void Reverse();

};

