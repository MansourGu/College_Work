#include<iostream>
#include<vector>
#include<string>
using namespace std;
int count_troop = 0;
int count_cities = 0;
int count_Edge = 0;
struct Troop //����
{
	int Troop_ID;//���ӱ��
	int ID; // �����ڵ���
	int Path_Weight = 0;//�߹���·��Ȩֵ
};
struct Vertix
{
	int ID;    //�ڵ���
	int Edge_ID = -1;//���ڱߵı��
	int father = -1;//���׽ڵ�λ��
	int Weight_to_Father = -1;//�����׽ڵ��λ��
	vector<int>son;//���ӽڵ�λ��
	bool IsCritical_Vertix = false;//�Ƿ�Ϊ�� ���ڵ�
	vector<int>troop_arrive;//���ӵ���ʱ��
	bool Is_trooped = false;//�����Ƿ�פ��
	vector<int> Troop_ID;//פ�����ӵ�ID
};
vector<Vertix*>Cities_List;//�ڵ�����
vector<Vertix*>Critical_Vertix;//�ؼ��ڵ�
vector<Troop*>Troop_List;//����
vector<Vertix*>Trooped_Cities;//���о���פ���Ľڵ�
void Initial()
{
	Vertix * head = new Vertix;
	Cities_List.push_back(head);
	Vertix * root = new Vertix;
	root->ID = 1;
	Cities_List.push_back(root);
	count_cities++;
}
void Add_Cities(int father, int now, int weight)//��ӳ���
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
		Cities_List[ID]->IsCritical_Vertix = true;//�����ӵĸ�����Ψһ��ô�ýڵ�Ϊ�ؼ��ڵ㣬����ֹ�ݹ飻
		Critical_Vertix.push_back(Cities_List[ID]);
		return;
	}
	if (Cities_List[ID]->son.size() == 1 )
	{
		Cities_List[ID]->IsCritical_Vertix = true;//�����ӵĸ���Ϊһ��ô�ýڵ�Ϊ�ؼ��ڵ㣻
		Critical_Vertix.push_back(Cities_List[ID]);
		Find_Critical_Vertix(Cities_List[ID]->son[0]);
	}
}
void Find_Critical_Vertix()//Ѱ�ҹؼ��ڵ�(Ч����ߵĽڵ�)
{
	for (int i = 0; i < Cities_List[1]->son.size(); i++)
	{
		Find_Critical_Vertix(Cities_List[1]->son[i]);
	}
}
void Troop_Move(Troop *t)//�����ƶ�
{
	while (!(Cities_List[t->ID]->IsCritical_Vertix))//�������ڽڵ㲻�ǹؼ��ڵ�
	{
		t->Path_Weight += Cities_List[t->ID]->Weight_to_Father;//��¼�ƶ�ʱ��
		t->ID = Cities_List[t->ID]->father;//���׶�����Ѱ��
	}
	Cities_List[t->ID]->troop_arrive.push_back(t->Path_Weight);//�ýڵ��¼���ӵ���ʱ��
	Cities_List[t->ID]->Is_trooped = true;//���Ϊ��פ��
	Trooped_Cities.push_back(Cities_List[t->ID]);//����פ������
	Cities_List[t->ID]->Troop_ID.push_back(t->Troop_ID);//��¼פ�����ӵı��
}
int * Check()//����Ƿ�����֧·�Ĺؼ��ڵ�פ������
{	
	int* Edge_detect = new int[count_Edge];
	for (int i = 0; i < count_Edge; i++)
	{
		Edge_detect[i] = 0; //��ʼ������פ����
	}
	for (int i = 0; i < Trooped_Cities.size(); i++)
	{
		Edge_detect[Trooped_Cities[i]->Edge_ID - 1]++;
	}
	return Edge_detect;
}
int Cal_nearest_critical_cities_in_edges(int Edge_ID)//������������ĳһ��֧·�Ĺؼ�����ID
{
	for (int i = 0; i < Cities_List.size(); i++)
	{
		if (Cities_List[i]->father == 1 && Cities_List[i]->Edge_ID == Edge_ID)
		{
			return Cities_List[i]->ID;
		}
	}
}
int Cal_Path_Weight_to_father(int start_ID , int end_ID)//���㵽������֧ͬ·���м�ľ���
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
int Cal_edge_nearest_troop_cities(int Edge_ID)//�����������ϵ������ľ��ӵı��
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
int Find_Max(vector<int>&v)//����Ҫ���ӵĽڵ���ѡ���������׶���Զ��
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
int Find_Min(vector<int>&v)//�ڿ��ƶ��ľ�����ѡ�����ƶ�+���׶��ľ�����С�ľ���
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
void Army_move(int move_army , int move_cities)//�����ƶ�����
{
	for (int i = 0; i < Trooped_Cities.size(); i++)
	{
		for (int j = 0; j < Trooped_Cities[i]->Troop_ID.size(); j++)
		{
			if (Trooped_Cities[i]->Troop_ID[j] == move_army)//�ھ���֮ǰפ���ĳ���ɾ������ID
			{
				Trooped_Cities[i]->Troop_ID.erase(Trooped_Cities[i]->Troop_ID.begin() + j);
				Trooped_Cities.erase(Trooped_Cities.begin() + i);//������֮ǰ��פ���ĳ�������Ϊδפ������פ�����ӵĳ��е��б���ɾ��
				Cities_List[Troop_List[move_army]->ID]->Is_trooped = false;//������֮ǰ��פ���ĳ�������Ϊδפ��
				goto part1;
			}
		}

	}
	part1:
	Troop_List[move_army]->Path_Weight += Cal_Path_Weight_to_father(Troop_List[move_army]->ID, move_cities);//���ӵ��ƶ�ʱ��ı�
	Troop_List[move_army]->ID = move_cities;//����פ���ĳ���ID�ı�
	Cities_List[move_cities]->Is_trooped = true;//�µĳ�������Ϊ��פ��
	Cities_List[move_cities]->Troop_ID.push_back(move_army);//���µĳ������פ���ľ��ӵ�ID
	Cities_List[move_cities]->troop_arrive.push_back(Troop_List[move_army]->Path_Weight);//���פ��ʱ��
	Trooped_Cities.push_back(Cities_List[move_cities]);//����פ���б�����Ӹó���
	return;
}
void Adjust()//���нڵ㵽������֧·�Ĺؼ��ڵ����е���
{
	int * Edge_detect = Check();
	vector<int>cities_need_army;//��Ҫ���ӵĹؼ��ڵ�ID
	vector<int>cities_idle_army_ID;//�����ƶ��Ŀ��о��ӵ�ID
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
		int move_army = Find_Min(cities_idle_army_ID);//��ǰ���ƶ���Сʱ��ľ���
		int move_cities = Find_Max(cities_need_army);//��ǰ�����Զ���������פ���Ľڵ�
		Army_move(move_army, move_cities);
	}
}
void Add_Troop(int City_ID)//��Ӿ���
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
	cout << "��������и���(�������׶�)��";
	cin >> num_cities;
	cout << "�����������Ϣ �����ڵ� ����ڵ� Ȩֵ��" << endl;
	for (int i = 0; i < num_cities; i++)
	{
		int father_cities, now_cities, weight;
		cout << "�������" << i+1 << "��������Ϣ�����ڵ� ����ڵ� Ȩֵ�� �� ";
		cin >> father_cities >> now_cities >> weight;
		Add_Cities(father_cities, now_cities, weight);
	}
	int num_troop;
	cout << "��������Ӹ�����";
	cin >> num_troop;
	cout << "�����������Ϣ ��פ�����У�"<<endl;
	for (int i = 0; i < num_troop; i++)
	{
		int trooped_city;
		cout << "�������" << i+1 << "��������Ϣ ��פ�����У��� ";
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
		cout << "�����޷����ƣ���"<<endl;
		return;
	}
	Find_Critical_Vertix();
	for (int i = 0; i < Troop_List.size(); i++)
	{
		Troop_Move(Troop_List[i]);
	}
	Adjust();
	cout << "������������ʱ��Ϊ��" << Cal_result() << "hours"<<endl;
}
int main()
{
	menu();
	system("pause");
	return 0;
}