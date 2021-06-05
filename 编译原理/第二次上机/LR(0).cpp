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

//返回s的第一个词
string firstWord(string s)
{
	s += " ";
	string first = s.substr(0, s.find(" "));
	return first;
}

//将字符串划分为一个个词
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
class Item//项目
{
private:
	string item;//项目
	string left;//左部
	string right;//有部
	static int count;//推导次数

public:
	int id;//编号

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

	//找点的位置
	int getDot(string item)
	{
		return item.find(".");
	}

	//给文法加点
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

	//判断一个项目进度是否到结尾
	int hasNextDot()
	{
		vector<string>buffer = Partition(right, ".");
		if (buffer.size() > 1)
			return 1;
		else
			return 0;
	}

	//得到"."后面的一个文法符号
	string getPath()
	{
		vector<string>buffer = Partition(item, ".");
		buffer[1].erase(0, 1);
		string first = firstWord(buffer[1]);
		return first;
	}

	//返回下一个点的串
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

//转换函数
struct GOTO
{
	int from;//来时状态
	int to;//去往的状态
	string path;//经过哪个字符

	GOTO(int s, string p, int t)
	{
		from = s;
		path = p;
		to = t;
	}
};
//DFA中状态
struct State
{
	int id;//状态编号
	set<Item>items;//项目集
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

		//有一个项目不相等，两项目集一定不相等
		else
			return false;
	}
	return true;
}

class Grammar//文法
{
private:
	int number = 0;
	vector<string>T;//终结符号集合
	vector<string>NT;//非终结符号集合
	string S;//开始符号
	map<string, vector<string>>production;//产生式
	map<string, int>numPro;//编号的产生式集合，用于规约
	set<State>States;//状态集合
	vector<GOTO>GO;//转换函数
	map<pair<int, string>, string>actionTable;//action表
	map<pair<int, string>, int>gotoTable;//goto表

	//读取文法规则
	void readGrammar(string fileName)
	{
		ifstream input(fileName);
		if (!input)
		{
			cout << fileName << " Failed" << endl;
		}

		//读取文法规则
		string line;//读入的每一行
		while (getline(input, line))
		{
			int i;

			//读取左部
			string left = "";
			for (i = 0; line[i] != '-'&&i < line.size(); i++)
			{
				left += line[i];
			}

			NT.push_back(left);//左部加入非终结符号集

		
			string right = line.substr(i + 2, line.size() - i);//获取产生式右部
			addP(left, right);//添加产生式
		}
		addT();//添加终极符
		S = *NT.begin();
		input.close();
	}

	//填产生式
	void addP(string left, string right)
	{
		right += "#";//'#'作为每句文法结尾标志
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

	//带标号的产生式集
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

	//填终结符
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
						//不是非终结，且不是空，则加入终结符号
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

		//终结符去重
		sort(T.begin(), T.end());
		T.erase(unique(T.begin(), T.end()), T.end());
	}
	//判断是否是非终极符号
	bool isNT(string token)
	{
		if (find(NT.begin(), NT.end(), token) != NT.end())
			return true;
		return false;
	}
	//判断是否应该规约
	bool tableReduce(int num)
	{
		for (State s : States)
		{
			//目标状态
			if (s.id == num)
			{
				//cout<<s.id<<"\t"<<s.items.size()<<"*"<<endl;
				//规约项目肯定只有一个
				if (s.items.size() > 1)
					return 0;

				//遍历项目集
				for (Item i : s.items)
				{
					//cout<<num<<"\t 待定 "<<i.getItem();
					if (i.hasNextDot())
						return 0;
					else
						return 1;
				}
			}
		}
		return -1;
	}

	//找到item规约到的产生式，返回其编号
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

	//找到产生式序号为pro的产生式
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
	//构造函数，读入所需的四元组
	Grammar(string fileName)
	{
		readGrammar(fileName);
		Extension();//拓广文法
	}

	//拓广文法
	void Extension()
	{
		string newS = S;
		newS += "'";
		NT.insert(NT.begin(), newS);
		production[newS].push_back(S);
		S = newS;
	}

	//状态集是否已经包含该状态
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

	//项目闭包
	set<Item> closure(Item item)
	{
		set<Item>C;//项目闭包
		C.insert(item);

		vector<string>buffer = Partition(item.getRight(), ".");

		if (buffer.size() > 1)
		{
			string first = firstWord(buffer[1].erase(0, 1));

			if (isNT(first))//如果"."后面第一个字符是NT
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

	//构造DFA
	void Construct_DFA()
	{
		State s0;//初始项目集
		s0.id = number++;//状态序号

		//初始项目集
		string firstRight = *(production[S].begin());
		Item start(S, firstRight);
		s0.items = closure(start);//加到状态中
		States.insert(s0);

		//构建DFA
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

					//如果该状态在状态集里没有出现过，就加入状态集
					//printI(next);
					if (hasState(next) == -1)
					{
						State t;
						t.id = number++;
						t.items = next;
						States.insert(t);
						GO.push_back(GOTO(s.id, path, t.id));
					}
					//该状态已经在状态集中了
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

	//构造LR(0)分析表
	void LRtable()
	{
		addNumP();
		string s = S;
		s = s.erase(s.find("'"));

		for (GOTO go : GO)
		{
			//目的地是NT
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
			//加入action表
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

	//语法分析过程
	int parsing(string input)
	{
		stack<string>Analysis;
		input += " $";

		//0状态入栈
		Analysis.push("$");
		Analysis.push("0");

		vector<string>w = Partition(input, " ");//将输入串分成一个个词
		int ip = 0;//输入串的指针

		while (true)
		{
			pair<int, string>title(stoi(Analysis.top()), w[ip]);//stoi函数用于string to int
			string res = actionTable[title];
			cout << "栈顶：s" << setw(10) << Analysis.top() << "当前输入字符：" << setw(8) << w[ip];

			//shift
			if (res[0] == 's')
			{
				cout << "动作：shift" << endl;
				int state = stoi(res.substr(1));
				Analysis.push(w[ip]);
				Analysis.push(to_string(state));
				ip++;
			}
			//reduce
			else if (res[0] == 'r')
			{
				cout << "动作：reduce ";
				int pro = stoi(res.substr(1));
				string left;//产生式左部
				int b = 2 * rightCount(left, pro);//2倍的产生式右部符号数量

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
				cout << "动作：接受" << endl;
				return 1;
			}

			else
			{
				cout << "文法错误" << endl;
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

		//读取token
		char c;
		string program = "";
		int line = 1;
		cout << "源程序的token序列为" << endl;
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


		cout << "分析结果：" << endl;

		if (parsing(program))
			cout << endl << "*********************输入串属于该文法*********************" << endl;
		else
			cout << endl << "********************输入串不属于该文法********************" << endl;;

	}
	/*=====================打印===========================*/
	//打印NT和T
	void printV()
	{
		cout << "非终结符号集合：" << endl;
		for (int i = 0; i < NT.size(); i++)
		{
			cout << NT[i] << " ";
		}
		cout << endl;
		cout << "终结符号集合：" << endl;
		for (int i = 0; i < T.size(); i++)
		{
			cout << T[i] << " ";
		}
		cout << endl;
	}

	//打印分析表
	void printTable()
	{
		cout << "LR(0)分析表：" << endl;

		vector<string>x = T;//含界符的终结符号集合
		x.push_back("$");

		//输出表格横轴
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

		/*打印GOTO表*/
		vector<string>y = NT;//不含S’的非终结符号集合
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

		cout << endl << "LR(0)分析表构建完成" << endl << endl;
	}


	//打印产生式
	void printP()
	{
		cout << "语法的产生式为" << endl;
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

	//打印状态表
	void printS()
	{
		cout << "**********状态集合为**********" << endl;
		for (State s : States)
		{
			cout << "状态编号：" << s.id << endl;
			printI(s.items);
		}
		cout << endl;
	}

	//打印状态转移函数
	void printGO()
	{
		cout << "**********状态转移函数为**********" << endl;
		for (GOTO go : GO)
		{
			cout << go.from << "---" << go.path << "-->" << go.to << endl;
		}
		cout << endl;
	}

	//打印项目集
	void printI(set<Item>I)
	{
		cout << "LR(0)的项目集为" << endl;
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
	G.printP();//输出产生式
	G.parser("Tokens.txt");
	system("pause");
	return 0;
}