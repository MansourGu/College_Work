#include"Graph.cpp"
#pragma once
using namespace std;
#define UFS_Size 20;
class UFSet
{
public:
	UFSet(int sz)
	{
		UFSet_Size = sz;
		Parent = new int[UFSet_Size];
		for (int i = 0; i < UFSet_Size; i++)
		{
			Parent[i] = -1;                    //初始化父指针数组
		}
	}
	~UFSet()
	{
		delete[]Parent;
	}
	int Find(int x) //返回包含元素x的根
	{
		while (Parent[x]>=0)
		{
			x = Parent[x];   //沿着x的父指针寻x
		}
		return x;
	}
	void Union_UFS(int Root1, int Root2)//将两个集合的做合并
	{	
		if (Root1 == Root2)
		{
			cout << "两个元素已在同一个根下，不做合并！";
			return;
		}
		Parent[Root1] += Parent[Root2];
		Parent[Root2] = Root1;             //将Root2 指向Root1
	}

private:

	int UFSet_Size;
	int * Parent;
};