#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<string>
#include<stack>
#include<algorithm>
#include<easyx.h>
using namespace std;
struct Node_A_star //A*
{
	int f;//
	int g;//起始节点到当前节点值
	int h;//当前节点到目标节点的估计值
	int name;
	Node_A_star(int name, int h, int g)
	{
		this->name = name;
		this->g = g;
		this->h = h;
		this->f = g + h;
	}
	bool operator < (const Node_A_star & a)const
	{
		return (f < a.f);
	}
};
struct Node_UCS // UCS 结点
{
	int cost;
	int name;
	int parent;
	Node_UCS(int n, int c)
	{
		this->name = n;
		this->cost = c;
	}
	bool operator < (const Node_UCS & a)const
	{
		return (cost < a.cost);
	}
};
struct Map_coord //图形化界面地图坐标
{
	int x;
	int y;
	Map_coord(int x_, int y_)
	{
		x = x_;
		y = y_;
	}
	Map_coord() {}

};
int Dest = 1;//目的地
int City_Map[20][20];//邻接矩阵存放地图信息
int Greedy[20] = { 366,0,166,242,161,176,77,151,226,244,241,234,380,10,193,253,329,80,199,374 };//启发式信息
bool check_close[20];//A* 闭表
bool check_open[20];//A* 检查开表
bool check_explored[20];//以探索节点
int parent[20];//记录父亲位置的指针
vector<Node_UCS> Frontier;//UCS优先级队列
vector<string>City_Name;//存放城市名字
vector<Node_A_star> open_list;//A* 开表
vector<Map_coord> Coordinates;//图形化界面坐标
void Initial_City_Map(string s ,int k)//i 初始化矩阵
{	
	string temp = "";
	int count = -1;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\t')
		{
			if (count == -1)
			{
				temp = "";
				count++;
				continue;
			}
			else if (temp == "\t")
			{
				temp = "";
				continue;
			}
			else
			{
				City_Map[k][count] = atoi(temp.c_str());
				temp = "";
				count++;
				continue;
			}
		}
		temp += s[i];
		if (i == s.size() - 1)
		{
			City_Map[k][count] = atoi(temp.c_str());
		}
	}
}
void Initial_City_Name(string s)
{
	string temp = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\t')
		{
		    if (temp == "\t")
			{
				temp = "";
				continue;
			}
			if (temp == "")
			{
				continue;
			}
			else
			{
				City_Name.push_back(temp);
				temp = "";
				continue;
			}
		}
		temp += s[i];
		if (i == s.size() - 1)
		{
			City_Name.push_back(temp);
		}
	}
}
void Partition(string s)
{
	string temp = "";
	Map_coord v;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
		{
			if (temp == " ")
			{
				temp = "";
				continue;
			}
			if (temp == "")
			{
				continue;
			}
			else
			{
				v.x = atoi(temp.c_str());
				temp = "";
				continue;
			}
		}
		temp += s[i];
		if (i == s.size() - 1)
		{
			v.y = atoi(temp.c_str());
			Coordinates.push_back(v);
		}

	}
}
void Read_Coordinates()
{
	fstream fin;
	fin.open("coordinate.txt");
	string s;
	while (getline(fin, s))
	{
		Partition(s);
	}
}
void Read_File()//读取文件信息
{	
	fstream fin;
	fin.open("map.txt");
	string s;
	int count = -1;
	while (getline(fin,s))
	{
		if (count == -1)//不要第一行元素
		{
			Initial_City_Name(s); 
			count++;
			continue;	
		}
		Initial_City_Map(s, count);
		count++;
	}
} 
void Signify_Vertix(int i ,int mode)
{
	if (mode ==1)
	{
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 5);
	}
	if (mode ==2)
	{
		setlinecolor(GREEN);
		setlinestyle(PS_SOLID, 5);
	}
	Map_coord v = Coordinates[i];
	circle(v.x, v.y, 10);
}
void Line_Vertix(int s, int e ,int mode)
{
	if (mode == 1)
	{
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 5);
	}
	if (mode == 2)
	{
		setlinecolor(GREEN);
		setlinestyle(PS_SOLID, 5);
	}
	Map_coord start = Coordinates[s];
	Map_coord end = Coordinates[e];
	line(start.x, start.y, end.x, end.y);
}
void Initial_Graph()
{
	initgraph(824, 480);
	IMAGE map;
	loadimage(&map, _T("1.png"));
	putimage(0, 0, &map);
	Read_Coordinates();
}
int Find_Next(int start)//对于贪婪算法而言找到最下一个节点
{
	vector<int>neighbor;
	for (int i = 0; i < 20; i++)
	{
		if (City_Map[start][i]>0 && City_Map[start][i] <1000)
		{
			neighbor.push_back(i);
			Signify_Vertix(i ,1);
		}
	}
	int min = 1000 , min_pos;
	for (int i = 0; i < neighbor.size(); i++)
	{
		if (Greedy[neighbor[i]] < min)
		{
			min = Greedy[neighbor[i]];
			min_pos = neighbor[i];
		}
	}
	return min_pos;

}
void Greedy_Best_Search(int start, vector<int> &temp)
{
	if (start == Dest)
	{
		return;
	}
	else
	{
		int next = Find_Next(start);
		Sleep(2000);
		Signify_Vertix(next , 2);
		Line_Vertix(start, next , 2);
		temp.push_back(next);
		Greedy_Best_Search(next,temp);
	}
}
void A_star(Node_A_star & n)
{
	for (int i = 0; i < 20; i++)
	{
		parent[i] = -1;
	}
	for (int i = 0; i < 20; i++)
	{
		check_open[i] = false;
		check_close[i] = false;
	}
	open_list.push_back(n);
	sort(open_list.begin(), open_list.end());
	while (!open_list.empty())
	{
		/*取代价最小的节点*/
		Node_A_star current = open_list [0];                     //取首节点，代价最小
		if (current.name == Dest)                       //目标
			return;
		open_list.erase(open_list.begin());           //从openlist序列中删除这个节点
		check_open[current.name] = false;                     //将当前节点标记为不在openList中
		check_close[current.name] = true;                 //将当前节点加入closeList

		/*遍历子节点*/
		for (int i = 0; i < 20; i++)
		{
			
			if (City_Map[current.name][i] >0 && City_Map[current.name][i]<1000 && !check_close[i])      //节点相邻并且不在close中，可访问
			{
				Signify_Vertix(i , 1);
				Sleep(2000);
				if (check_open[i])                                            //如果在list序列中，说明属于扩展节点集
				{
					int j = 0;
					for (int j = 0; j < open_list.size(); j++) {              //遍历，找到当前节点的位置
						if (open_list[j].name == i)  break;
					}
					/*刷新节点*/
					int cost = current.g + City_Map[current.name][i];
					if (cost < open_list[j].g)
					{
						Line_Vertix(current.name, i , 1);
						open_list[j].g = cost;                           //更新g
						open_list[j].f = cost + open_list[j].h;           //更新f
						parent[i] = current.name;                           //更新parent
					}
				}
				else                                                    //节点不在openList，则创建一个新点，加入openList扩展集
				{
					Node_A_star newNode(i, current.g + City_Map[current.name][i], Greedy[i]);
					Line_Vertix(current.name, i, 1);
					if (parent[i]!=-1)
					{
						Line_Vertix(parent[i], current.name, 1);
					}
					parent[i] = current.name;
					open_list.push_back(newNode);
					sort(open_list.begin(), open_list.end());             //排序
					check_open[i] = true;
				}
			}
		}
	}
}
void Out_Put(vector<int>&record)
{
	int p = open_list[0].name;
	record.push_back(p);
	while (parent[p] != -1)
	{
		record.push_back(parent[p]);
		p = parent[p];
	}
	return;
}
int Find_Pos(int n)
{
	for (int i = 0; i < Frontier.size(); i++)
	{
		if (n == Frontier[i].name)
		{
			return i;
		}
	}
	return -1; 
}
void UCS(Node_UCS & n , vector<int>&record)
{
	for (int i = 0; i < 20; i++)
	{
		parent[i] = -1;
	}
	for (int i = 0; i < 20; i++)
	{
		check_explored[i] = false;
	}
	Frontier.push_back(n);
	int cost = 0;
	check_explored[n.name] = true;
	sort(Frontier.begin(), Frontier.end());
	while (!Frontier.empty())
	{
		sort(Frontier.begin(), Frontier.end());
		Node_UCS  current = Frontier[0];//取出列表头元素
		cost = current.cost;
		record.push_back(current.name);
		if (current.name == Dest)//如果与目标相同结束
		{
			return;
		}
		Frontier.erase(Frontier.begin());//删除头结点
		for (int i = 0; i < 20; i++)//遍历子节点
		{
			if (City_Map[current.name][i] > 0 && City_Map[current.name][i] < 1000 && !check_explored[i] && Find_Pos(i) == -1 ) // 找到相邻且未经探索的节点并且没有在队列中
			{
				Node_UCS insert(i, cost + City_Map[current.name][i]);
				Frontier.push_back(insert);//将其放入列表
				Signify_Vertix(i, 1);
				Line_Vertix(current.name, i, 1);
				Sleep(2000);
				check_explored[i] = true;
				parent[i] = current.name;
			}
			if (City_Map[current.name][i] > 0 && City_Map[current.name][i] < 1000  && Find_Pos(i) != -1)// 找到相邻且未经探索的节点并且在队列中用小的代价值替代高的代价值
			{
				int temp = Find_Pos(i);
				if (City_Map[current.name][i]+cost < Frontier[temp].cost)
				{
					Node_UCS takeplace(i, City_Map[current.name][i] + cost);
					Signify_Vertix(i, 1);
					Line_Vertix(current.name, i, 1);
					Sleep(2000);
					Frontier[temp] = takeplace;
					parent[i] = current.name;
					
				}
				check_explored[i] = true;
			}
		}
	}
}
void Menu()
{
	int start = 0;
	vector<int>record_greed;
	vector<int>record_A_star;
	vector<int>record_ucs;
	cout << "请选择搜索方式： 1、贪婪算法 2、A* 3、代价一致搜索";
	int mode;
	cin >> mode;
	Initial_Graph();
	system("pause");
	Signify_Vertix(start ,2);
	switch (mode)
	{
	case 1:
	{
		record_greed.push_back(start);
	    Greedy_Best_Search(start, record_greed);
		break;
	}
	case 2:
	{
		Node_A_star s(start, 0, Greedy[start]);
		A_star(s);
		Out_Put(record_A_star);
		for (int i = 0; i < record_A_star.size()-1; i++)
		{
			Line_Vertix(record_A_star[i], record_A_star[i + 1] ,2);
			Signify_Vertix(record_A_star[i], 2);
			Signify_Vertix(record_A_star[i+1], 2);
		}
		break;
	}
	case 3:
	{
		Node_UCS u_s(start, 0);
		UCS(u_s, record_ucs);
		int p = Dest;
		vector<int>re;
		while (p !=-1)
		{
		re.push_back(p);
		p = parent[p];
		}
		for (int i = 0; i < re.size()-1; i++)
		{
			Line_Vertix(re[i], re[i + 1], 2);
			Signify_Vertix(re[i], 2);
			Signify_Vertix(re[i + 1], 2);
		}
		break;
	}
	default:
		break;
	}
	system("pause");
	closegraph();
	system("cls");
	Menu();
}
int main()
{
	Read_File();
	Read_Coordinates();
	Menu();

	system("pause"); 
	return 0;
}
