#include"Stack.cpp"
#include"MinimalHeap.cpp"
#include"UnionFindSet.cpp"
#include"MSTTree.cpp"
#pragma once
using namespace std;
void DFS(Graph& G, int v, bool Visited[])
{
	Visited[v] = true;//�����ʽڵ���
	int w = G.GetFirstNeibor(v);//��һ���ڽӵ�
	while (w != -1)
	{
		cout << G.GetValue(w)<<endl;
		if (Visited[w] == false)
		{
			DFS(G, w, Visited);//�ݹ�����ڽӵ�
		}
		w = G.GetNextNeighbor(v, w);//��һ���ڽӶ���
	}

}
void DFS(Graph &G, const Vertix &v)
{
	int loc;
	int n = G.Get_Vertix_num();//��ȡ�������
	bool *Visted = new bool[n];//������������
	for (int i = 0; i < n; i++)//���������ʼ��
	{
		Visted[i] = false;
	}
	loc = G.Get_VertixPos(v);//��ȡ��ǰ����λ��
	DFS(G, loc, Visted);//��ʼ�������
	delete[]Visted;//ɾ����������
}
void Prim(Graph &G, Vertix u0, MinSpanTree& MST)
{
	MSTEdgeNode ed;
	int i, u, v, count;//�߽�㸨����Ԫ
	int n = G.Get_Vertix_num(); // ������
	int m = G.Get_Edge_num();  //����
	 u = G.Get_VertixPos(u0);//����ʼ�����
	MinmalHeap H(m);//������С��
	bool *Vmst = new bool[n];//��С���������㼯��
	for (i = 0; i < n; i++)
	{
		Vmst[i] = false;//��ʼ��
	}
	Vmst[u] = true;  //����ʼ�ڵ���Ϊ��
	count = 1;
	do
	{
		v = G.GetFirstNeibor(u);
		while (v!=-1)                                //�ظ����u�������ڽӶ���
		{
			if (Vmst[v]==false)                      //��v ������������ ��u��v�����
			{ 
				ed.tail = u;                                             
				ed.head = v;                           
				ed.weight = G.GetWeight(u, v);       //tail�����ڣ�head��������
				H.Insert(ed);                        
			}
			v = G.GetNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count<n)
		{
			H.RemoveMin(ed);                         //�Ӷ����˳���СȨֵ�ı�
			if (Vmst[ed.head] == false)              
			{
				MST.Insert(ed);                     //������С������
				u = ed.head;                        
				Vmst[u] = true;                     //u��������������ϼ�
				count++; break;              
			}
		}
	} while (count < n);
	

}
void Dijkstra(Graph &G, Vertix v, int dist[], int path[])
{
	int v_pos = G.Get_VertixPos(v);
	int n = G.Get_Vertix_num();//��ȡ�ܽ����
	int w;//Ȩ��
	bool *S = new bool[n];//���·����㼯
	for (int i = 0; i < n; i++)
	{
		dist[i] = G.GetWeight(v_pos,i);//���ý�㵽i���ıߴ�������
		S[i] = false;  //��㼯��ʼ��
		if (i!=v_pos && dist[i]<9999)
		{
			path[i] = v_pos;
		}
		else
		{
			path[i] = -1;
		}
	}
	S[v_pos] = true;//���ýڵ���붥�㼯
	dist[v_pos] = 0;
	for (int i = 0; i < n-1; i++)
	{
		int min = 9999;
		int u = v_pos;
		for (int j = 0; j < n; j++)
		{
			if (!S[j] && dist[j]<min)
			{
				u = j; min = dist[j];//�ҵ���̵�·��
			}
			S[u] = true;//���ý����뼯��S
			for (int k = 0; k < n; k++)
			{
				w = G.GetWeight(u, k);//��ȡu��k ֮���Ȩ��
				if (!S[k] && w<9999 && dist[u]+w <dist[k])
				{
					dist[k] = dist[u] + w;//�޸ĵ�k��Ȩֵ
					path[k] = u;//�޸ĵ�k��·��
				}
			}
		}
	}







}