#include<iostream>
#include<ctime>
using namespace std;
#define num_queen 20//�ʺ���Ŀ
int row[num_queen];//row[i]��ʾ��i�еĻʺ���Ŀ
int col[num_queen];//col[j]��ʾ��j�еĻʺ���Ŀ
int principal_diagnal[num_queen*2];//ÿһ�������ϵ����µĶԽ����ϵĻʺ���Ŀ
int counter_diagnal [num_queen*2];//ÿһ�������ϵ����µĶԽ����ϵĻʺ���
int Queen [num_queen];//������Żʺ��λ��Queen[i] = j  ��i��j����һ���ʺ�
int Get_NO_Principal_diagnal(int row, int col)//����һ��λ�÷��������Խ��߱��(���ϵ��¿�ʼ���)
{
	return row - col + num_queen - 1;
}
int Get_NO_Conter_diagnal(int row, int col)//����һ��λ�÷����丱�Խ��߱��(���ϵ��¿�ʼ���)
{
	return row + col;
}
int random_func(int start, int end)
{
	return rand() % (end - start) + start;
}
void random(int a[], int start, int end)//ϴ���㷨 ���������
{
	for (int i = start; i <  end -1; i++)
	{
		int temp = random_func(i,end);//���ȡһ����i��end ֮�����
		swap(a[i], a[temp]);
	}
}
void initial()
{
	for (int i = 0; i < num_queen; i++)//��ʼ��������ÿ���Խ����϶���һ���ʺ�
	{
		Queen[i] = i;
	}
	random(Queen, 0, num_queen);//���ʺ���Ҵ�ʱû��һ���ʺ�ͬ�С�û��һ���ʺ�ͬ��
	for (int i = 0; i < num_queen; i++)//ûһ���ʺ�ͬ����ͬ�� ��ôÿ�� and ÿ�� ���ҽ���һ���ʺ�
	{
		row[i] = 1;//ÿ�ж���һ��
		col[i] = 0;//ÿ�ж���һ��
	}
	for (int i = 0; i < 2*num_queen -1 ; i++)//��ʼ���Խ���
	{
		principal_diagnal[i] = 0;
		counter_diagnal[i] = 0;
	}
	for (int i = 0; i < num_queen; i++)
	{
		col[Queen[i]]++;
		principal_diagnal[Get_NO_Principal_diagnal(i, Queen[i])]++;//�����Խ���Ԫ�س�ʼ��
		counter_diagnal[Get_NO_Conter_diagnal(i, Queen[i])]++;//�����Խ���Ԫ�س�ʼ��
	}
}
bool Verify()
{
	for (int i = 0; i < num_queen; i++)
	{
		if (col[Queen[i]] != 1 || 
			principal_diagnal[Get_NO_Principal_diagnal(i,Queen[i])] != 1 ||
			counter_diagnal[Get_NO_Conter_diagnal(i,Queen[i])] != 1)//�����һ�еĻʺ���Ŀ or һ�����������Խ����ϵĻʺ���Ŀ���� 1 ��ô���Ͳ���������
		{
			return false;
		}
	}
	return true;//�����С��������Խ��߶�����������ô����true
}
bool Adjust(int row)// ������
{
	int current_col = Queen[row];//��ǰ�лʺ����
	int best_col = current_col;//����к�
	int min_conflict = col[best_col] + (principal_diagnal[Get_NO_Principal_diagnal(row, best_col)] -1) +
		(counter_diagnal[Get_NO_Conter_diagnal(row,best_col)]-1);//�Խ��߳�ͻ��ĿΪ�Խ��߻ʺ���Ŀ - 1
	for (int i = 0; i < num_queen; i++)//������Ѱrow�е�ÿ��λ�õĳ�ͻ��Ŀ
	{
		if (i == current_col)
		{
			continue;
		}
		int conflict = col[i] + principal_diagnal[Get_NO_Principal_diagnal(row, i)]+counter_diagnal[Get_NO_Conter_diagnal(row, i)];
		if (conflict < min_conflict)
		{
			min_conflict = conflict;//����ҵ��ȵ�ǰ��ͻ������ô���滻
			best_col = i;
		}
	}
	if (best_col != current_col)
	{
		col[current_col]--;//ԭ���лʺ�������һ
		col[best_col]++;//��ǰ�еĻʺ���Ŀ��һ
		principal_diagnal[Get_NO_Principal_diagnal(row, current_col)]--;//ԭ���öԽ��ߵĻʺ���Ŀ-1
		principal_diagnal[Get_NO_Principal_diagnal(row, best_col)]++;//��ǰ�Խ����ϻʺ���Ŀ��һ
		counter_diagnal[Get_NO_Conter_diagnal(row, current_col)]--;
		counter_diagnal[Get_NO_Conter_diagnal(row, best_col)]++;
		Queen[row] = best_col;
		if (col[current_col]==1 && col[best_col]==1 && principal_diagnal[Get_NO_Principal_diagnal(row,best_col)]==1 && counter_diagnal[Get_NO_Conter_diagnal(row, best_col)] ==1)
		{
			return Verify();
		}

	}
	return false;// ��ѵ�û��˵��û�ﵽ��ֹ����
}
void Print()
{
	
	for (int i = 0; i < num_queen; i++)
	{
		cout << "ÿ"<<i+1<<"�еĻʺ�λ��Ϊ��" << Queen[i]+1<<"�� " <<endl;
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