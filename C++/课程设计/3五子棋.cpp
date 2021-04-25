#include<iostream>
#include<iomanip>
#include<cstdlib>
using namespace std;
#define range 10//���̴�С
char a[range][range];//����
int out(int x, int y)//�ж��Ƿ����
{
	if (x>range-1||x<0||y>range - 1 ||y<0)
	{
		return 1;
	}
	return 0;
}
void test_right(int x,int y,char c)//�ҶԽ��ߵļ�⣨���µ����ϣ�
{
	int sum , i, j,row,col;
	for (i = x + 4, j = y - 4;i<=x,j<=y;i--,j++)//�����µ�����λ���μ��
	{
		sum = 0;
		if (out(i,j)==1)
		{
			continue;
		}
		for (row = i,col = j; sum<=5; row--,col++)//�кż�һ �кż�һ
		{
			if (a[row][col] != c)//����ӵĸ��� ���в�����ֱ���˳�
			{
				break;
			}
			else
			{
				sum++;
			}
		}
		if (sum==5)
		{
			cout << "ִ" << c << "���߻�ʤ!!!";
			system("pause");
			exit(0);
		}
	}
}
void test_left(int x, int y, char c)//��Խ��ߵļ�� �����ϵ����£�
{
	int sum, i, j,row,col;
	for (i = x - 4, j = y - 4; i <= x, j <= y; i++, j++)
	{
		sum = 0;
		if (out(i, j) == 1)
		{
			continue;
		}
		for ( row = i, col = j; sum <= 5; row++, col++)
		{
			if (a[row][col] != c)
			{
				break;
			}
			else
			{
				sum++;
			}
		}
		if (sum == 5)
		{
			cout << "ִ" << c << "���߻�ʤ!!!";
			system("pause");
			exit(0);
		}
	}
}
void test_left_to_right(int x, int y, char c)//�����ҵļ��
{
	int sum, i,col;
	for (i=y-4; i <= y; i++)//�кŲ����к����μ�һ
	{
		sum = 0;
		if (out(x,i) == 1)
		{
			continue;
		}
		for ( col = i; sum <= 5; col++)
		{
			if (a[x][col] != c)
			{
				break;
			}
			else
			{
				sum++;
			}
		}
		if (sum == 5)
		{
			cout << "ִ" << c << "���߻�ʤ!!!";
			system("pause");
			exit(0);
		}
	}
}
void test_down_to_up(int x, int y, char c)//���µ��ϵļ��
{
	int sum, i,row;
	for (i = x-4; i <= x; i++)//�кŲ����к����μ�һ
	{
		sum = 0;
		if (out(i, y) == 1)
		{
			continue;
		}
		for (row = i; sum <= 5; row++)
		{
			if (a[row][y] != c)
			{
				break;
			}
			else
			{
				sum++;
			}
		}
		if (sum == 5)
		{
			cout << "ִ" << c << "���߻�ʤ!!!";
			system("pause");
			exit(0);
		}
	}
}
void test(int x, int y, char c)//�ܼ��
{
	if (a[x+1][y-1]==c||a[x-1][y+1]==c)//����ҶԽ���
	{
		test_right(x, y, c);
	}
	if (a[x-1][y-1]==c||a[x+1][y+1]==c)//�����Խ���
	{
		test_left(x, y, c);
	}
	if (a[x-1][y]==c||a[x+1][y]==c)//�����
	{
		test_down_to_up(x, y, c);
	}
	if (a[x][y-1]==c||a[x][y+1]==c)//�����
	{
		
		test_left_to_right(x, y, c);
	}
}

void put_chess(char c)//����
{
part1:
	int x = ' ', y = ' ';
	cout << "��ִ" << c << "���ѡ������ ���������꣩��";
	cin >> x >> y;
	if (out(x, y) == 1)
	{
		cout << "���峬����Χ�����䣡";
		goto part1;
	}
	if (a[x][y] != ' ')
	{
		cout << "��λ���ѱ�ռ�ã� �����䣡";
		goto part1;
	}
	a[x][y] = c;
	test(x, y, c);
}
void print()//��ӡ����
{
	cout << " ح";
	for (int j = 0; j < range; j++)
	{
			cout<< setw(1) << j << "ح";
	}
	cout << endl;
	for (int i = 0; i < range; i++)
	{
		for (int k = 0; k < (range+1)*3; k++)
		{
			cout << "-";
		}
		cout << endl;
		cout << i << "ح";
		for (int j = 0; j < range; j++)
		{
			cout<<setw(1)<<a[i][j] << "ح";
		}
		cout << endl;
	}
	cout << endl;
}
int main()
{part2:
    print();
	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < range; j++)
		{
			a[i][j] = ' ';
		}
	}
	cout <<setw(3*(range/2)+4)<< "��Ϸ��ʼ" << endl;
	int round = 0;//�غ���
	while (round<=(range*range))
	{
		if (round==range*range)
		{
			cout << "ƽ�֣�" << endl;
			cout << "���¿�ʼ��" << endl;
			goto part2;
		}
		put_chess('B');// ����
		system("cls");//ͨ�������ٴ�ӡʵ�ֶ�̬�仯
		print();
		put_chess('W');//����
		system("cls");
		print();
		round++;
	}
	system("pause");
	return 0;
}