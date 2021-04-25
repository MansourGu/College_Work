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
			Parent[i] = -1;                    //��ʼ����ָ������
		}
	}
	~UFSet()
	{
		delete[]Parent;
	}
	int Find(int x) //���ذ���Ԫ��x�ĸ�
	{
		while (Parent[x]>=0)
		{
			x = Parent[x];   //����x�ĸ�ָ��Ѱx
		}
		return x;
	}
	void Union_UFS(int Root1, int Root2)//���������ϵ����ϲ�
	{	
		if (Root1 == Root2)
		{
			cout << "����Ԫ������ͬһ�����£������ϲ���";
			return;
		}
		Parent[Root1] += Parent[Root2];
		Parent[Root2] = Root1;             //��Root2 ָ��Root1
	}

private:

	int UFSet_Size;
	int * Parent;
};