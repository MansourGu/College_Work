#include<iostream>
#include<string>
#include<vector>
#pragma once
#define MAX_Vertix 10
#define MAX_Weight 9999
using namespace std;
struct  Vertix
{
	string Name; //节点名字
	int x; //节点横坐标
	int y;//节点纵坐标
	Vertix(string name) { Name = name; }
	Vertix() :Name(""), x(0),y(0){};
	bool operator==(const Vertix& v) //重载==运算符
	{
		if (this->Name == v.Name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	friend	ostream& operator<<(ostream& output, Vertix v)//重载输出运算符
	{
		output << v.Name;
		return output;
	}
	friend istream& operator>>(istream& input, Vertix v)//重载输入运算符
	{
		input >> v.Name;
		return input;
	}
	Vertix& operator=(const Vertix &v)//重载赋值运算符
	{
		if (this != &v )
		{
			this->Name = v.Name;
			this->x = v.x;
			this->y = v.y;
		}
		return *this ;
	}
};
struct Edge
{
	Vertix head;
	Vertix tail;
	int weight = -1;
	Edge(Vertix H, Vertix T, int w) { head = H; tail = T; weight = w; }
	bool operator< (const Edge& e) //重载小于号
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
	bool operator<= (const Edge& e) //重载小于等于号
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
	bool operator> (const Edge& e)//重载大于号
	{
		if (this->weight>e.weight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	Edge& operator=(const Edge &e)//重载赋值运算符
	{
		if (this != &e)
		{
			this->head = this->head;
			this->tail = this->tail;
			this->weight = this->weight;
		}
		return *this;
	}
	friend	ostream& operator<<(ostream& output, Edge e)//重载输出运算符
	{
		output << e.weight;
		return output;
	}
	friend istream& operator>>(istream& input, Edge e)//重载输入运算符
	{
		input >> e.weight;
		return input;
	}
};
class Graph
{
public:

	Graph()
	{
		MaxVertix = MAX_Vertix;
		Maxweight = MAX_Weight;
		Vertix_num = 0;
		Edge_num = 0;
		Vlist = new Vertix[MaxVertix];
		E = (int * *) new int *[MaxVertix];
		for (int i = 0; i < MaxVertix; i++)
		{
			E[i] = new int[MaxVertix];
		}
		for (int i = 0; i < MaxVertix; i++)
		{
			for (int j = 0; j < MaxVertix; j++)
			{
				if (i == j)
				{
					E[i][j] = 0;//对角线置零
				}
				E[i][j] = Maxweight;//其他位置置为无穷大
			}
		}
	}
	~Graph()
	{
		delete[]Vlist;
		delete[]E;
	}
	string GetValue(int i)
	{
		if (i >= 0 && i <= Vertix_num)
		{
			return Vlist[i].Name;
		}
		return "没有此节点！";
	}
	int GetWeight(int v1, int v2)
	{
		if (v1 != -1 && v2 != -1)
		{
			return E[v1][v2];
		}
		else return -1;
	}
	int GetFirstNeibor(int v)
	{
		if (v != -1)
		{
			for (int col = 0; col < Vertix_num; col++)
			{
				if (E[v][col] > 0 && E[v][col] < Maxweight)
				{
					return col;
				}
			}
		}
		return -1;
	}
	int GetNextNeighbor(int v, int w)
	{
		if (v != -1 && w != -1)
		{
			for (int col = w + 1; col < Vertix_num; col++)
			{
				if (E[v][col] > 0 && E[v][col] < Maxweight)
				{
					return col;
				}
			}
		}
		return -1;
	}
	bool InsertVertix(const Vertix& v)
	{
		if (Vertix_num == MaxVertix)//当前顶点数，已到达最大值
		{
			return false;
		}
		Vlist[Vertix_num] = v;
		Vertix_num++;
		return true;
	}
	bool RemoveVertix(int v)//删除位置为v的节点
	{
		if (v < 0 && v >= Vertix_num)//v不在图中
		{
			return false;
		}
		if (Vertix_num == 1)//图中只剩一个节点不删除
		{
			return false;
		}
		Vlist[v] = Vlist[Vertix_num - 1];//用最后一列代替删除的这一列
		for (int i = 0; i < Vertix_num; i++)
		{
			if (E[i][v] > 0 && E[i][v] < Maxweight)
			{
				Edge_num--;              //通过查找第V列 找到与V相关的边 并删除
			}
		}
		for (int i = 0; i < Vertix_num; i++)
		{
			E[i][v] = E[i][Vertix_num - 1]; //用最后一列代替填补第V列
		}
		Vertix_num--;
		for (int i = 0; i < Vertix_num; i++)
		{
			E[v][i] = E[Vertix_num][i];   // 用最后一行填补第v行的空缺

		}
		return true;
	}
	bool Insert_Edge(int v1, int v2, int weight)
	{
		if (v1 > -1 && v1<Vertix_num && v2>-1 && v2 < Vertix_num && E[v1][v2] == Maxweight)//V1 V2在顶点集中并且之前没有边
		{
			E[v1][v2] = E[v2][v1] = weight;
			Edge_num++;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool Remove_Edge(int v1, int v2)
	{
		if (v1 > -1 && v1<Vertix_num && v2>-1 && v2 < Vertix_num && E[v1][v2] < Maxweight &&E[v1][v2] > 0)//V1 V2在顶点集中并且之前没有边
		{
			E[v1][v2] = E[v2][v1] = Maxweight;
			Edge_num++;
			return true;
		}
		else
		{
			return false;
		}
	}
	int Get_Vertix_num() { return Vertix_num; }//返回当前图的顶点数
	int Get_Edge_num() { return Edge_num; }//返回当前图的边数
	bool IsEmpty()//判断图是否为空
	{
		if (Edge_num == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsFull()//判断图是否已满
	{
		if (Vertix_num == MaxVertix || Edge_num == MaxVertix* (MaxVertix -1)/2 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int Get_VertixPos(Vertix v)
	{
		for (int i = 0; i < Vertix_num; i++)
		{
			if (Vlist[i] == v)
			{
				return i;
			}
		}
		return -1;
	}

private:
	Vertix * Vlist;
	int * * E;
	int Maxweight;
	int MaxVertix;
	int Edge_num;
	int Vertix_num;
};
