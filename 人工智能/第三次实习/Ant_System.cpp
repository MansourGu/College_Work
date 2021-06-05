#include <iostream>
#include <math.h>
#include <time.h>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

#define N 20  //���нڵ���Ŀ
#define M 40	 //��������
#define DEST 1
#define START 0
int NcMax = 2000;  //���ѭ������NcMax
double alpha = 1, beta = 5, rou = 0.5, alpha1 = 0.5, qzero = 0.1;
//��Ϣ�������ӣ���������ʽ���ӣ�ȫ����Ϣ�ػӷ��������ֲ���Ϣ�ػӷ�����, ״̬ת�ƹ�ʽ�е�q0
double City_Map[N][N];	//�����ʾ��������֮��ľ���
vector<string>City_Name;
double Lnn;		//�ֲ�����ʱ��ʹ�õĵĳ���������������ڷ����õ���һ������
//����ڷ���:���Ǵ�Դ�ڵ������ÿ��ѡ��һ��������̵ĵ����������еĽڵ�õ���·����ÿ���ڵ㶼������ΪԴ�ڵ�������

int ChooseNextNode(int currentNode, int visitedNode[]);	  //ѡ����һ���ڵ㣬�������ĺ���������ĳ���
double CalAdjacentDistance(int node);	//��һ���ڵ�������ھ��뷽�����㳤��Lnn
double calculateSumOfDistance(int* tour);	//��þ���n�����е�·������
class AntColonySystem     //��Ⱥϵͳ
{
private:
	double info[N][N], visible[N][N];//�ڵ�֮�����Ϣ����,�ڵ�֮�������ʽ��Ϣ��
public:
	AntColonySystem()
	{
	}
	double Transition(int i, int j);	//���㵱ǰ�ڵ㵽��һ�ڵ�ת�Ƶĸ���
	void UpdateLocalPathRule(int i, int j);	//�ֲ����¹���	
	void InitParameter(double value);	//��ʼ��	
	void UpdateGlobalPathRule(int* bestTour, int globalBestLength);	//ȫ����Ϣ�ظ���
};

class ACSAnt                //���ϸ���
{
private:
	AntColonySystem* antColony;   //��Ⱥ
protected:
	int startCity, cururentCity;//��ʼ���б�ţ���ǰ���б��
	int allowed[N];//���ɱ�	
	int Tour[N][2];//��ǰ·������һ����·����������ɣ�����currentcity��nextcity������(Tour[i][0],Tour[i][1])��ʾ
	int currentTourIndex;//��ǰ·����������0��ʼ���洢���Ͼ������еı��
public:
	ACSAnt(AntColonySystem* acs, int start)
	{
		antColony = acs;
		startCity = start;
	}
	int* Search();	//��ʼ����	
	int Choose();	//ѡ����һ�ڵ�	
	void MoveToNextCity(int nextCity);	//�ƶ�����һ�ڵ�
};
void Initial_City_Map(string s, int k)//i ��ʼ������
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
void Read_File()//��ȡ�ļ���Ϣ
{
	fstream fin;
	fin.open("map.txt");
	string s;
	int count = -1;
	while (getline(fin, s))
	{
		if (count == -1)//��Ҫ��һ��Ԫ��
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
	srand((unsigned int)time(NULL));  //��ʼ��������ӣ���֤�����rand��������������һ���������
	Read_File();
	AntColonySystem* acs = new AntColonySystem();	//��Ⱥϵͳ����
	ACSAnt* ants[M];
	for (int k = 0; k < M; k++)	//���Ϸֲ��ڳ���������
	{
		ants[k] = new ACSAnt(acs, START);		 //M = N = 20
	}
	int node = rand() % N;	//���ѡ��һ���ڵ����������ڷ����õ���һ������
	Lnn = CalAdjacentDistance(node);
	double initInfo = 1 / (N * Lnn);	//����·���ϳ�ʼ������Ϣ��ǿ��
	acs->InitParameter(initInfo);	  //��ʼ��

	int globalTour[N][2];        //ȫ������·��������·������								
	double globalBestLength = 0.0;	 //ȫ�����ų���
	for (int i = 0; i < NcMax; i++)    //NcMax���ѭ������
	{
		int localTour[N][2];	//�ֲ�����·��	
		double localBestLength = 0.0;	//�ֲ����ų���	
		double tourLength;	//��ǰ·������
		for (int j = 0; j < M; j++)
		{
			int* tourPath = ants[j]->Search();
			tourLength = calculateSumOfDistance(tourPath);
			//�ֲ��Ƚϣ�����¼·���ͳ���
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

		//ȫ�ֱȽϣ�����¼·���ͳ���
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
		//�����������ѭ��һ�κ�ĵ�������·��
		cout << "�� " << i + 1 << " ��������·��:" << localBestLength << "	  " << endl;
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

	//���ȫ������·��
	cout << "ȫ������·������:" << globalBestLength << endl;
	cout << "ȫ������·��:";
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
//���㵱ǰ�ڵ㵽��һ�ڵ�ת�Ƶĸ���
double AntColonySystem::Transition(int i, int j)
{
	if (i != j)
	{
		return (pow(info[i][j], alpha) * pow(visible[i][j], beta));  //���õ�5.1�ĸ��ʼ��㹫ʽ
	}
	else
	{
		return 0.0;
	}
}

//�ֲ����¹���
void AntColonySystem::UpdateLocalPathRule(int i, int j)
{
	info[i][j] = (1.0 - alpha1) * info[i][j] + alpha1 * (1.0 / (N * Lnn));
	info[j][i] = info[i][j];
}

//��ʼ��
void AntColonySystem::InitParameter(double value)
{
	//��ʼ��·���ϵ���Ϣ��ǿ��tao0
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			info[i][j] = value;   //��Ϣ��ǿ��
			info[j][i] = value;
			if (i != j)
			{
				visible[i][j] = 1.0 / City_Map[i][j];   //����ʽ��Ϣǿ��
				visible[j][i] = visible[i][j];
			}
		}
	}
}

//ȫ����Ϣ�ظ���
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

//ѡ����һ���ڵ㣬�������ĺ���������ĳ���
int ChooseNextNode(int currentNode, int visitedNode[])
{
	int nextNode = -1;
	double shortDistance = 0.0;
	for (int i = 0; i < N; i++)
	{
		//ȥ�����߹��Ľڵ�,��ʣ�½ڵ���ѡ���������Ľڵ�
		
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

//��һ���ڵ�������ھ��뷽�����㳤��
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
	
			sum += City_Map[currentNode][nextNode];  //allDistanceΪ�����м�ľ������
			currentNode = nextNode;
			visitedNode[currentNode] = 0;
		}
	} while (nextNode >= 0);
	sum += City_Map[currentNode][node];
	return sum;
}


//��ʼ����
int* ACSAnt::Search()
{
	cururentCity = startCity;
	int toCity;
	currentTourIndex = 0;        //��ǰ·���������洢���Ͼ������еı��
	for (int i = 0; i < N; i++)
	{
		allowed[i] = 1;          //���ɱ�
	}
	allowed[cururentCity] = 0;	//cururentCityΪ��ǰ���б��
	int endCity;
	int count = 0;
	do
	{
		count++;
		endCity = cururentCity;
		toCity = Choose();	     //ѡ����һ���ڵ�	
		if (toCity == DEST)
		{
			MoveToNextCity(toCity);    //�ƶ�����һ���ڵ�
			antColony->UpdateLocalPathRule(endCity, toCity);  //���оֲ�����
			break;
		}
		if (toCity >= 0)
		{
			MoveToNextCity(toCity);    //�ƶ�����һ���ڵ�
			antColony->UpdateLocalPathRule(endCity, toCity);  //���оֲ�����
			cururentCity = toCity;
		}
	} while (toCity >= 0);
	MoveToNextCity(toCity);
	return *Tour;  
}

//ѡ����һ�ڵ�
int ACSAnt::Choose()
{
	int nextCity = -1;
	double q = rand() / (double)RAND_MAX;    //����һ��0~1֮��������q												 
	if (q <= qzero)	//��� q <= q0,������֪ʶ�������򰴸���ת��
	{
		double probability = -1.0;//ת�Ƶ���һ�ڵ�ĸ���
		for (int i = 0; i < N; i++)
		{
			//ȥ�����ɱ������߹��Ľڵ�,��ʣ�½ڵ���ѡ�������ʵĿ��нڵ�
			if (1 == allowed[i] )
			{
				double prob = antColony->Transition(cururentCity, i);  //���㵱ǰ�ڵ�ת�Ƶ���һ�ڵ�ĸ���
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
		//������ת��			
		double p = rand() / (double)RAND_MAX;	//����һ�������,�����ж������ĸ������
		double sum = 0.0;
		double probability = 0.0;	//���ʵ�����㣬p �����ĸ�����Σ���õ���ת�Ƶķ���										
		for (int i = 0; i < N; i++)	//������ʹ�ʽ�ķ�ĸ��ֵ
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
				probability += antColony->Transition(cururentCity, j) / sum; //������jת�Ƶĸ���
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

//�ƶ�����һ�ڵ�
void ACSAnt::MoveToNextCity(int nextCity)
{
	allowed[nextCity] = 0;    //���ɱ�
	Tour[currentTourIndex][0] = cururentCity;	//��ǰ·��
	Tour[currentTourIndex][1] = nextCity;
	currentTourIndex++;
	cururentCity = nextCity;
}


//��þ���n�����е�·������  
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

