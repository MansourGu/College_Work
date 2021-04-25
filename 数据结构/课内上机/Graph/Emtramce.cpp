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
	void Insert(MSTEdgeNode& item)
	{
		if (Currentsize == Maxsize)
		{
			cout << "�ռ�������";
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
	int Maxsize, Currentsize;//���Ԫ�ظ����͵�ǰ����
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
	MinmalHeap(MSTEdgeNode arr[], int n)//ͨ�����齨��
	{

		if (MaxHeap_Size < n)
		{
			MaxHeap_Size = n;
		}

		heap = new  MSTEdgeNode[MaxHeap_Size];
		if (heap == NULL)
		{
			cout << "�Ѵ洢����ʧ�ܣ�" << endl;
			exit(1);
		}
		for (int i = 0; i < MaxHeap_Size; i++)
		{
			heap[i] = arr[i];                 //���ƶ����飬������С��
		}
		Current_Size = n;                     //��ǰ��С�ѵĴ�С
		int Current_Pos = (Current_Size - 2) / 2;//Ѱ������ĵ���λ�ã����ķ�֧�ڵ�
		while (Current_Pos >= 0)
		{
			SiftDown(Current_Pos, Current_Size - 1);//�ֲ����������»�����
			Current_Pos--;//����ǰ��һ����֧�ڵ�
		}
	}
	~MinmalHeap()
	{
		delete[]heap;
	}
	bool Insert(const  MSTEdgeNode& e)//��Ԫ�ز������
	{
		if (Current_Size == MaxHeap_Size)//���������ڲ���
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
		e = heap[0];                        //���Ѷ�Ԫ��ȡ��
		heap[0] = heap[Current_Size - 1];   //�����һ��Ԫ�ط���Ѷ�
		Current_Size--;                     //��ǰԪ������һ
		SiftDown(0, Current_Size - 1);      //�������¿�ʼ����
		return true;
	}
	void SiftDown(int start, int m)
	{
		int i = start, j = 2 * i + 1;//j��i������Ůλ��
		MSTEdgeNode temp = heap[i];
		while (j <= m)              //����Ƿ�����λ��
		{
			if (j<m && heap[i] > heap[j + 1])
			{
				j++;			   //��jָ������Ů��С��
			}
			if (temp <= heap[j])  //С��������
			{
				break;
			}
			else
			{
				heap[i] = heap[j];//����С�����ƣ�i��j�½�
				i = j;
				j = 2 * i + 1;
			}
		}
		heap[i] = temp;          //�ط�temp�е��ݴ�Ԫ��
	}
	void SiftUp(int start)//��start�ϻ���0������Ϊ��С��
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
	int MaxHeap_Size; //��С�ѵ����Ԫ����
	int Current_Size; //��С�ѵĵ�ǰԪ����
	MSTEdgeNode * heap;//���������С����Ԫ�ص�����

};
struct  Vertix
{
	string Name; //�ڵ�����
	int x; //�ڵ������
	int y;//�ڵ�������
	Vertix(string name , int x1 ,int y1) { Name = name, x= x1 ,y=y1; }
	Vertix() :Name(""), x(0), y(0) {};
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
		if (this->weight > e.weight)
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
	if (judge == 1)//��ʾδ̽��
	{
		setfillcolor(BLUE);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
	if (judge == 2)//��ʾ���ʳɹ�
	{
		setfillcolor(GREEN);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
	if (judge == 3)//��ʾ���Է���
	{
		setfillcolor(RED);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
	if (judge == 4)//��ʾ��ǰ���
	{
		setfillcolor(YELLOW);
		fillcircle(x, y, 20);
		outtextxy(x - 4, y - 6, v.Name.c_str());
	}
	if (judge == 5)//��ʾ���״̬
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
	if (judge ==1)//��ʾ�ɹ�
	{
		setlinecolor(GREEN);
		line(x1, y1, x2, y2);
		int temp = G.GetWeight(G.Get_VertixPos(v1), G.Get_VertixPos(v2));
		string str = to_string(temp);
		outtextxy((x1 + x2) / 2 - 5, (y1 + y2) / 2, str.c_str());
	}
	if (judge == 2)//��ʾ�ظ�
	{
		setlinecolor(RED);
		line(x1, y1, x2, y2);
		int temp = G.GetWeight(G.Get_VertixPos(v1), G.Get_VertixPos(v2));
		string str = to_string(temp);
		outtextxy((x1 + x2) / 2 - 5, (y1 + y2) / 2, str.c_str());
	
	}
	if (judge == 3)//��ʾ�ָ�
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
	Visited[v] = true;//�����ʽڵ���
	outtextxy(0, 300, DFS_PATH.c_str());
	int w = G.GetFirstNeibor(v);//��һ���ڽӵ�
	while (w != -1)
	{
		string temp = "��ǰ�ڵ㣺" + to_string(v);
		outtextxy(0, 0, temp.c_str());
		string temp1 = "��ǰ���ʽڵ㣺" + to_string(w);
		outtextxy(0, 20, temp1.c_str());
		if (Visited[w] == true)
		{
			string temp2 = "�ѷ��ʣ�";
			outtextxy(0, 40, temp2.c_str());
			/*Sleep(500);
			Print_Vertix(V[w], 3,1);
			Sleep(500);
			Print_Vertix(V[w], 2 ,1);*/
		}
		if (Visited[w] == false)
		{
			
			
			string temp3 = "�ɹ���";
			outtextxy(0, 40, temp3.c_str());
			Print_Line(V[v], V[w],1,1);
			Print_Vertix(V[w], 2,1);
			Sleep(500);
			Print_Vertix(V[v], 2,1);
			DFS(G, w, Visited);//�ݹ�����ڽӵ�
			Print_Vertix(V[w], 4, 1);
			Sleep(500);
			Print_Vertix(V[w], 2, 1);

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
		Print_Vertix(V[i], 1,1);
	}
	loc = G.Get_VertixPos(v);//��ȡ��ǰ����λ��
	DFS_PATH = "��ǰ·����Ϣ��";
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
		Print_Vertix(V[i], 1,2);
	}
	Vmst[u] = true;  //����ʼ�ڵ���Ϊ��
	Print_Vertix(V[u], 2,2);
	Sleep(500);
	count = 1;
	do
	{
		v = G.GetFirstNeibor(u);
		while (v != -1)                                //�ظ����u�������ڽӶ���
		{
			if (Vmst[v] == false)                      //��v ������������ ��u��v�����
			{
				ed.tail = u;
				ed.head = v;
				ed.weight = G.GetWeight(u, v);       //tail�����ڣ�head��������
				H.Insert(ed);
			}
			v = G.GetNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count < n)
		{
			H.RemoveMin(ed);                         //�Ӷ����˳���СȨֵ�ı�
			if (Vmst[ed.head] == false)
			{
				MST.Insert(ed);                     //������С������
				u = ed.head;
				Vmst[u] = true;                     //u��������������ϼ�
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
	int n = G.Get_Vertix_num();//��ȡ�ܽ����
	int w;//Ȩ��
	bool *S = new bool[n];//���·����㼯
	for (int i = 0; i < n; i++)
	{
		Print_Vertix(V[i], 1,3);
	}
	Print_Vertix(V[v_pos], 2,3);
	for (int i = 0; i < n; i++)
	{
		dist[i] = G.GetWeight(v_pos, i);//���ý�㵽i���ıߴ�������
		S[i] = false;  //��㼯��ʼ��
		
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
	S[v_pos] = true;//���ýڵ���붥�㼯
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
				u = j; min = dist[j];//�ҵ���̵�·��
				Print_Vertix(V[u], 2,3);
				Sleep(500);
			}
			S[u] = true;//���ý����뼯��S
			
			for (int k = 0; k < n; k++)
			{
				w = G.GetWeight(u, k);//��ȡu��k ֮���Ȩ��
				if (S[k]==false && w < 9999 && ((dist[u] + w) < dist[k]))
				{	
					dist[k] = dist[u] + w;//�޸ĵ�k��Ȩֵ
					if (path[k]!=-1)
					{
						Print_Line(V[path[k]], V[k], 3, 3);
						Sleep(500);
					}
					path[k] = u;//�޸ĵ�k��·��
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
		G.InsertVertix(V[i]);//��ʼ��������
	}
	for (int i = 0; i < 17; i++)
	{
		G.Insert_Edge(G.Get_VertixPos(E[i].head), G.Get_VertixPos(E[i].tail), E[i].weight);//��ʼ����
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
	string temp1 = ("��" + V[i].Name + "��·����ϢΪ��");
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
	
	cout << "��ѡ��ʼ�Ľ��";
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
		string temp = (Path_record(j)+"            ·������Ϊ: " +temp1);
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