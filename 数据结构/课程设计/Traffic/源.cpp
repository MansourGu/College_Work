#include<iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include<string>
using namespace std;
class Stack
{
public:
	int top = 0;
	int data[11];
	bool Push(int x)
	{
		if (top == 11)
			return false;
		data[top] = x;
		top++;
		return true;
	}
	int Pop()
	{
		if (top == 0)
			return -1;
		top--;
		return data[top];
	}
};
struct City
{
	string City_Name = "";
	int Pos;
};
class Graph
{
public:
	City city[34];
	int Edge[34][34];
	int Vertix_num = 34;
	int Get_VertixPos(City v)
	{
		return v.Pos;
	}
	int Get_Vertix_num()
	{
		return Vertix_num;
	}
	int GetWeight(int v_ID, int i)
	{
		return Edge[v_ID][i];
	}
	int GetFirstNeibor(int pos)
	{
		for (int i = 0; i < 34; i++)
		{
			if (Edge[pos][i] > 0 && Edge[pos][i] < 9999)
			{
				return i;
			}
		}
		return -1;
	}
	int GetNextNeighbor(int pos, int j)
	{
		for (int i = j + 1; i < 34; i++)
		{
			if (Edge[pos][i] > 0 && Edge[pos][i] < 9999)
			{
				return i;
			}
		}
		return -1;
	}
};
//��ͼ1��ʼ���ߺͶ���
void Print_All(int SrcNum, int DesNum, Graph& G);
void Graph_Initial(int neighboor[34][34], string CityList[34], Graph& g, int Mode = 2)
{
	for (int i = 0; i < 34; i++)
	{
		g.city[i].City_Name = CityList[i];
		g.city[i].Pos = i;
	}
	for (int i = 0; i < 34; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			if (Mode == 1)
			{
				if (!neighboor[i][j] == 0)
				{
					g.Edge[i][j] = neighboor[i][j];
				}
				else
				{
					g.Edge[i][j] = 9999;
				}
			}
			else
			{
				g.Edge[i][j] = neighboor[i][j];
			}
		}
	}
}
//��ȡ�����ļ�������������
void Read_File(int neighboor[34][34], string* CityList, int chooseFile = 1)
{
	ifstream fin;
	if (chooseFile == 1)
	{
		fin.open("city1.csv");
	}
	else
	{
		fin.open("city2.csv");
	}
	if (!fin.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	string field;
	string din;
	bool isfirstline = true;//ȥ����һ���ַ�
	int countRow = 0, countList = 0, countString = 0;
	while (!fin.eof())
	{
		bool isfirst = true;//ȥ��ÿ�е�һ���ַ�
		getline(fin, din);
		istringstream sin(din);
		if (isfirstline)
		{
			isfirstline = false;
			while (!sin.eof())
			{
				getline(sin, field, ',');//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ��� 
				if (isfirst)
				{
					isfirst = false;
					continue;
				}
				CityList[countString] = field.c_str();
				countString++;
			}
		}
		else
		{
			while (!sin.eof())
			{
				getline(sin, field, ',');//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ��� 
				if (isfirst)
				{
					isfirst = false;
					continue;
				}
				neighboor[countRow][countList] = atoi(field.c_str());
				countList++;
				if (countList == 34)
				{
					countList = 0;
					countRow++;
				}
			}
		}
	}
	fin.close();
}
//�����Ҽ�¼·����С�ڵ���10���ܵ���Ŀ�ĵ��·��
void DFS(int start, int end, int path[10000][11], Graph& g, int& pathID, Stack& Stack, bool* visited)//������ջ��ѯ����·��
{
	visited[start] = true;//visited����洢������ı��������trueΪ�ѱ�������ǣ�
	Stack.Push(start);//��ջ
	if (Stack.top == 11)//����10�����
	{
		Stack.Pop();
		visited[start] = false;
		return;
	}
	for (int j = 0; j < 34; j++)
	{
		if (start == end) //�ҵ��յ�
		{
			for (int i = 0; i < Stack.top; i++)
			{
				path[pathID][i] = Stack.data[i];
			}
			pathID++;
			Stack.Pop();//��ջ
			visited[start] = false;
			break;
		}
		if (!visited[j] && (g.Edge[start][j] > 0 && g.Edge[start][j] < 9999))//�ö���δ�����ʹ��Ҵ˶�������ڽ��ȥ
		{
			DFS(j, end, path, g, pathID, Stack, visited);
		}
		if (j == 33) //����ö�������������
		{
			Stack.Pop();
			visited[start] = false;
		}
	}
}
void Floyd(Graph& g, int path[34][34], int dis[34][34])
{
	int i, j, k, n = 34;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			dis[i][j] = g.GetWeight(i, j);
			if (i != j && dis[i][j] < 9999)
			{
				path[i][j] = i;
			}
			else
			{
				path[i][j] = 0;
			}
		}
	}
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (dis[i][k] + dis[k][j] < dis[i][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
}
void Dijkstra(Graph& G, City v, int dist[], int path[])
{
	int v_pos = G.Get_VertixPos(v);
	int n = G.Get_Vertix_num();//��ȡ�ܽ����
	int w;//Ȩ��
	bool* S = new bool[n];//���·����㼯
	for (int i = 0; i < n; i++)
	{
		dist[i] = G.GetWeight(v_pos, i);//���ý�㵽i���ıߴ�������
		S[i] = false;  //��㼯��ʼ��
		if (i != v_pos && dist[i] < 9999)
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
	for (int i = 0; i < n - 1; i++)
	{
		int min = 9999;
		int u = v_pos;
		for (int j = 0; j < n; j++)
		{
			if (!S[j] && dist[j] < min)
			{
				u = j; min = dist[j];//�ҵ���̵�·��
			}
		}
		S[u] = true;//���ý����뼯��S
		for (int k = 0; k < n; k++)
		{
			w = G.GetWeight(u, k);//��ȡu��k ֮���Ȩ��
			if (!S[k] && w < 9999 && dist[u] + w < dist[k])
			{
				dist[k] = dist[u] + w;//�޸ĵ�k��Ȩֵ
				path[k] = u;//�޸ĵ�k��·��
			}
		}

	}
}
int Get_City_ID(string cityName, Graph& g)//��ȡ������ͼ���±�
{
	for (int i = 0; i < 34; i++)
	{
		if (g.city[i].City_Name == cityName)
		{
			return i;
		}
	}
	return -1;
}
//�����·��
void Short_Path(Graph& G, string* CityList, int mode)
{
	int way_to_find;
	string Start_City_Name, End_City_Name;
	cout << "�����뿪ʼ����" << endl;
	if (mode == 2)
		cin.ignore();
	getline(cin, Start_City_Name);
	cout << "�������������" << endl;
	getline(cin, End_City_Name);
	cout << "��ѡ�������õ������·���㷨��ͨ����Ӧ�㷨ǰ�ı��ѡ��" << endl << "1.Floyd " << endl << "2.Dijkstra" << endl;
	cin >> way_to_find;
	while (way_to_find != 1 && way_to_find != 2)
	{
		cout << "�������,����������" << endl;
		cin >> way_to_find;
	}
	cin.ignore();//��Ϊǰ����cin���º����getlineֱ�Ӷ�ȡ��cin��Ļ��з��� ���������Ϊ�� �轫�˴��������

	int Start_City_ID = Get_City_ID(Start_City_Name, G), End_City_ID = Get_City_ID(End_City_Name, G);

	if (mode == 2)
	{
		Print_All(Start_City_ID, End_City_ID, G);
	}
	int Path[34];//��¼ȫ��·��(���򴢴�)
	for (int i = 0; i < 34; i++)
	{
		Path[i] = -1;
	}
	int lowestDis;
	if (way_to_find == 1)
	{
		int path[34][34], dis[34][34];
		Floyd(G, path, dis);
		Path[0] = End_City_ID;
		for (int i = 1; i < 34; i++)
		{
			Path[i] = path[Start_City_ID][Path[i - 1]];
			if (path[Start_City_ID][Path[i - 1]] == Start_City_ID)
			{
				break;
			}
		}
		lowestDis = dis[Start_City_ID][End_City_ID];
	}
	else if (way_to_find == 2)
	{
		int path[34], dis[34];
		Dijkstra(G, G.city[Start_City_ID], dis, path);
		Path[0] = End_City_ID;
		for (int i = 1; i < 34; i++)
		{
			Path[i] = path[Path[i - 1]];
			if (path[Path[i - 1]] == Start_City_ID)
			{
				break;
			}
		}
		lowestDis = dis[End_City_ID];
	}
	//�ڵڶ���ѡ���½����ļ�д��
	if (mode == 2)
	{
		if (way_to_find == 1)
		{
			cout << "��Floyd�µ�";
		}
		else
		{
			cout << "��Djkstra�µ�";
		}
		cout << "·������Ϊ��" << lowestDis << "  ·��Ϊ��";
		for (int i = 33; i >= 0; i--)
		{
			if (Path[i] == -1)
			{
				continue;
			}
			cout << G.city[Path[i]].City_Name << " ";
		}
		cout << endl;
	}
	//�ڵ�����ѡ�������·����·����
	if (mode == 3)
	{
		cout << "·������Ϊ��" << lowestDis << "  ·��Ϊ��";
		for (int i = 33; i >= 0; i--)
		{
			if (Path[i] == -1)
			{
				continue;
			}
			cout << CityList[Path[i]] << " ";
		}
	}
}
//�ϲ�������ʹ���Ϊ��������ر�
void Find_GRAPH_edge(int neigboor[][34], int weight[][34])
{
	for (int i = 0; i < 34; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			if (neigboor[i][j] == 0)
			{
				weight[i][j] = 9999;
			}
		}
	}
}
//�ܿ�ĳ������ѡ·��
void Avoid_Some_CIty(int weight[][34], Graph& G)
{
	string Avoid_City_Name;
	cout << "��������Ҫ�ƹ��ĳ���" << endl;
	cin.ignore();
	getline(cin, Avoid_City_Name);
	int Avoid_City_ID = Get_City_ID(Avoid_City_Name, G);
	for (int i = 0; i < 34; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			if (i == Avoid_City_ID || j == Avoid_City_ID)
			{
				weight[i][j] = 9999;
			}
		}
	}
}
int partition(int arr[], int start, int end)  //�һ�׼�� ����
{
	int i = start + 1;
	int j = end;
	int temp = arr[start];

	while (i <= j)
	{
		while (arr[i] < temp)
		{
			i++;
		}
		while (arr[j] > temp)
		{
			j--;
		}
		if (i < j)
		{
			swap(arr[i++], arr[j--]);
		}
		else
		{
			i++;
		}
	}
	swap(arr[j], arr[start]);
	return j;

}
void quick_sort(int arr[], int start, int end)
{
	if (start > end)
	{
		return;
	}
	int j = partition(arr, start, end);
	quick_sort(arr, start, j - 1);
	quick_sort(arr, j + 1, end);
}
//����ȫ������·��
void Print_All(int Start_Num, int End_Num, Graph& G)
{
	int print_all[10000][11], path_num = 0;//print_all����ȫ��·��
	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			print_all[i][j] = -1;
		}
	}
	Stack Stack;
	bool visted[34];
	for (int i = 0; i < 34; i++)
	{
		visted[i] = 0;
	}
	DFS(Start_Num, End_Num, print_all, G, path_num, Stack, visted);
	int* path_length = new int[path_num], *temp = new int[path_num];//temp������¼���ź��·�������˳��
	//����ӦPos·����·����
	for (int i = 0; i < path_num; i++)
	{
		path_length[i] = 0;
		for (int j = 0; j < 10; j++)
		{
			if (print_all[i][j + 1] != -1)
			{
				path_length[i] += G.Edge[print_all[i][j]][print_all[i][j + 1]];//���϶�Ӧ·��Pos�µ�����·����
			}
		}
	}
	for (int i = 0; i < path_num; i++)//temp���������С˳��
	{
		temp[i] = path_length[i];
	}
	quick_sort(temp, 0, path_num - 1);
	ofstream PrintFile("Path.text", ios::out);//ios::out�����û���ļ�����ô���ɿ��ļ���������ļ�������ļ�
	if (!PrintFile)
	{
		cout << "���ļ�ʧ�ܣ�" << endl;
		exit(1);
	}
	for (int k = 0; k < path_num; k++)
	{
		for (int j = 0; j < path_num; j++)
		{
			if (path_length[j] == temp[k])
			{
				PrintFile << "·������Ϊ��" << path_length[j] << "  ·��Ϊ��";
				for (int i = 0; i < 11; i++)
				{
					if (print_all[j][i] == -1)
					{
						break;
					}
					PrintFile << G.city[print_all[j][i]].City_Name << " ";
				}
				PrintFile << endl;
			}
		}
	}
}
//���k��·��
void Kth_Shortest_Path(string* cityname, Graph& G)
{
	int k;
	string Start_ID, End_ID;
	cout << "�����뿪ʼ����" << endl;
	cin.ignore();
	getline(cin, Start_ID);
	cout << "�������������" << endl;
	getline(cin, End_ID);
	cout << "����������Ҫ�ĵ�k��·��" << endl;
	cin >> k;
	int Start_City_ID = Get_City_ID(Start_ID, G), End_City_ID = Get_City_ID(End_ID, G);
	int all_path[10000][11], path_num = 0;
	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			all_path[i][j] = -1;
		}
	}
	Stack Stack;
	bool visted[34];
	for (int i = 0; i < 34; i++)
	{
		visted[i] = 0;
	}
	DFS(Start_City_ID, End_City_ID, all_path, G, path_num, Stack, visted);
	int* Length_of_Path = new int[path_num], *temp = new int[path_num];//temp������¼���ź��·�������˳��
	//����ӦPos·����·����
	for (int i = 0; i < path_num; i++)
	{
		Length_of_Path[i] = 0;
		for (int j = 0; j < 10; j++)
		{
			if (all_path[i][j + 1] != -1)
			{
				Length_of_Path[i] += G.Edge[all_path[i][j]][all_path[i][j + 1]];//���϶�Ӧ·��Pos�µ�����·����
			}
		}
	}
	for (int i = 0; i < path_num; i++)
	{
		temp[i] = Length_of_Path[i];
	}
	quick_sort(temp, 0, path_num - 1);
	cout << "��" << Start_ID << "��" << End_ID << "�ĵ�" << k << "��·��������:" << temp[k - 1] << endl;
	cout << "·����:";
	for (int i = 0; i < path_num; i++)
	{
		if (Length_of_Path[i] == temp[k + 1])
		{
			for (int j = 0; j < 11; j++)
			{
				if (all_path[i][j] == -1)
				{
					break;
				}
				else
				{
					cout << G.city[all_path[i][j]].City_Name << " ";
				}
			}
		}
	}
}
void UI()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "����������ʵ�ֹ���:" << endl;
	cout << "1.�������Ƿ��人�ж�" << endl;
	cout << "2.������·��" << endl;
	cout << "3.������·��(�ƿ�ĳ������)" << endl;
	cout << "4.����м�ĵ�k��·��" << endl;
	cout << "����.�˳�" << endl;
	cout << "------------------------------------------------------------" << endl;
}
void Func_one()
{
	string cityname[34];
	int neighboor[34][34];
	Read_File(neighboor, cityname, 1);
	int weight[34][34];
	Read_File(weight, cityname, 2);
	for (int i = 0; i < 34; i++)//��ȫ·�����Ȳ�ȫ�ĵط�
	{
		for (int j = 0; j < 34; j++)
		{
			if (weight[i][j] == 0)
			{
				weight[i][j] = weight[j][i];
			}
		}
	}
	int desID;
	int desDist[34], desPath[34];
	Find_GRAPH_edge(neighboor, weight);
	Graph G;
	Graph_Initial(neighboor, cityname, G, 1);
	desID = Get_City_ID("�人", G);
	Dijkstra(G, G.city[desID], desDist, desPath);
	for (int i = 0; i < 34; i++)
	{
		if (desDist[i] > 3)
		{
			cout << "ȫ�����人�ĳ��У�ʡ�ᣩ���м䳬��2��" << endl;
			break;
		}
	}
	cout << "ȫ�����人�ĳ��У�ʡ�ᣩ���м䲻����2��" << endl;
}
void Func_two()
{
	string cityname[34];
	int neighboor[34][34];
	Read_File(neighboor, cityname, 1);
	int weight[34][34];
	Read_File(weight, cityname, 2);
	for (int i = 0; i < 34; i++)//��ȫ·�����Ȳ�ȫ�ĵط�
	{
		for (int j = 0; j < 34; j++)
		{
			if (weight[i][j] == 0)
			{
				weight[i][j] = weight[j][i];
			}
		}
	}
	int desID;
	int desDist[34], desPath[34];
	Find_GRAPH_edge(neighboor, weight);
	Graph G;
	Graph_Initial(weight, cityname, G);
	Short_Path(G, cityname, 2);
	cout << "д��ɹ�" << endl;
}
void Func_three()
{
	string cityname[34];
	int neighboor[34][34];
	Read_File(neighboor, cityname, 1);
	int weight[34][34];
	Read_File(weight, cityname, 2);
	for (int i = 0; i < 34; i++)//��ȫ·�����Ȳ�ȫ�ĵط�
	{
		for (int j = 0; j < 34; j++)
		{
			if (weight[i][j] == 0)
			{
				weight[i][j] = weight[j][i];
			}
		}
	}
	int desID;
	int desDist[34], desPath[34];
	Find_GRAPH_edge(neighboor, weight);
	Graph G;
	Graph_Initial(neighboor, cityname, G, 1);
	Avoid_Some_CIty(weight, G);
	Graph_Initial(weight, cityname, G);
	Short_Path(G, cityname, 3);
}
void Func_four()
{
	string cityname[34];
	int neighboor[34][34];
	Read_File(neighboor, cityname, 1);
	int weight[34][34];
	Read_File(weight, cityname, 2);
	for (int i = 0; i < 34; i++)//��ȫ·�����Ȳ�ȫ�ĵط�
	{
		for (int j = 0; j < 34; j++)
		{
			if (weight[i][j] == 0)
			{
				weight[i][j] = weight[j][i];
			}
		}
	}
	int desID;
	int desDist[34], desPath[34];
	Find_GRAPH_edge(neighboor, weight);
	Graph G;
	Graph_Initial(weight, cityname, G);
	Kth_Shortest_Path(cityname, G);
}
void Menu()
{
	bool Is_stop = 1;
	while (Is_stop)
	{
		UI();
		int choose_func;
		cin >> choose_func;
		switch (choose_func)
		{
		case 1:
			Func_one();
			break;
		case 2:
			Func_two();
			break;
		case 3:
			Func_three();
			break;
		case 4:
			Func_four();
			break;
		case 5:
			break;
		default:
			Is_stop = 0;
			break;
		}
		system("pause");
		system("cls");
	}
}
int main()
{
	Menu();
	return 0;
}