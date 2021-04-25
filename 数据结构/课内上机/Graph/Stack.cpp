#include"Graph.cpp"
#pragma once
using namespace std;
#define MAX_SIZE 30;
class Stack
{
public:
	Stack()
	{
		Top = -1;
		MaxSize = MAX_SIZE;
	}
	~Stack()
	{
		delete[]Element;
	}
	bool IsEmpty()
	{
		if (Top == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}//判断栈是否为空
	bool IsFull()
	{
		if (Top == MaxSize-1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}//判断栈是否已满
	bool Get_Top(Vertix &x)//获取栈顶元素值
	{
		if (IsEmpty())
		{
			return false;
		}
		x = Element[Top];
		return true;
	}
	bool Pop(Vertix &x)//退栈
	{
		if (IsEmpty())
		{
			return false;
		}
		x = Element[Top];
		Top--;
		return true;
	}
	bool Push(const Vertix &x)//压栈
	{
		if (IsFull())
		{
			return false;
		}
		Top++;
		Element[Top] = x;
	}
private:
	Vertix * Element; // 栈元素存放数组
	int Top;          // 栈顶指针
	int MaxSize;      // 栈的最大容量

};