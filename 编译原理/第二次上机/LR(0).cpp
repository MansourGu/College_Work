#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <utility>
#include <iomanip>
#include<vector>
using namespace std;

//����s�ĵ�һ����
string firstWord(string s)
{
	s += " ";
	string first = s.substr(0, s.find(" "));
	return first;
}

//���ַ�������Ϊһ������
vector<string> Partition(string s, string separator)
{
	vector<string>v;

	string::size_type pos1, pos2;
	pos2 = s.find(separator);
	pos1 = 0;

	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + separator.size();
		pos2 = s.find(separator, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));

	return v;
}
class Item//��Ŀ
{
private:
	string item;//��Ŀ
	string left;//��
	string right;//�в�
	static int count;//�Ƶ�����

public:
	int id;//���

	Item(string i)
	{
		id = count++;
		left = i.substr(0, i.find("->"));
		right = i.substr(i.find("->") + 2);
		item = left + "->" + right;

		if (right.find(".") == string::npos)
			addDot(0);
	}

	Item(string l, string r)
	{
		id = count++;
		left = l;
		right = r;
		item = left + "->" + right;

		if (right.find(".") == string::npos)
			addDot(0);
	}

	string getLeft()
	{
		return left;
	}

	string getRight()
	{
		return right;
	}

	string getItem()
	{
		item = left + "->" + right;
		return item;
	}

	//�ҵ��λ��
	int getDot(string item)
	{
		return item.find(".");
	}

	//���ķ��ӵ�
	void addDot(int pos)
	{
		if (right[pos] == '@')
			right = ".";
		else if (pos == 0)
			right.insert(pos, ". ");
		else if (pos == right.size())
			right.insert(pos, " .");
		else
			right.insert(pos, " . ");
	}

	//�ж�һ����Ŀ�����Ƿ񵽽�β
	int hasNextDot()
	{
		vector<string>buffer = Partition(right, ".");
		if (buffer.size() > 1)
			return 1;
		else
			return 0;
	}

	//�õ�"."�����һ���ķ�����
	string getPath()
	{
		vector<string>buffer = Partition(item, ".");
		buffer[1].erase(0, 1);
		string first = firstWord(buffer[1]);
		return first;
	}

	//������һ����Ĵ�
	string nextDot()
	{
		int dotPos = right.find(".");
		vector<string>buffer = Partition(item, ".");
		buffer[1].erase(0, 1);
		string first = firstWord(buffer[1]);
		int nextPos = dotPos + first.size();
		right.erase(right.find("."), 2);
		right.insert(nextPos, " .");
		return right;
	}

	bool operator ==(Item &x)
	{
		return getItem() == x.getItem();
	}
};
int Item::count = 0;

//ת������
struct GOTO
{
	int from;//��ʱ״̬
	int to;//ȥ����״̬
	string path;//�����ĸ��ַ�

	GOTO(int s, string p, int t)
	{
		from = s;
		path = p;
		to = t;
	}
};
//DFA��״̬
struct State
{
	int id;//״̬���
	set<Item>items;//��Ŀ��
};

bool operator <(const State &x, const State &y)
{

	return x.id < y.id;
}

bool operator <(const Item &x, const Item &y)
{

	return x.id < y.id;
}

bool operator ==(const set<Item> &x, const set<Item> &y)
{
	auto it1 = x.begin();
	auto it2 = y.begin();

	for (; it1 != x.end(), it2 != y.end(); it1++, it2++)
	{
		Item a = *it1;
		Item b = *it2;
		if (a == b)
			continue;

		//��һ����Ŀ����ȣ�����Ŀ��һ�������
		else
			return false;
	}
	return true;
}

class Grammar//�ķ�
{
private:
	int number = 0;
	vector<string>T;//�ս���ż���
	vector<string>NT;//���ս���ż���
	string S;//��ʼ����
	map<string, vector<string>>production;//����ʽ
	map<string, int>numPro;//��ŵĲ���ʽ���ϣ����ڹ�Լ
	set<State>States;//״̬����
	vector<GOTO>GO;//ת������
	map<pair<int, string>, string>actionTable;//action��
	map<pair<int, string>, int>gotoTable;//goto��

	//��ȡ�ķ�����
	void readGrammar(string fileName)
	{
		ifstream input(fileName);
		if (!input)
		{
			cout << fileName << " Failed" << endl;
		}

		//��ȡ�ķ�����
		string line;//�����ÿһ��
		while (getline(input, line))
		{
			int i;

			//��ȡ��
			string left = "";
			for (i = 0; line[i] != '-'&&i < line.size(); i++)
			{
				left += line[i];
			}

			NT.push_back(left);//�󲿼�����ս���ż�

		
			string right = line.substr(i + 2, line.size() - i);//��ȡ����ʽ�Ҳ�
			addP(left, right);//��Ӳ���ʽ
		}
		addT();//����ռ���
		S = *NT.begin();
		input.close();
	}

	//�����ʽ
	void addP(string left, string right)
	{
		right += "#";//'#'��Ϊÿ���ķ���β��־
		string pRight = "";
		for (int i = 0; i < right.size(); i++)
		{
			if (right[i] == '|' || right[i] == '#')
			{
				production[left].push_back(pRight);
				pRight = "";
			}
			else
			{
				pRight += right[i];
			}
		}
	}

	//����ŵĲ���ʽ��
	void addNumP()
	{
		int i = 0;
		for (string left : NT)
		{
			for (string right : production[left])
			{
				numPro[left + "->" + right] = i;
				i++;
			}
		}

		//        for(auto it=numPro.begin();it!=numPro.end();it++)
		//            cout<<it->first<<"\t"<<it->second<<endl;
	}

	//���ս��
	void addT()
	{
		string temp = "";
		for (string left : NT)
		{
			for (string right : production[left])
			{
				right += "#";
				for (int i = 0; i < right.size(); i++)
				{
					if (right[i] == '|' || right[i] == ' ' || right[i] == '#')
					{
						//���Ƿ��սᣬ�Ҳ��ǿգ�������ս����
						if ((find(NT.begin(), NT.end(), temp) == NT.end()) && temp != "@")
						{
							T.push_back(temp);
						}
						temp = "";
					}
					else
					{
						temp += right[i];
					}
				}
			}
		}

		//�ս��ȥ��
		sort(T.begin(), T.end());
		T.erase(unique(T.begin(), T.end()), T.end());
	}
	//�ж��Ƿ��Ƿ��ռ�����
	bool isNT(string token)
	{
		if (find(NT.begin(), NT.end(), token) != NT.end())
			return true;
		return false;
	}
	//�ж��Ƿ�Ӧ�ù�Լ
	bool tableReduce(int num)
	{
		for (State s : States)
		{
			//Ŀ��״̬
			if (s.id == num)
			{
				//cout<<s.id<<"\t"<<s.items.size()<<"*"<<endl;
				//��Լ��Ŀ�϶�ֻ��һ��
				if (s.items.size() > 1)
					return 0;

				//������Ŀ��
				for (Item i : s.items)
				{
					//cout<<num<<"\t ���� "<<i.getItem();
					if (i.hasNextDot())
						return 0;
					else
						return 1;
				}
			}
		}
		return -1;
	}

	//�ҵ�item��Լ���Ĳ���ʽ����������
	int findReduce(int num)
	{
		for (State s : States)
		{
			if (s.id == num)
			{
				for (Item i : s.items)
				{
					string temp = i.getItem();
					temp.erase(temp.find("."));
					temp.pop_back();
					return numPro.find(temp)->second;
				}
			}
		}
		return -1;
	}

	//�ҵ�����ʽ���Ϊpro�Ĳ���ʽ
	int rightCount(string &left, int pro)
	{
		for (auto it = numPro.begin(); it != numPro.end(); it++)
		{
			if (it->second == pro)
			{
				cout << it->first << endl;
				string target = it->first;
				left = target.substr(0, target.find("->"));
				string right = target.substr(target.find("->") + 2);
				vector<string>temp = Partition(right, " ");
				return temp.size();
			}
		}
		return 0;
	}
public:
	//���캯���������������Ԫ��
	Grammar(string fileName)
	{
		readGrammar(fileName);
		Extension();//�ع��ķ�
	}

	//�ع��ķ�
	void Extension()
	{
		string newS = S;
		newS += "'";
		NT.insert(NT.begin(), newS);
		production[newS].push_back(S);
		S = newS;
	}

	//״̬���Ƿ��Ѿ�������״̬
	int hasState(set<Item>J)
	{
		for (State s : States)
		{
			if (s.items.size() != J.size())
				continue;

			if (s.items == J)
				return s.id;
			else
				continue;

		}
		return -1;
	}

	//��Ŀ�հ�
	set<Item> closure(Item item)
	{
		set<Item>C;//��Ŀ�հ�
		C.insert(item);

		vector<string>buffer = Partition(item.getRight(), ".");

		if (buffer.size() > 1)
		{
			string first = firstWord(buffer[1].erase(0, 1));

			if (isNT(first))//���"."�����һ���ַ���NT
			{
				for (auto it2 = production[first].begin(); it2 != production[first].end(); it2++)
				{
					Item temp(first, *it2);
					C.insert(temp);
				}
			}
		}
		return C;
	}

	//����DFA
	void Construct_DFA()
	{
		State s0;//��ʼ��Ŀ��
		s0.id = number++;//״̬���

		//��ʼ��Ŀ��
		string firstRight = *(production[S].begin());
		Item start(S, firstRight);
		s0.items = closure(start);//�ӵ�״̬��
		States.insert(s0);

		//����DFA
		for (State s : States)
		{
			for (Item now : s.items)
			{
				now.getItem();
				if (now.hasNextDot())
				{
					string path = now.getPath();//path
					Item nextD(now.getLeft(), now.nextDot());
					set<Item>next = closure(nextD);//to

					//�����״̬��״̬����û�г��ֹ����ͼ���״̬��
					//printI(next);
					if (hasState(next) == -1)
					{
						State t;
						t.id = number++;
						t.items = next;
						States.insert(t);
						GO.push_back(GOTO(s.id, path, t.id));
					}
					//��״̬�Ѿ���״̬������
					else
					{
						int tID = hasState(next);
						GO.push_back(GOTO(s.id, path, tID));
					}
				}
			}
		}
		printS();
		printGO();
	}

	//����LR(0)������
	void LRtable()
	{
		addNumP();
		string s = S;
		s = s.erase(s.find("'"));

		for (GOTO go : GO)
		{
			//Ŀ�ĵ���NT
			if (isNT(go.path))
			{
				if (go.path == s)
				{
					pair<int, string>title(go.to, "$");
					actionTable[title] = "acc";
				}

				pair<int, string>title(go.from, go.path);
				gotoTable[title] = go.to;

			}
			//����action��
			else
			{
				//shift
				pair<int, string>title(go.from, go.path);
				actionTable[title] = "s" + to_string(go.to);
			}
			//reduce
			if (tableReduce(go.to))
			{
				if (go.path != s)
				{
					vector<string>x = T;
					x.push_back("$");

					for (string p : x)
					{
						pair<int, string>title(go.to, p);
						actionTable[title] = "r" + to_string(findReduce(go.to));
					}
				}
			}
		}
		printTable();
	}

	//�﷨��������
	int parsing(string input)
	{
		stack<string>Analysis;
		input += " $";

		//0״̬��ջ
		Analysis.push("$");
		Analysis.push("0");

		vector<string>w = Partition(input, " ");//�����봮�ֳ�һ������
		int ip = 0;//���봮��ָ��

		while (true)
		{
			pair<int, string>title(stoi(Analysis.top()), w[ip]);//stoi��������string to int
			string res = actionTable[title];
			cout << "ջ����s" << setw(10) << Analysis.top() << "��ǰ�����ַ���" << setw(8) << w[ip];

			//shift
			if (res[0] == 's')
			{
				cout << "������shift" << endl;
				int state = stoi(res.substr(1));
				Analysis.push(w[ip]);
				Analysis.push(to_string(state));
				ip++;
			}
			//reduce
			else if (res[0] == 'r')
			{
				cout << "������reduce ";
				int pro = stoi(res.substr(1));
				string left;//����ʽ��
				int b = 2 * rightCount(left, pro);//2���Ĳ���ʽ�Ҳ���������

				while (b > 0)
				{
					Analysis.pop();
					b--;
				}

				int s1 = stoi(Analysis.top());
				Analysis.push(left);

				pair<int, string>t(s1, left);
				Analysis.push(to_string(gotoTable[t]));
			}
			else if (res[0] == 'a')
			{
				cout << "����������" << endl;
				return 1;
			}

			else
			{
				cout << "�ķ�����" << endl;
				return 0;
			}
		}
	}

	void parser(string fileName)
	{
		ifstream input(fileName);
		if (!input)
		{
			cout << fileName << " Failed" << endl;
			return;
		}

		Construct_DFA();
		LRtable();

		//��ȡtoken
		char c;
		string program = "";
		int line = 1;
		cout << "Դ�����token����Ϊ" << endl;
		cout << line << "  ";
		while ((c = input.get()) != EOF)
		{
			cout << c;
			if (c == '\n')
			{
				cout << ++line << "  ";
				program += " ";
			}
			else
				program += c;
		}
		cout << endl;


		cout << "���������" << endl;

		if (parsing(program))
			cout << endl << "*********************���봮���ڸ��ķ�*********************" << endl;
		else
			cout << endl << "********************���봮�����ڸ��ķ�********************" << endl;;

	}
	/*=====================��ӡ===========================*/
	//��ӡNT��T
	void printV()
	{
		cout << "���ս���ż��ϣ�" << endl;
		for (int i = 0; i < NT.size(); i++)
		{
			cout << NT[i] << " ";
		}
		cout << endl;
		cout << "�ս���ż��ϣ�" << endl;
		for (int i = 0; i < T.size(); i++)
		{
			cout << T[i] << " ";
		}
		cout << endl;
	}

	//��ӡ������
	void printTable()
	{
		cout << "LR(0)������" << endl;

		vector<string>x = T;//��������ս���ż���
		x.push_back("$");

		//���������
		cout << "****************action****************" << endl;
		cout.setf(ios::left);
		for (auto it1 = x.begin(); it1 != x.end(); it1++)
		{
			if (it1 == x.begin())
				cout << setw(10) << " ";
			cout << setw(8) << *it1;
		}
		cout << endl;

		for (int i = 0; i < States.size(); i++)
		{
			cout << setw(10) << i;

			for (string t : x)
			{
				//cout<<i<<"ttt"<<endl;

				if (!actionTable.empty())
				{
					pair<int, string>title(i, t);
					cout << setw(8) << actionTable[title];
				}

				else
					cout << setw(8);
			}
			cout << endl;
		}
		cout << endl;

		/*��ӡGOTO��*/
		vector<string>y = NT;//����S���ķ��ս���ż���
		y.erase(y.begin());

		cout << "****************goto******************" << endl;
		cout.setf(ios::left);

		for (auto it1 = y.begin(); it1 != y.end(); it1++)
		{
			if (it1 == y.begin())
				cout << setw(10) << "";

			cout << setw(8) << *it1;
		}
		cout << endl;

		for (int i = 0; i < States.size(); i++)
		{
			cout << setw(10) << i;

			for (string t : y)
			{
				pair<int, string>title(i, t);

				if (gotoTable[title] != 0)
				{
					cout << setw(8) << gotoTable[title];
				}
				else
					cout << setw(8) << "";
			}
			cout << endl;
		}

		cout << endl << "LR(0)�����������" << endl << endl;
	}


	//��ӡ����ʽ
	void printP()
	{
		cout << "�﷨�Ĳ���ʽΪ" << endl;
		for (string left : NT)
		{
			cout << left << "->";
			for (auto it = production[left].begin(); it != production[left].end(); it++)
			{
				if (it != production[left].end() - 1)
					cout << *it << "|";
				else
					cout << *it << endl;
			}
		}
		cout << endl;
	}

	//��ӡ״̬��
	void printS()
	{
		cout << "**********״̬����Ϊ**********" << endl;
		for (State s : States)
		{
			cout << "״̬��ţ�" << s.id << endl;
			printI(s.items);
		}
		cout << endl;
	}

	//��ӡ״̬ת�ƺ���
	void printGO()
	{
		cout << "**********״̬ת�ƺ���Ϊ**********" << endl;
		for (GOTO go : GO)
		{
			cout << go.from << "---" << go.path << "-->" << go.to << endl;
		}
		cout << endl;
	}

	//��ӡ��Ŀ��
	void printI(set<Item>I)
	{
		cout << "LR(0)����Ŀ��Ϊ" << endl;
		for (Item i : I)
		{
			cout << i.getItem() << endl;
		}
		cout << endl;
	}
};
int main()
{
	string filename = "Grammer.txt";
	Grammar G(filename);
	G.printP();//�������ʽ
	G.parser("Tokens.txt");
	system("pause");
	return 0;
}