#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<string>
#include<vector>
#define MAX_Vertix 10
#define MAX_Weight 9999
#define Size 20;
using namespace std;
struct MSTEdgeNode
{
	int head;
	int tail;
	int weight;
	MSTEdgeNode() :head(-1), tail(-1), weight(0) {};
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
	void Insert(MSTEdgeNode& item)
	{
		if (Currentsize == Maxsize)
		{
			cout << "空间已满！";
			return;
		}
		EdgeValue[Currentsize] = item;
		Currentsize++;
		return;

	}
	~MinSpanTree() { delete[] EdgeValue; }
	void Output()
	{
		for (int i = 0; i < Currentsize; i++)
		{
			cout << EdgeValue[i]<<endl;
		}
	}

private:
	MSTEdgeNode*EdgeValue;
	int Maxsize, Currentsize;//最大元素个数和当前个数
};
class MinmalHeap
{
public:
	MinmalHeap(int sz)
	{
		MaxHeap_Size = Size;
		if (MaxHeap_Size < sz)
		{
			MaxHeap_Size = sz;
		}
		heap = new MSTEdgeNode[MaxHeap_Size];
		Current_Size = 0;
	}
	MinmalHeap(MSTEdgeNode arr[], int n)//通过数组建堆
	{

		if (MaxHeap_Size < n)
		{
			MaxHeap_Size = n;
		}

		heap = new  MSTEdgeNode[MaxHeap_Size];
		if (heap == NULL)
		{
			cout << "堆存储分配失败！" << endl;
			exit(1);
		}
		for (int i = 0; i < MaxHeap_Size; i++)
		{
			heap[i] = arr[i];                 //复制堆数组，建立最小堆
		}
		Current_Size = n;                     //当前最小堆的大小
		int Current_Pos = (Current_Size - 2) / 2;//寻找最初的调整位置，最后的分支节点
		while (Current_Pos >= 0)
		{
			SiftDown(Current_Pos, Current_Size - 1);//局部自上向下下滑调整
			Current_Pos--;//在向前换一个分支节点
		}
	}
	~MinmalHeap()
	{
		delete[]heap;
	}
	bool Insert(const  MSTEdgeNode& e)//将元素插入堆中
	{
		if (Current_Size == MaxHeap_Size)//堆满不能在插入
		{
			return false;
		}
		heap[Current_Size] = e;
		SiftUp(Current_Size);
		Current_Size++;
		return true;
	}
	bool RemoveMin(MSTEdgeNode &e)
	{
		if (Current_Size == 0)
		{
			cout << "Heap is Empty!" << endl;
			return false;
		}
		e = heap[0];                        //将堆顶元素取出
		heap[0] = heap[Current_Size - 1];   //将最后一个元素放入堆顶
		Current_Size--;                     //当前元素数减一
		SiftDown(0, Current_Size - 1);      //自上向下开始调整
		return true;
	}
	void SiftDown(int start, int m)
	{
		int i = start, j = 2 * i + 1;//j是i的左子女位置
		MSTEdgeNode temp = heap[i];
		while (j <= m)              //检查是否到最后的位置
		{
			if (j<m && heap[i] > heap[j + 1])
			{
				j++;			   //让j指向两子女的小者
			}
			if (temp <= heap[j])  //小则不做调整
			{
				break;
			}
			else
			{
				heap[i] = heap[j];//否则小者上移，i，j下降
				i = j;
				j = 2 * i + 1;
			}
		}
		heap[i] = temp;          //回放temp中的暂存元素
	}
	void SiftUp(int start)//从start上滑到0调整成为最小堆
	{
		int j = start, i = (j - 1) / 2;
		MSTEdgeNode temp = heap[j];
		while (j > 0)
		{
			if (heap[i] <= temp)
			{
				break;
			}
			else
			{
				heap[j] = heap[i]; j = i; i = (i - 1) / 2;
			}
		}
		heap[j] = temp;
	}
	bool IsEmpty()
	{
		if (Current_Size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


private:
	int MaxHeap_Size; //最小堆的最大元素数
	int Current_Size; //最小堆的当前元素数
	MSTEdgeNode * heap;//存放数组最小堆中元素的数组

};
struct  Vertix
{
	string Name; //节点名字
	int x; //节点横坐标
	int y;//节点纵坐标
	Vertix(string name , int x1 ,int y1) { Name = name, x= x1 ,y=y1; }
	Vertix() :Name(""), x(0), y(0) {};
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
			this->Name = v.Name;
			this->x = v.x;
			this->y = v.y;
		return *this;
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
		if (this->weight > e.weight)
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
			int temp = E[v1][v2];
			return temp;
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
		if (Vertix_num == MaxVertix || Edge_num == MaxVertix * (MaxVertix - 1) / 2)
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
string DFS_PATH;
Graph G,G1,G2,G3;
int path[10];
int dist1[10];
string path_record[10];
Vertix v0("0",320,40), v1("1", 220, 60), v2("2", 90, 130), v3("3", 200, 120), v4("4", 300, 100), v5("5", 20, 180), v6("6" ,90, 230), v7("7", 180, 190), v8("8", 300, 180), v9("9", 170, 280);
Vertix V[10] = { v0, v1, v2, v3, v4, v5, v6, v7, v8, v9 };
Vertix V2[10];
Vertix V3[10];
Edge e0(v0, v1, 750), e1(v4, v8, 960), e2(v1, v2, 1140), e3(v2, v5, 840), e4(v5, v6, 340), e5(v6, v7, 900), e6(v7, v8, 680), e7(v7, v9, 1380),
e8(v6, v9, 2500), e9(v9, v8, 2600), e10(v7, v3, 530), e11(v3, v2, 570), e12(v3, v4, 820), e13(v3, v1, 650), e14(v3, v8, 1200),
e15(v1, v4, 800), e16(v0, v4, 680);
Edge E[17] = { e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12,e13,e14,e15,e16};
void Print_Vertix(Vertix v, int judge ,int flag)
{
	int x, y;
	if (flag ==1)
	{
		x = v.x;
		y = v.y;
	}
	if (flag ==2)
	{
		x = v.x + 360;
		y = v.y;
	}
	if (flag ==3)
	{
		x = v.x + 720;
		y = v.y;
	}
	if (judge == 1)//表示未探测
	{
		setfillcolor(BLUE);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
	if (judge == 2)//表示访问成功
	{
		setfillcolor(GREEN);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
	if (judge == 3)//表示尝试访问
	{
		setfillcolor(RED);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
	if (judge == 4)//表示当前结点
	{
		setfillcolor(YELLOW);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
	if (judge == 5)//表示最初状态
	{
		setfillcolor(WHITE);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
}
void Print_Line(Vertix v1,Vertix v2 ,int judge ,int flag)
{
	int x1, y1,x2,y2;
	if (flag == 1)
	{
		x1 = v1.x;
		y1 = v1.y;
		x2 = v2.x;
		y2 = v2.y;
	}
	if (flag == 2)
	{
		x1 = v1.x+360;
		y1 = v1.y;
		x2 = v2.x+360;
		y2 = v2.y;
	}
	if (flag == 3)
	{
		x1 = v1.x + 720;
		y1 = v1.y;
		x2 = v2.x + 720;
		y2 = v2.y;
	}
	if (judge ==1)//表示成功
	{
		setlinecolor(GREEN);
		line(x1, y1, x2, y2);
		int temp = G.GetWeight(G.Get_VertixPos(v1), G.Get_VertixPos(v2));
		string str = to_string(temp);
		outtextxy((x1 + x2) / 2 - 5, (y1 + y2) / 2, str.c_str());
	}
	if (judge == 2)//表示重复
	{
		setlinecolor(RED);
		line(x1, y1, x2, y2);
		int temp = G.GetWeight(G.Get_VertixPos(v1), G.Get_VertixPos(v2));
		string str = to_string(temp);
		outtextxy((x1 + x2) / 2 - 5, (y1 + y2) / 2, str.c_str());
	
	}
	if (judge == 3)//表示恢复
	{
		setlinecolor(WHITE);
		line(x1, y1, x2, y2);
		int temp = G.GetWeight(G.Get_VertixPos(v1), G.Get_VertixPos(v2));
		string str = to_string(temp);
		outtextxy((x1 + x2) / 2 - 5, (y1 + y2) / 2, str.c_str());
	
	}

}
void DFS(Graph& G, int v, bool Visited[])
{
	DFS_PATH += (to_string(v) + "->");
	Visited[v] = true;//将访问节点标记
	outtextxy(0, 300, DFS_PATH.c_str());
	int w = G.GetFirstNeibor(v);//第一个邻接点
	while (w != -1)
	{
		string temp = "当前节点：" + to_string(v);
		outtextxy(0, 0, temp.c_str());
		string temp1 = "当前访问节点：" + to_string(w);
		outtextxy(0, 20, temp1.c_str());
		if (Visited[w] == true)
		{
			string temp2 = "已访问！";
			outtextxy(0, 40, temp2.c_str());
			/*Sleep(500);
			Print_Vertix(V[w], 3,1);
			Sleep(500);
			Print_Vertix(V[w], 2 ,1);*/
		}
		if (Visited[w] == false)
		{
			
			
			string temp3 = "成功！";
			outtextxy(0, 40, temp3.c_str());
			Print_Line(V[v], V[w],1,1);
			Print_Vertix(V[w], 2,1);
			Sleep(500);
			Print_Vertix(V[v], 2,1);
			DFS(G, w, Visited);//递归访问邻接点
			Print_Vertix(V[w], 4, 1);
			Sleep(500);
			Print_Vertix(V[w], 2, 1);

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
		Print_Vertix(V[i], 1,1);
	}
	loc = G.Get_VertixPos(v);//获取当前顶点位置
	DFS_PATH = "当前路径信息：";
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
		Print_Vertix(V[i], 1,2);
	}
	Vmst[u] = true;  //将起始节点置为真
	Print_Vertix(V[u], 2,2);
	Sleep(500);
	count = 1;
	do
	{
		v = G.GetFirstNeibor(u);
		while (v != -1)                                //重复检测u的所有邻接顶点
		{
			if (Vmst[v] == false)                      //若v 不在生成树中 （u，v）入堆
			{
				ed.tail = u;
				ed.head = v;
				ed.weight = G.GetWeight(u, v);       //tail在树内，head不在树内
				H.Insert(ed);
			}
			v = G.GetNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count < n)
		{
			H.RemoveMin(ed);                         //从堆中退出最小权值的边
			if (Vmst[ed.head] == false)
			{
				MST.Insert(ed);                     //加入最小生成树
				u = ed.head;
				Vmst[u] = true;                     //u加入生成树顶点合集
				Print_Line(V[u], V[ed.tail], 1,2);
				Sleep(500);
				Print_Vertix(V[u], 2,2);
				Sleep(500);
				count++;
				break;
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
		Print_Vertix(V[i], 1,3);
	}
	Print_Vertix(V[v_pos], 2,3);
	for (int i = 0; i < n; i++)
	{
		dist[i] = G.GetWeight(v_pos, i);//将该结点到i结点的边存入数组
		S[i] = false;  //结点集初始化
		
		if (i != v_pos && dist[i] < 9999)
		{
			path[i] = v_pos;
			Print_Line(V[v_pos], V[i],1,3);
			Sleep(500);
			Print_Vertix(V[i], 2,3);
			Sleep(500);
		}
		else
		{
			path[i] = -1;
		}
	}
	S[v_pos] = true;//将该节点放入顶点集
	Print_Vertix(V[v_pos], 2,3);
	Sleep(500);
	dist[v_pos] = 0;
	for (int i = 0; i < n-1 ; i++)
	{
		int min = 9999;
		int u = v_pos;
		for (int j = 0; j < n; j++)
		{
			if (S[j]==false && dist[j] < min)
			{
				u = j; min = dist[j];//找到最短的路径
				Print_Vertix(V[u], 2,3);
				Sleep(500);
			}
			S[u] = true;//将该结点放入集合S
			
			for (int k = 0; k < n; k++)
			{
				w = G.GetWeight(u, k);//获取u，k 之间的权重
				if (S[k]==false && w < 9999 && ((dist[u] + w) < dist[k]))
				{	
					dist[k] = dist[u] + w;//修改到k的权值
					if (path[k]!=-1)
					{
						Print_Line(V[path[k]], V[k], 3, 3);
						Sleep(500);
					}
					path[k] = u;//修改到k的路径
					Print_Line(V[u], V[k], 1,3);
					Print_Vertix(V[k], 2, 3);
					Sleep(500);
				}
			}
		}
	}
}
void Initial_G(Graph &G ,Vertix V[] ,Edge E[])
{
	for (int i = 0; i < 10; i++)
	{
		G.InsertVertix(V[i]);//初始化顶点结点
	}
	for (int i = 0; i < 17; i++)
	{
		G.Insert_Edge(G.Get_VertixPos(E[i].head), G.Get_VertixPos(E[i].tail), E[i].weight);//初始化边
	}
}
void Initial_Graph(int flag)
{
	if (flag==1)
	{
		initgraph(1080, 640);
	}
	for (int i = 0; i < 17; i++)
	{
		Edge e = E[i];
		Print_Line(e.head, e.tail, 3, flag);
	}
	for (int i = 0; i < 10; i++)
	{
		Print_Vertix(V[i], 5, flag);
	}
}
string Path_record(int i)
{
	string temp1 = ("到" + V[i].Name + "的路径信息为：");
	string temp2;
	string temp3;
	int j = path[i];
	while (j!=-1)
	{
		temp2 += (V[j].Name + "  ");
		j = path[j];
	}
	return temp1+temp2;
}
void Initial_ALL()
{
	Initial_G(G, V, E);
	Initial_G(G1, V, E);
	Initial_G(G2, V, E);
	Initial_G(G3, V, E);

	Initial_Graph(1);
	Initial_Graph(2);
	Initial_Graph(3);
	
}
void Menu()
{
	
	cout << "请选择开始的结点";
	string temp;
	cin >> temp;
	int i;
	Initial_ALL();
	for ( i = 0; i < 10; i++)
	{
		if (V[i].Name == temp)
		{
			//DFS(G1, V[i]);
			MinSpanTree MST(20);
			Prim(G2, V[i], MST);
			//Dijkstra(G3, V[i], dist1, path);
			break;
		}
	}
	for (int j = 0; j < 10; j++)
	{
		string temp1 = to_string(dist1[j]);
		string temp = (Path_record(j)+"            路径长度为: " +temp1);
		outtextxy(720, 400+j*20, temp.c_str());
	}
	system("pause");
	system("cls");
	closegraph();
	Menu();
}
int main()
{
	Menu();
	system("pause");
	return 0;
}