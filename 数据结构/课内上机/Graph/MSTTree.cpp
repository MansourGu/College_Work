#include"Graph.cpp"
#pragma once
using namespace std;
struct MSTEdgeNode
{
	int head;
	int tail;
	int weight;
	MSTEdgeNode() :head(-1), tail(-1),weight(0) {};
	bool operator< (const MSTEdgeNode& e) //重载小于号
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
	bool operator<= (const MSTEdgeNode& e) //重载小于等于号
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
	bool operator> (const MSTEdgeNode& e)//重载大于号
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
	MSTEdgeNode& operator=(const MSTEdgeNode &e)//重载赋值运算符
	{
		if (this != &e)
		{
			this->head = e.head;
			this->tail = e.tail;
			this->weight = e.weight;
		}
		return *this;
	}
	friend	ostream& operator<<(ostream& output, MSTEdgeNode e)//重载输出运算符
	{
		output << e.weight;
		return output;
	}
	friend istream& operator>>(istream& input, MSTEdgeNode e)//重载输入运算符
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
	int Maxsize, Currentsize;//最大元素个数和当前个数
};