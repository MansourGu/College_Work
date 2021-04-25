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
	}//�ж�ջ�Ƿ�Ϊ��
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
	}//�ж�ջ�Ƿ�����
	bool Get_Top(Vertix &x)//��ȡջ��Ԫ��ֵ
	{
		if (IsEmpty())
		{
			return false;
		}
		x = Element[Top];
		return true;
	}
	bool Pop(Vertix &x)//��ջ
	{
		if (IsEmpty())
		{
			return false;
		}
		x = Element[Top];
		Top--;
		return true;
	}
	bool Push(const Vertix &x)//ѹջ
	{
		if (IsFull())
		{
			return false;
		}
		Top++;
		Element[Top] = x;
	}
private:
	Vertix * Element; // ջԪ�ش������
	int Top;          // ջ��ָ��
	int MaxSize;      // ջ���������

};