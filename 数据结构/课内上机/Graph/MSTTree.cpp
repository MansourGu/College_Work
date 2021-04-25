#include"Graph.cpp"
#pragma once
using namespace std;
struct MSTEdgeNode
{
	int head;
	int tail;
	int weight;
	MSTEdgeNode() :head(-1), tail(-1),weight(0) {};
	bool operator< (const MSTEdgeNode& e) //����С�ں�
	{
		if (this->weight < e.weight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator<= (const MSTEdgeNode& e) //����С�ڵ��ں�
	{
		if (this->weight <= e.weight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator> (const MSTEdgeNode& e)//���ش��ں�
	{
		if (this->weight > e.weight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	MSTEdgeNode& operator=(const MSTEdgeNode &e)//���ظ�ֵ�����
	{
		if (this != &e)
		{
			this->head = e.head;
			this->tail = e.tail;
			this->weight = e.weight;
		}
		return *this;
	}
	friend	ostream& operator<<(ostream& output, MSTEdgeNode e)//������������
	{
		output << e.weight;
		return output;
	}
	friend istream& operator>>(istream& input, MSTEdgeNode e)//�������������
	{
		input >> e.weight;
		return input;
	}
};
class MinSpanTree
{
	
public:
	MinSpanTree(int sz)
	{
		Maxsize = sz;
		Currentsize = 0;
		EdgeValue = new MSTEdgeNode[sz];
	}
	int Insert(MSTEdgeNode& item);
	~MinSpanTree() {};

private:
	MSTEdgeNode*EdgeValue;
	int Maxsize, Currentsize;//���Ԫ�ظ����͵�ǰ����
};