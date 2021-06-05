#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
void get_init();
float fun(float x, float y);
void find_min(float x[], int n);
void V_update(int x);
void P_update(int x);
void F_update(int x);
void Best_update(int x);
void Print();

const int maxgen = 300;//迭代次数
const int sizepop = 5;//种群个数
float Vmax = 0.6;//最大速度
float Vmin = -0.6;//最小速度
int w = 1;//权重
int popmax = 10;//最大位置
int popmin = -10;//最小位置
float c1 = 2;//加速因子
float c2 = 2;//加速因子
float pop[sizepop][2];
float V[sizepop][2];
float fitness[sizepop];
float min = 10000;
int index = 0;
float fitnesszbest;
int bestindex;
float fitnessgbest[sizepop];//每个种群的最佳适应值
float zbest[2];
float gbest[sizepop][2];
double best_record[maxgen];



int main()
{
	srand((int)time(0));
	get_init();
	find_min(fitness, sizepop);
	fitnesszbest = min;                             //全局最优值
	bestindex = index;                                //全局最优索引
	for (int i = 0; i < sizepop; i++)
	{
		fitnessgbest[i] = fitness[i];             //个体最优值
	}
	for (int i = 0; i < 2; i++)
	{
		zbest[i] = pop[bestindex][i];             // 种群历史最优解
	}
	for (int i = 0; i < sizepop; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			gbest[i][j] = pop[i][j];                     //个体历史最优解
		}
	}


	for (int i = 0; i < maxgen; i++)
	{
		for (int j = 0; j < sizepop; j++)
		{
			V_update(j);
			P_update(j);
			F_update(j);
			cout << "第" << j + 1 << "个种群的第" << i + 1 << "次迭代 取值：" << pop[j][0] << "  " << pop[j][1]<<"  ";
			cout<<fun(pop[j][0],pop[j][1])<<endl;
		}
		for (int j = 0; j < sizepop; j++)
		{
			Best_update(j);
		}
		best_record[i] = fitnesszbest;
	}
	cout << "最佳取值为：" << zbest[0] << "\t" << zbest[1] << endl;
	cout << "最小函数值为：" << fitnesszbest << endl;
	
	system("pause");
	return 0;
}

float fun(float x, float y)
{
	return (x*x -y*y);
}

void get_init()
{
	for (int i = 0; i < sizepop; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pop[i][j] = -10 + 20 * rand() / float(RAND_MAX);
			V[i][j] = -0.6 + 1.2 * rand() / float(RAND_MAX);
		}
		fitness[i] = fun(pop[i][0], pop[i][1]);
	}
}

void find_min(float x[], int n)
{
	for (int i = 0; i <= n - 1; i++)
	{
		if (x[i] <= min)
		{
			min = x[i];
			index = i;
		}
	}
}

void V_update(int x)
{
	float random = rand() / float(RAND_MAX);
	for (char j = 0; j < 2; j++)
	{
		V[x][j] = w * V[x][j] + c1 * random * (gbest[x][j] - pop[x][j]) + c2 * random * (zbest[j] - pop[x][j]);
		if (V[x][j] > Vmax)
		{
			V[x][j] = Vmax;
		}
		if (V[x][j] < Vmin)
		{
			V[x][j] = Vmin;
		}
	}
}

void P_update(int x)
{
	for (char j = 0; j < 2; j++)
	{
		pop[x][j] = pop[x][j] + V[x][j];
		if (pop[x][j] > popmax)
		{
			pop[x][j] = popmax;
		}
		if (pop[x][j] < popmin)
		{
			pop[x][j] = popmin;
		}
	}
}

void F_update(int x)
{
	fitness[x] = fun(pop[x][0], pop[x][1]);

}

void Best_update(int x)
{
	if (fitness[x] < fitnessgbest[x])
	{
		for (char j = 0; j < 2; j++)
		{
			gbest[x][j] = pop[x][j];
		}
		fitnessgbest[x] = fitness[x];
	}
	if (fitness[x] < fitnesszbest)
	{
		for (char j = 0; j < 2; j++)
		{
			zbest[j] = pop[x][j];
		}
		fitnesszbest = fitness[x];
	}
}

void Print()
{
	for (int i = 0; i < maxgen; i++)
	{
		cout<<*gbest[i]<<endl;
	}
}