#include<iostream>
#include<vector>
#include<string>
using namespace std;
int count_troop = 0;
int count_cities = 0;
int count_Edge = 0;
struct Troop //军队
{
	int Troop_ID;//军队编号
	int ID; // 所处节点编号
	int Path_Weight = 0;//走过的路径权值
};
struct Vertix
{
	int ID;    //节点标号
	int Edge_ID = -1;//所在边的编号
	int father = -1;//父亲节点位置
	int Weight_to_Father = -1;//到父亲节点的位置
	vector<int>son;//孩子节点位置
	bool IsCritical_Vertix = false;//是否为关 键节点
	vector<int>troop_arrive;//军队到达时间
	bool Is_trooped = false;//军队是否驻扎
	vector<int> Troop_ID;//驻扎军队的ID
};
vector<Vertix*>Cities_List;//节点数组
vector<Vertix*>Critical_Vertix;//关键节点
vector<Troop*>Troop_List;//军队
vector<Vertix*>Trooped_Cities;//已有军队驻扎的节点
void Initial()
{
	Vertix * head = new Vertix;
	Cities_List.push_back(head);
	Vertix * root = new Vertix;
	root->ID = 1;
	Cities_List.push_back(root);
	count_cities++;
}
void Add_Cities(int father, int now, int weight)//添加城市
{
	Vertix * insert = new Vertix;
	insert->ID = now;
	insert->father = father;
	if (father == 1)
	{
		count_Edge++;
		insert->Edge_ID = count_Edge;
		insert->Weight_to_Father = weight;
	}
	else
	{
		insert->Edge_ID = Cities_List[father]->Edge_ID;
		insert->Weight_to_Father = weight;
	}
	Cities_List.push_back(insert);
	Cities_List[father]->son.push_back(now);
	count_cities++;
}
void Find_Critical_Vertix(int ID)
{
	if (Cities_List[ID]->son.size() > 1 || Cities_List[ID]->son.size() == 0)
	{
		Cities_List[ID]->IsCritical_Vertix = true;//若孩子的个数不唯一那么该节点为关键节点，并终止递归；
		Critical_Vertix.push_back(Cities_List[ID]);
		return;
	}
	if (Cities_List[ID]->son.size() == 1 )
	{
		Cities_List[ID]->IsCritical_Vertix = true;//若孩子的个数为一那么该节点为关键节点；
		Critical_Vertix.push_back(Cities_List[ID]);
		Find_Critical_Vertix(Cities_List[ID]->son[0]);
	}
}
void Find_Critical_Vertix()//寻找关键节点(效率最高的节点)
{
	for (int i = 0; i < Cities_List[1]->son.size(); i++)
	{
		Find_Critical_Vertix(Cities_List[1]->son[i]);
	}
}
void Troop_Move(Troop *t)//军队移动
{
	while (!(Cities_List[t->ID]->IsCritical_Vertix))//军队所在节点不是关键节点
	{
		t->Path_Weight += Cities_List[t->ID]->Weight_to_Father;//记录移动时间
		t->ID = Cities_List[t->ID]->father;//向首都方向寻找
	}
	Cities_List[t->ID]->troop_arrive.push_back(t->Path_Weight);//该节点记录军队到达时间
	Cities_List[t->ID]->Is_trooped = true;//标记为已驻扎
	Trooped_Cities.push_back(Cities_List[t->ID]);//放入驻扎城市
	Cities_List[t->ID]->Troop_ID.push_back(t->Troop_ID);//记录驻扎军队的编号
}
int * Check()//检查是否所有支路的关键节点驻扎军队
{	
	int* Edge_detect = new int[count_Edge];
	for (int i = 0; i < count_Edge; i++)
	{
		Edge_detect[i] = 0; //初始化军队驻扎数
	}
	for (int i = 0; i < Trooped_Cities.size(); i++)
	{
		Edge_detect[Trooped_Cities[i]->Edge_ID - 1]++;
	}
	return Edge_detect;
}
int Cal_nearest_critical_cities_in_edges(int Edge_ID)//计算离根最近的某一条支路的关键城市ID
{
	for (int i = 0; i < Cities_List.size(); i++)
	{
		if (Cities_List[i]->father == 1 && Cities_List[i]->Edge_ID == Edge_ID)
		{
			return Cities_List[i]->ID;
		}
	}
}
int Cal_Path_Weight_to_father(int start_ID , int end_ID)//计算到两个不同支路城市间的距离
{
	int count_path_start = 0;
	int count_path_end = 0;
	while (start_ID != 1)
	{
		count_path_start += Cities_List[start_ID]->Weight_to_Father;
		start_ID = Cities_List[start_ID]->father;
	}
	while (end_ID !=1)
	{
		count_path_end += Cities_List[end_ID]->Weight_to_Father;
		end_ID = Cities_List[end_ID]->father;
	}
	return count_path_start + count_path_end;
}
int Cal_edge_nearest_troop_cities(int Edge_ID)//计算这条边上到根最快的军队的编号
{
	int Troop_ID;
	int count_path = 999999;
	for (int i = 0; i < Troop_List.size(); i++)
	{
		if (Cities_List[Troop_List[i]->ID]->Edge_ID == Edge_ID)
		{
			if (Cal_Path_Weight_to_father(Troop_List[i]->ID,1)+Troop_List[i]->Path_Weight < count_path)
			{
				count_path = Cal_Path_Weight_to_father(Troop_List[i]->ID, 1) + Troop_List[i]->Path_Weight;
				Troop_ID = Troop_List[i]->Troop_ID;
			}
		}
	}

	return Troop_ID;
}
int Find_Max(vector<int>&v)//在需要军队的节点中选出，距离首都最远的
{
	if (v.size()==0)
	{
		return -1;
	}
	int k = 0;
	int max_id = v[0];
	int max_path = Cal_Path_Weight_to_father(Cities_List[v[0]]->ID, 1);
	for (int i = 0; i < v.size(); i++)
	{
		if (Cal_Path_Weight_to_father(Cities_List[v[0]]->ID, 1)>max_path)
		{
			max_path = Cal_Path_Weight_to_father(Cities_List[v[0]]->ID, 1);
			max_id = v[i];
		}
	}
	v.erase(v.begin() + k);
	return max_id;
}
int Find_Min(vector<int>&v)//在可移动的军队中选出已移动+到首都的距离最小的军队
{
	if (v.size() == 0)
	{
		return -1;
	}
	int min_id = v[0];
	int k = 0;
	int min_path = Cal_Path_Weight_to_father(Troop_List[v[0]]->ID, 1) + Troop_List[v[0]]->Path_Weight;
	for (int i = 0; i < v.size(); i++)
	{
		if (Cal_Path_Weight_to_father(Troop_List[v[0]]->ID, 1) < min_path)
		{
			min_path = Cal_Path_Weight_to_father(Troop_List[v[i]]->ID, 1) + Troop_List[v[i]]->Path_Weight;
			min_id = v[i];
			k = i;
		}
	}
	v.erase(v.begin() + k);
	return min_id;
}
void Army_move(int move_army , int move_cities)//调整移动军队
{
	for (int i = 0; i < Trooped_Cities.size(); i++)
	{
		for (int j = 0; j < Trooped_Cities[i]->Troop_ID.size(); j++)
		{
			if (Trooped_Cities[i]->Troop_ID[j] == move_army)//在军队之前驻扎的城市删除军队ID
			{
				Trooped_Cities[i]->Troop_ID.erase(Trooped_Cities[i]->Troop_ID.begin() + j);
				Trooped_Cities.erase(Trooped_Cities.begin() + i);//将军队之前所驻扎的城市设置为未驻扎，从驻扎军队的城市的列表中删除
				Cities_List[Troop_List[move_army]->ID]->Is_trooped = false;//将军队之前所驻扎的城市设置为未驻扎
				goto part1;
			}
		}

	}
	part1:
	Troop_List[move_army]->Path_Weight += Cal_Path_Weight_to_father(Troop_List[move_army]->ID, move_cities);//军队的移动时间改变
	Troop_List[move_army]->ID = move_cities;//军队驻扎的城市ID改变
	Cities_List[move_cities]->Is_trooped = true;//新的城市设置为已驻扎
	Cities_List[move_cities]->Troop_ID.push_back(move_army);//给新的城市添加驻扎的军队的ID
	Cities_List[move_cities]->troop_arrive.push_back(Troop_List[move_army]->Path_Weight);//添加驻扎时间
	Trooped_Cities.push_back(Cities_List[move_cities]);//在已驻扎列表中添加该城市
	return;
}
void Adjust()//所有节点到达所在支路的关键节点后进行调整
{
	int * Edge_detect = Check();
	vector<int>cities_need_army;//需要军队的关键节点ID
	vector<int>cities_idle_army_ID;//可以移动的空闲军队的ID
	for (int i = 0; i < count_Edge; i++)
	{
		if (Edge_detect[i]==0)
		{
			cities_need_army.push_back(Cal_nearest_critical_cities_in_edges(i + 1));
		}
		if (Edge_detect[i]>1)
		{
			cities_idle_army_ID.push_back(Cal_edge_nearest_troop_cities(i + 1));
		}
	}
	while (cities_need_army.size()!=0)
	{
		int move_army = Find_Min(cities_idle_army_ID);//当前已移动最小时间的军队
		int move_cities = Find_Max(cities_need_army);//当前离根最远的所需军队驻扎的节点
		Army_move(move_army, move_cities);
	}
}
void Add_Troop(int City_ID)//添加军队
{
	Troop* t = new Troop;
	t->ID = City_ID;
	t->Troop_ID = Troop_List.size();
	Troop_List.push_back(t);
	count_troop++;
}
int Cal_result()
{
	int max = -1;
	for (int i = 0; i < count_Edge; i++)
	{
		if (max < Troop_List[Cal_edge_nearest_troop_cities(i + 1)]->Path_Weight)
		{
			max = Troop_List[Cal_edge_nearest_troop_cities(i + 1)]->Path_Weight;
		}
	}
	return max;
}
void Input()
{
	int num_cities;
	cout << "请输入城市个数(不包括首都)：";
	cin >> num_cities;
	cout << "请输入城市信息 （父节点 自身节点 权值）" << endl;
	for (int i = 0; i < num_cities; i++)
	{
		int father_cities, now_cities, weight;
		cout << "请输入第" << i+1 << "个城市信息（父节点 自身节点 权值） ： ";
		cin >> father_cities >> now_cities >> weight;
		Add_Cities(father_cities, now_cities, weight);
	}
	int num_troop;
	cout << "请输入军队个数：";
	cin >> num_troop;
	cout << "请输入军队信息 （驻扎城市）"<<endl;
	for (int i = 0; i < num_troop; i++)
	{
		int trooped_city;
		cout << "请输入第" << i+1 << "个军队信息 （驻扎城市）： ";
		cin >> trooped_city;
		Add_Troop(trooped_city);
	}
}
void menu()
{
	Initial();
	/*Add_Cities(1, 2, 1);
	Add_Cities(2, 3, 2);
	Add_Cities(3, 4, 3);
	Add_Cities(3, 5, 4);
	Add_Cities(1, 6, 2);
	Add_Cities(6, 7, 3);
	Add_Cities(6, 8, 15);
	Add_Cities(1, 9, 2);
	Add_Cities(9, 10, 6);
	Add_Troop(4);
	Add_Troop(5);
	Add_Troop(8);*/
	Input();
	if (count_Edge > count_troop)
	{
		cout << "疫情无法控制！！"<<endl;
		return;
	}
	Find_Critical_Vertix();
	for (int i = 0; i < Troop_List.size(); i++)
	{
		Troop_Move(Troop_List[i]);
	}
	Adjust();
	cout << "控制疫情所需时间为：" << Cal_result() << "hours"<<endl;
}
int main()
{
	menu();
	system("pause");
	return 0;
}