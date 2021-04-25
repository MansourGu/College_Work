#include"Stack.cpp"
#include"MinimalHeap.cpp"
#include"UnionFindSet.cpp"
#include"MSTTree.cpp"
#pragma once
using namespace std;
void DFS(Graph& G, int v, bool Visited[])
{
	Visited[v] = true;//将访问节点标记
	int w = G.GetFirstNeibor(v);//第一个邻接点
	while (w != -1)
	{
		cout << G.GetValue(w)<<endl;
		if (Visited[w] == false)
		{
			DFS(G, w, Visited);//递归访问邻接点
		}
		w = G.GetNextNeighbor(v, w);//下一个邻接顶点
	}

}
void DFS(Graph &G, const Vertix &v)
{
	int loc;
	int n = G.Get_Vertix_num();//获取顶点个数
	bool *Visted = new bool[n];//创建辅助数组
	for (int i = 0; i < n; i++)//辅助数组初始化
	{
		Visted[i] = false;
	}
	loc = G.Get_VertixPos(v);//获取当前顶点位置
	DFS(G, loc, Visted);//开始深度搜素
	delete[]Visted;//删除辅助数组
}
void Prim(Graph &G, Vertix u0, MinSpanTree& MST)
{
	MSTEdgeNode ed;
	int i, u, v, count;//边结点辅助单元
	int n = G.Get_Vertix_num(); // 顶点数
	int m = G.Get_Edge_num();  //边数
	 u = G.Get_VertixPos(u0);//求起始顶点号
	MinmalHeap H(m);//建立最小堆
	bool *Vmst = new bool[n];//最小生成树顶点集合
	for (i = 0; i < n; i++)
	{
		Vmst[i] = false;//初始化
	}
	Vmst[u] = true;  //将起始节点置为真
	count = 1;
	do
	{
		v = G.GetFirstNeibor(u);
		while (v!=-1)                                //重复检测u的所有邻接顶点
		{
			if (Vmst[v]==false)                      //若v 不在生成树中 （u，v）入堆
			{ 
				ed.tail = u;                                             
				ed.head = v;                           
				ed.weight = G.GetWeight(u, v);       //tail在树内，head不在树内
				H.Insert(ed);                        
			}
			v = G.GetNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count<n)
		{
			H.RemoveMin(ed);                         //从堆中退出最小权值的边
			if (Vmst[ed.head] == false)              
			{
				MST.Insert(ed);                     //加入最小生成树
				u = ed.head;                        
				Vmst[u] = true;                     //u加入生成树顶点合集
				count++; break;              
			}
		}
	} while (count < n);
	

}
void Dijkstra(Graph &G, Vertix v, int dist[], int path[])
{
	int v_pos = G.Get_VertixPos(v);
	int n = G.Get_Vertix_num();//获取总结点数
	int w;//权重
	bool *S = new bool[n];//最短路径结点集
	for (int i = 0; i < n; i++)
	{
		dist[i] = G.GetWeight(v_pos,i);//将该结点到i结点的边存入数组
		S[i] = false;  //结点集初始化
		if (i!=v_pos && dist[i]<9999)
		{
			path[i] = v_pos;
		}
		else
		{
			path[i] = -1;
		}
	}
	S[v_pos] = true;//将该节点放入顶点集
	dist[v_pos] = 0;
	for (int i = 0; i < n-1; i++)
	{
		int min = 9999;
		int u = v_pos;
		for (int j = 0; j < n; j++)
		{
			if (!S[j] && dist[j]<min)
			{
				u = j; min = dist[j];//找到最短的路径
			}
			S[u] = true;//将该结点放入集合S
			for (int k = 0; k < n; k++)
			{
				w = G.GetWeight(u, k);//获取u，k 之间的权重
				if (!S[k] && w<9999 && dist[u]+w <dist[k])
				{
					dist[k] = dist[u] + w;//修改到k的权值
					path[k] = u;//修改到k的路径
				}
			}
		}
	}







}