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
//对图1初始化边和顶点
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
//读取矩阵文件并存在数组中
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
	bool isfirstline = true;//去除第一行字符
	int countRow = 0, countList = 0, countString = 0;
	while (!fin.eof())
	{
		bool isfirst = true;//去除每行第一个字符
		getline(fin, din);
		istringstream sin(din);
		if (isfirstline)
		{
			isfirstline = false;
			while (!sin.eof())
			{
				getline(sin, field, ',');//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
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
				getline(sin, field, ',');//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符 
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
//遍历且记录路径点小于等于10且能到达目的点的路径
void DFS(int start, int end, int path[10000][11], Graph& g, int& pathID, Stack& Stack, bool* visited)//深搜入栈查询所有路径
{
	visited[start] = true;//visited数组存储各定点的遍历情况，true为已遍历（标记）
	Stack.Push(start);//入栈
	if (Stack.top == 11)//超过10个结点
	{
		Stack.Pop();
		visited[start] = false;
		return;
	}
	for (int j = 0; j < 34; j++)
	{
		if (start == end) //找到终点
		{
			for (int i = 0; i < Stack.top; i++)
			{
				path[pathID][i] = Stack.data[i];
			}
			pathID++;
			Stack.Pop();//出栈
			visited[start] = false;
			break;
		}
		if (!visited[j] && (g.Edge[start][j] > 0 && g.Edge[start][j] < 9999))//该顶点未被访问过且此顶点可以邻结出去
		{
			DFS(j, end, path, g, pathID, Stack, visited);
		}
		if (j == 33) //如果该顶点无其它出度
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
	int n = G.Get_Vertix_num();//获取总结点数
	int w;//权重
	bool* S = new bool[n];//最短路径结点集
	for (int i = 0; i < n; i++)
	{
		dist[i] = G.GetWeight(v_pos, i);//将该结点到i结点的边存入数组
		S[i] = false;  //结点集初始化
		if (i != v_pos && dist[i] < 9999)
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
	for (int i = 0; i < n - 1; i++)
	{
		int min = 9999;
		int u = v_pos;
		for (int j = 0; j < n; j++)
		{
			if (!S[j] && dist[j] < min)
			{
				u = j; min = dist[j];//找到最短的路径
			}
		}
		S[u] = true;//将该结点放入集合S
		for (int k = 0; k < n; k++)
		{
			w = G.GetWeight(u, k);//获取u，k 之间的权重
			if (!S[k] && w < 9999 && dist[u] + w < dist[k])
			{
				dist[k] = dist[u] + w;//修改到k的权值
				path[k] = u;//修改到k的路径
			}
		}

	}
}
int Get_City_ID(string cityName, Graph& g)//获取城市在图中下表
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
//求最短路径
void Short_Path(Graph& G, string* CityList, int mode)
{
	int way_to_find;
	string Start_City_Name, End_City_Name;
	cout << "请输入开始城市" << endl;
	if (mode == 2)
		cin.ignore();
	getline(cin, Start_City_Name);
	cout << "请输入结束城市" << endl;
	getline(cin, End_City_Name);
	cout << "请选择所需用的求最短路径算法（通过对应算法前的标号选择）" << endl << "1.Floyd " << endl << "2.Dijkstra" << endl;
	cin >> way_to_find;
	while (way_to_find != 1 && way_to_find != 2)
	{
		cout << "输入错误,请重新输入" << endl;
		cin >> way_to_find;
	}
	cin.ignore();//因为前面有cin导致后面的getline直接读取了cin后的换行符号 导致其读入为空 需将此次输入忽略

	int Start_City_ID = Get_City_ID(Start_City_Name, G), End_City_ID = Get_City_ID(End_City_Name, G);

	if (mode == 2)
	{
		Print_All(Start_City_ID, End_City_ID, G);
	}
	int Path[34];//记录全部路径(倒序储存)
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
	//在第二个选择下进行文件写入
	if (mode == 2)
	{
		if (way_to_find == 1)
		{
			cout << "在Floyd下的";
		}
		else
		{
			cout << "在Djkstra下的";
		}
		cout << "路径长度为：" << lowestDis << "  路径为：";
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
	//在第三个选择下输出路径和路径长
	if (mode == 3)
	{
		cout << "路径长度为：" << lowestDis << "  路径为：";
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
//合并两个表，使其成为正常的领矩表
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
//避开某个城市选路径
void Avoid_Some_CIty(int weight[][34], Graph& G)
{
	string Avoid_City_Name;
	cout << "请输入需要绕过的城市" << endl;
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
int partition(int arr[], int start, int end)  //找基准数 划分
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
//遍历全部可行路径
void Print_All(int Start_Num, int End_Num, Graph& G)
{
	int print_all[10000][11], path_num = 0;//print_all储存全部路径
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
	int* path_length = new int[path_num], *temp = new int[path_num];//temp用来记录快排后的路径长输出顺序
	//求相应Pos路径的路径长
	for (int i = 0; i < path_num; i++)
	{
		path_length[i] = 0;
		for (int j = 0; j < 10; j++)
		{
			if (print_all[i][j + 1] != -1)
			{
				path_length[i] += G.Edge[print_all[i][j]][print_all[i][j + 1]];//加上对应路径Pos下的所有路径长
			}
		}
	}
	for (int i = 0; i < path_num; i++)//temp储存数组大小顺序
	{
		temp[i] = path_length[i];
	}
	quick_sort(temp, 0, path_num - 1);
	ofstream PrintFile("Path.text", ios::out);//ios::out：如果没有文件，那么生成空文件；如果有文件，清空文件
	if (!PrintFile)
	{
		cout << "打开文件失败！" << endl;
		exit(1);
	}
	for (int k = 0; k < path_num; k++)
	{
		for (int j = 0; j < path_num; j++)
		{
			if (path_length[j] == temp[k])
			{
				PrintFile << "路径长度为：" << path_length[j] << "  路径为：";
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
//求第k短路径
void Kth_Shortest_Path(string* cityname, Graph& G)
{
	int k;
	string Start_ID, End_ID;
	cout << "请输入开始城市" << endl;
	cin.ignore();
	getline(cin, Start_ID);
	cout << "请输入结束城市" << endl;
	getline(cin, End_ID);
	cout << "请输入所需要的第k短路径" << endl;
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
	int* Length_of_Path = new int[path_num], *temp = new int[path_num];//temp用来记录快排后的路径长输出顺序
	//求相应Pos路径的路径长
	for (int i = 0; i < path_num; i++)
	{
		Length_of_Path[i] = 0;
		for (int j = 0; j < 10; j++)
		{
			if (all_path[i][j + 1] != -1)
			{
				Length_of_Path[i] += G.Edge[all_path[i][j]][all_path[i][j + 1]];//加上对应路径Pos下的所有路径长
			}
		}
	}
	for (int i = 0; i < path_num; i++)
	{
		temp[i] = Length_of_Path[i];
	}
	quick_sort(temp, 0, path_num - 1);
	cout << "从" << Start_ID << "到" << End_ID << "的第" << k << "短路径长度是:" << temp[k - 1] << endl;
	cout << "路径是:";
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
	cout << "请输入所需实现功能:" << endl;
	cout << "1.两跳内是否到武汉判断" << endl;
	cout << "2.求解最短路径" << endl;
	cout << "3.求解最短路径(绕开某个城市)" << endl;
	cout << "4.求城市间的第k短路径" << endl;
	cout << "其他.退出" << endl;
	cout << "------------------------------------------------------------" << endl;
}
void Func_one()
{
	string cityname[34];
	int neighboor[34][34];
	Read_File(neighboor, cityname, 1);
	int weight[34][34];
	Read_File(weight, cityname, 2);
	for (int i = 0; i < 34; i++)//补全路径长度不全的地方
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
	desID = Get_City_ID("武汉", G);
	Dijkstra(G, G.city[desID], desDist, desPath);
	for (int i = 0; i < 34; i++)
	{
		if (desDist[i] > 3)
		{
			cout << "全国到武汉的城市（省会）的中间超过2个" << endl;
			break;
		}
	}
	cout << "全国到武汉的城市（省会）的中间不超过2个" << endl;
}
void Func_two()
{
	string cityname[34];
	int neighboor[34][34];
	Read_File(neighboor, cityname, 1);
	int weight[34][34];
	Read_File(weight, cityname, 2);
	for (int i = 0; i < 34; i++)//补全路径长度不全的地方
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
	cout << "写入成功" << endl;
}
void Func_three()
{
	string cityname[34];
	int neighboor[34][34];
	Read_File(neighboor, cityname, 1);
	int weight[34][34];
	Read_File(weight, cityname, 2);
	for (int i = 0; i < 34; i++)//补全路径长度不全的地方
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
	for (int i = 0; i < 34; i++)//补全路径长度不全的地方
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