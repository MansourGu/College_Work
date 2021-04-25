#include<iostream>
#include<string>
#include<vector>
#pragma once
#define MAX_Vertix 10
#define MAX_Weight 9999
using namespace std;
struct  Vertix
{
	string Name; //�ڵ�����
	int x; //�ڵ������
	int y;//�ڵ�������
	Vertix(string name) { Name = name; }
	Vertix() :Name(""), x(0),y(0){};
	bool operator==(const Vertix& v) //����==�����
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
	friend	ostream& operator<<(ostream& output, Vertix v)//������������
	{
		output << v.Name;
		return output;
	}
	friend istream& operator>>(istream& input, Vertix v)//�������������
	{
		input >> v.Name;
		return input;
	}
	Vertix& operator=(const Vertix &v)//���ظ�ֵ�����
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
	bool operator< (const Edge& e) //����С�ں�
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
	bool operator<= (const Edge& e) //����С�ڵ��ں�
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
	bool operator> (const Edge& e)//���ش��ں�
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
	Edge& operator=(const Edge &e)//���ظ�ֵ�����
	{
		if (this != &e)
		{
			this->head = this->head;
			this->tail = this->tail;
			this->weight = this->weight;
		}
		return *this;
	}
	friend	ostream& operator<<(ostream& output, Edge e)//������������
	{
		output << e.weight;
		return output;
	}
	friend istream& operator>>(istream& input, Edge e)//�������������
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
					E[i][j] = 0;//�Խ�������
				}
				E[i][j] = Maxweight;//����λ����Ϊ�����
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
		return "û�д˽ڵ㣡";
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
		if (Vertix_num == MaxVertix)//��ǰ���������ѵ������ֵ
		{
			return false;
		}
		Vlist[Vertix_num] = v;
		Vertix_num++;
		return true;
	}
	bool RemoveVertix(int v)//ɾ��λ��Ϊv�Ľڵ�
	{
		if (v < 0 && v >= Vertix_num)//v����ͼ��
		{
			return false;
		}
		if (Vertix_num == 1)//ͼ��ֻʣһ���ڵ㲻ɾ��
		{
			return false;
		}
		Vlist[v] = Vlist[Vertix_num - 1];//�����һ�д���ɾ������һ��
		for (int i = 0; i < Vertix_num; i++)
		{
			if (E[i][v] > 0 && E[i][v] < Maxweight)
			{
				Edge_num--;              //ͨ�����ҵ�V�� �ҵ���V��صı� ��ɾ��
			}
		}
		for (int i = 0; i < Vertix_num; i++)
		{
			E[i][v] = E[i][Vertix_num - 1]; //�����һ�д������V��
		}
		Vertix_num--;
		for (int i = 0; i < Vertix_num; i++)
		{
			E[v][i] = E[Vertix_num][i];   // �����һ�����v�еĿ�ȱ

		}
		return true;
	}
	bool Insert_Edge(int v1, int v2, int weight)
	{
		if (v1 > -1 && v1<Vertix_num && v2>-1 && v2 < Vertix_num && E[v1][v2] == Maxweight)//V1 V2�ڶ��㼯�в���֮ǰû�б�
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
		if (v1 > -1 && v1<Vertix_num && v2>-1 && v2 < Vertix_num && E[v1][v2] < Maxweight &&E[v1][v2] > 0)//V1 V2�ڶ��㼯�в���֮ǰû�б�
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
	int Get_Vertix_num() { return Vertix_num; }//���ص�ǰͼ�Ķ�����
	int Get_Edge_num() { return Edge_num; }//���ص�ǰͼ�ı���
	bool IsEmpty()//�ж�ͼ�Ƿ�Ϊ��
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
	bool IsFull()//�ж�ͼ�Ƿ�����
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
