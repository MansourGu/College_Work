#include <iostream>
#include <math.h>
#include <time.h>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

#define N 20  //城市节点数目
#define M 40	 //蚂蚁数量
#define DEST 1
#define START 0
int NcMax = 2000;  //最大循环次数NcMax
double alpha = 1, beta = 5, rou = 0.5, alpha1 = 0.5, qzero = 0.1;
//信息启发因子，期望启发式因子，全局信息素挥发参数，局部信息素挥发参数, 状态转移公式中的q0
double City_Map[N][N];	//矩阵表示两两城市之间的距离
vector<string>City_Name;
double Lnn;		//局部更新时候使用的的常量，它是由最近邻方法得到的一个长度
//最近邻方法:就是从源节点出发，每次选择一个距离最短的点来遍历所有的节点得到的路径，每个节点都可能作为源节点来遍历

int ChooseNextNode(int currentNode, int visitedNode[]);	  //选择下一个节点，配合下面的函数来计算的长度
double CalAdjacentDistance(int node);	//给一个节点由最近邻距离方法计算长度Lnn
double calculateSumOfDistance(int* tour);	//获得经过n个城市的路径长度
class AntColonySystem     //蚁群系统
{
private:
	double info[N][N], visible[N][N];//节点之间的信息素量,节点之间的启发式信息量
public:
	AntColonySystem()
	{
	}
	double Transition(int i, int j);	//计算当前节点到下一节点转移的概率
	void UpdateLocalPathRule(int i, int j);	//局部更新规则	
	void InitParameter(double value);	//初始化	
	void UpdateGlobalPathRule(int* bestTour, int globalBestLength);	//全局信息素更新
};

class ACSAnt                //蚂蚁个体
{
private:
	AntColonySystem* antColony;   //蚁群
protected:
	int startCity, cururentCity;//初始城市编号，当前城市编号
	int allowed[N];//禁忌表	
	int Tour[N][2];//当前路径，是一个个路径段序列组成，即（currentcity，nextcity），用(Tour[i][0],Tour[i][1])表示
	int currentTourIndex;//当前路径索引，从0开始，存储蚂蚁经过城市的编号
public:
	ACSAnt(AntColonySystem* acs, int start)
	{
		antColony = acs;
		startCity = start;
	}
	int* Search();	//开始搜索	
	int Choose();	//选择下一节点	
	void MoveToNextCity(int nextCity);	//移动到下一节点
};
void Initial_City_Map(string s, int k)//i 初始化矩阵
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
void Read_File()//读取文件信息
{
	fstream fin;
	fin.open("map.txt");
	string s;
	int count = -1;
	while (getline(fin, s))
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
int main()
{
	srand((unsigned int)time(NULL));  //初始化随机种子，保证后面的rand（）函数产生不一样的随机数
	Read_File();
	AntColonySystem* acs = new AntColonySystem();	//蚁群系统对象
	ACSAnt* ants[M];
	for (int k = 0; k < M; k++)	//蚂蚁分布在出发城市上
	{
		ants[k] = new ACSAnt(acs, START);		 //M = N = 20
	}
	int node = rand() % N;	//随机选择一个节点计算由最近邻方法得到的一个长度
	Lnn = CalAdjacentDistance(node);
	double initInfo = 1 / (N * Lnn);	//各条路径上初始化的信息素强度
	acs->InitParameter(initInfo);	  //初始化

	int globalTour[N][2];        //全局最优路径，就是路径序列								
	double globalBestLength = 0.0;	 //全局最优长度
	for (int i = 0; i < NcMax; i++)    //NcMax最大循环次数
	{
		int localTour[N][2];	//局部最优路径	
		double localBestLength = 0.0;	//局部最优长度	
		double tourLength;	//当前路径长度
		for (int j = 0; j < M; j++)
		{
			int* tourPath = ants[j]->Search();
			tourLength = calculateSumOfDistance(tourPath);
			//局部比较，并记录路径和长度
			if (tourLength < localBestLength || abs(localBestLength - 0.0) < 0.000001)
			{
				for (int m = 0; m < N; m++)
				{
					int row = *(tourPath + 2 * m);
					int col = *(tourPath + 2 * m + 1);
					localTour[m][0] = row;
					localTour[m][1] = col;
				}
				localBestLength = tourLength;
			}
		}

		//全局比较，并记录路径和长度
		if (localBestLength < globalBestLength || abs(globalBestLength - 0.0) < 0.000001)
		{
			for (int m = 0; m < N; m++)
			{
				globalTour[m][0] = localTour[m][0];
				globalTour[m][1] = localTour[m][1];
			}
			globalBestLength = localBestLength;
		}
		acs->UpdateGlobalPathRule(*globalTour, globalBestLength);
		//输出所有蚂蚁循环一次后的迭代最优路径
		cout << "第 " << i + 1 << " 迭代最优路径:" << localBestLength << "	  " << endl;
		for (int m = 0; m < N; m++)
		{
			cout << City_Name[localTour[m][0]] << "	";
			if (globalTour[m][0] == DEST)
			{
				break;
			}
		}
		cout << endl;
	}

	//输出全局最优路径
	cout << "全局最优路径长度:" << globalBestLength << endl;
	cout << "全局最优路径:";
	for (int m = 0; m < N; m++)
	{
		
		cout << City_Name[globalTour[m][0]] << " ";
		if (globalTour[m][0] == DEST)
		{
			break;
		}
	}
	cout << endl;
	system("pause");
	return 0;
}
//计算当前节点到下一节点转移的概率
double AntColonySystem::Transition(int i, int j)
{
	if (i != j)
	{
		return (pow(info[i][j], alpha) * pow(visible[i][j], beta));  //采用的5.1的概率计算公式
	}
	else
	{
		return 0.0;
	}
}

//局部更新规则
void AntColonySystem::UpdateLocalPathRule(int i, int j)
{
	info[i][j] = (1.0 - alpha1) * info[i][j] + alpha1 * (1.0 / (N * Lnn));
	info[j][i] = info[i][j];
}

//初始化
void AntColonySystem::InitParameter(double value)
{
	//初始化路径上的信息素强度tao0
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			info[i][j] = value;   //信息素强度
			info[j][i] = value;
			if (i != j)
			{
				visible[i][j] = 1.0 / City_Map[i][j];   //启发式信息强度
				visible[j][i] = visible[i][j];
			}
		}
	}
}

//全局信息素更新
void AntColonySystem::UpdateGlobalPathRule(int* bestTour, int globalBestLength)
{
	for (int i = 0; i < N; i++)
	{
		int row = *(bestTour + 2 * i);
		int col = *(bestTour + 2 * i + 1);
		info[row][col] = (1.0 - rou) * info[row][col] + rou * (1.0 / globalBestLength);
		info[col][row] = info[row][col];
	}
}

//选择下一个节点，配合下面的函数来计算的长度
int ChooseNextNode(int currentNode, int visitedNode[])
{
	int nextNode = -1;
	double shortDistance = 0.0;
	for (int i = 0; i < N; i++)
	{
		//去掉已走过的节点,从剩下节点中选择距离最近的节点
		
		if (1 == visitedNode[i])
		{
			if (shortDistance == 0.0)
			{
				shortDistance = City_Map[currentNode][i];
				nextNode = i;
			}
			if (shortDistance < City_Map[currentNode][i])
			{
				nextNode = i;
			}
		}
	}
	return nextNode;
}

//给一个节点由最近邻距离方法计算长度
double CalAdjacentDistance(int node)
{
	double sum = 0.0;
	int visitedNode[N];
	for (int j = 0; j < N; j++)
	{
		visitedNode[j] = 1;
	}
	visitedNode[node] = 0;
	int currentNode = node;
	int nextNode;
	do
	{
		nextNode = ChooseNextNode(currentNode, visitedNode);
		if (nextNode >= 0)
		{
	
			sum += City_Map[currentNode][nextNode];  //allDistance为两城市间的距离矩阵
			currentNode = nextNode;
			visitedNode[currentNode] = 0;
		}
	} while (nextNode >= 0);
	sum += City_Map[currentNode][node];
	return sum;
}


//开始搜索
int* ACSAnt::Search()
{
	cururentCity = startCity;
	int toCity;
	currentTourIndex = 0;        //当前路径索引，存储蚂蚁经过城市的编号
	for (int i = 0; i < N; i++)
	{
		allowed[i] = 1;          //禁忌表
	}
	allowed[cururentCity] = 0;	//cururentCity为当前城市编号
	int endCity;
	int count = 0;
	do
	{
		count++;
		endCity = cururentCity;
		toCity = Choose();	     //选择下一个节点	
		if (toCity == DEST)
		{
			MoveToNextCity(toCity);    //移动到下一个节点
			antColony->UpdateLocalPathRule(endCity, toCity);  //进行局部更新
			break;
		}
		if (toCity >= 0)
		{
			MoveToNextCity(toCity);    //移动到下一个节点
			antColony->UpdateLocalPathRule(endCity, toCity);  //进行局部更新
			cururentCity = toCity;
		}
	} while (toCity >= 0);
	MoveToNextCity(toCity);
	return *Tour;  
}

//选择下一节点
int ACSAnt::Choose()
{
	int nextCity = -1;
	double q = rand() / (double)RAND_MAX;    //产生一个0~1之间的随机数q												 
	if (q <= qzero)	//如果 q <= q0,按先验知识，否则则按概率转移
	{
		double probability = -1.0;//转移到下一节点的概率
		for (int i = 0; i < N; i++)
		{
			//去掉禁忌表中已走过的节点,从剩下节点中选择最大概率的可行节点
			if (1 == allowed[i] )
			{
				double prob = antColony->Transition(cururentCity, i);  //计算当前节点转移到下一节点的概率
				if (prob > probability)
				{
					nextCity = i;
					probability = prob;
				}
			}
		}
	}
	else
	{
		//按概率转移			
		double p = rand() / (double)RAND_MAX;	//生成一个随机数,用来判断落在哪个区间段
		double sum = 0.0;
		double probability = 0.0;	//概率的区间点，p 落在哪个区间段，则该点是转移的方向										
		for (int i = 0; i < N; i++)	//计算概率公式的分母的值
		{
			if (1 == allowed[i] )
			{
				sum += antColony->Transition(cururentCity, i);
			}
		}
		for (int j = 0; j < N; j++)
		{
			if (1 == allowed[j] && sum > 0 )
			{
				probability += antColony->Transition(cururentCity, j) / sum; //往城市j转移的概率
				if (probability >= p || (p > 0.9999 && probability > 0.9999))
				{
					nextCity = j;
					break;
				}
			}
		}
	}
	return nextCity;
}

//移动到下一节点
void ACSAnt::MoveToNextCity(int nextCity)
{
	allowed[nextCity] = 0;    //禁忌表
	Tour[currentTourIndex][0] = cururentCity;	//当前路径
	Tour[currentTourIndex][1] = nextCity;
	currentTourIndex++;
	cururentCity = nextCity;
}


//获得经过n个城市的路径长度  
double calculateSumOfDistance(int* tour)
{
	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		int row = *(tour + 2 * i);
		int col = *(tour + 2 * i + 1);
		sum += City_Map[row][col];
	}
	return sum;
}

