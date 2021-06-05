#include<iostream>
#include<ctime>
using namespace std;
#define num_queen 20//皇后数目
int row[num_queen];//row[i]表示第i行的皇后数目
int col[num_queen];//col[j]表示第j列的皇后数目
int principal_diagnal[num_queen*2];//每一条从左上到右下的对角线上的皇后数目
int counter_diagnal [num_queen*2];//每一条从右上到左下的对角线上的皇后数
int Queen [num_queen];//用来存放皇后的位置Queen[i] = j  第i行j列有一个皇后
int Get_NO_Principal_diagnal(int row, int col)//给定一个位置返回其主对角线编号(由上到下开始编号)
{
	return row - col + num_queen - 1;
}
int Get_NO_Conter_diagnal(int row, int col)//给定一个位置返回其副对角线编号(由上到下开始编号)
{
	return row + col;
}
int random_func(int start, int end)
{
	return rand() % (end - start) + start;
}
void random(int a[], int start, int end)//洗牌算法 将数组打乱
{
	for (int i = start; i <  end -1; i++)
	{
		int temp = random_func(i,end);//随机取一个在i到end 之间的数
		swap(a[i], a[temp]);
	}
}
void initial()
{
	for (int i = 0; i < num_queen; i++)//初始化数组让每主对角线上都放一个皇后
	{
		Queen[i] = i;
	}
	random(Queen, 0, num_queen);//将皇后打乱此时没有一个皇后同行、没有一个皇后同列
	for (int i = 0; i < num_queen; i++)//没一个皇后同行且同列 那么每行 and 每列 有且仅有一个皇后
	{
		row[i] = 1;//每行都有一个
		col[i] = 0;//每列都有一个
	}
	for (int i = 0; i < 2*num_queen -1 ; i++)//初始化对角线
	{
		principal_diagnal[i] = 0;
		counter_diagnal[i] = 0;
	}
	for (int i = 0; i < num_queen; i++)
	{
		col[Queen[i]]++;
		principal_diagnal[Get_NO_Principal_diagnal(i, Queen[i])]++;//将主对角线元素初始化
		counter_diagnal[Get_NO_Conter_diagnal(i, Queen[i])]++;//将副对角线元素初始化
	}
}
bool Verify()
{
	for (int i = 0; i < num_queen; i++)
	{
		if (col[Queen[i]] != 1 || 
			principal_diagnal[Get_NO_Principal_diagnal(i,Queen[i])] != 1 ||
			counter_diagnal[Get_NO_Conter_diagnal(i,Queen[i])] != 1)//如果有一列的皇后数目 or 一条主（副）对角线上的皇后数目超过 1 那么他就不满足条件
		{
			return false;
		}
	}
	return true;//所有列、主、副对角线都满足条件那么返回true
}
bool Adjust(int row)// 调整行
{
	int current_col = Queen[row];//当前行皇后的列
	int best_col = current_col;//最佳列号
	int min_conflict = col[best_col] + (principal_diagnal[Get_NO_Principal_diagnal(row, best_col)] -1) +
		(counter_diagnal[Get_NO_Conter_diagnal(row,best_col)]-1);//对角线冲突数目为对角线皇后数目 - 1
	for (int i = 0; i < num_queen; i++)//按列搜寻row行的每个位置的冲突数目
	{
		if (i == current_col)
		{
			continue;
		}
		int conflict = col[i] + principal_diagnal[Get_NO_Principal_diagnal(row, i)]+counter_diagnal[Get_NO_Conter_diagnal(row, i)];
		if (conflict < min_conflict)
		{
			min_conflict = conflict;//如果找到比当前冲突还少那么就替换
			best_col = i;
		}
	}
	if (best_col != current_col)
	{
		col[current_col]--;//原来列皇后数减少一
		col[best_col]++;//当前列的皇后数目加一
		principal_diagnal[Get_NO_Principal_diagnal(row, current_col)]--;//原来该对角线的皇后数目-1
		principal_diagnal[Get_NO_Principal_diagnal(row, best_col)]++;//当前对角线上皇后数目加一
		counter_diagnal[Get_NO_Conter_diagnal(row, current_col)]--;
		counter_diagnal[Get_NO_Conter_diagnal(row, best_col)]++;
		Queen[row] = best_col;
		if (col[current_col]==1 && col[best_col]==1 && principal_diagnal[Get_NO_Principal_diagnal(row,best_col)]==1 && counter_diagnal[Get_NO_Conter_diagnal(row, best_col)] ==1)
		{
			return Verify();
		}

	}
	return false;// 最佳点没变说明没达到终止条件
}
void Print()
{
	
	for (int i = 0; i < num_queen; i++)
	{
		cout << "每"<<i+1<<"行的皇后位置为：" << Queen[i]+1<<"列 " <<endl;
	}
	for (int i = 0; i < num_queen; i++)
	{
		for (int j = 0; j < num_queen; j++)
		{
			if (Queen[i] == j)
			{
				cout << " Q ";
			}
			else
			{
				cout << " * ";
			}
		}
		cout << endl;
	}
}
int main()
{
	srand((unsigned)time(NULL));
	initial();
	if (Verify())
	{
		Print();
		system("pause");
		return 0;
	}
	bool Terminal = false;
	while (!Terminal)
	{
		for (int i = 0; i < num_queen; i++)
		{
			if (Adjust(i))
			{
				Terminal = true;
				break;
			}
		}

	}
	Print();
	system("pause");
	return 0;
}