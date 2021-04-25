#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include<cmath>
using namespace std;
string WEEK[7] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
int count_month(int year, int month);
void judege_holiday(int month, int day)//�ж��������
{
	if (month==1&&day==1)
	{
		cout << "������Ԫ��"<<endl;
	}
	if (month==2&&day==14)
	{
		cout << "���������˽�"<<endl;
	}
	if (month==3&&day==5)
	{
		cout << "�������׷������" << endl;
	}
	if (month==3&&day==8)
	{
		cout << "�����������˸�Ů��" << endl;
	}
	if (month==4&&day==1)
	{
		cout << "���������˽�" << endl;
	}
	if (month==5&&day==1)
	{
		cout << "�������塤һ�Ͷ���" << endl;
	}
	if (month==5&&day==4)
	{
		cout << "�������塤�������" << endl;
	}
	if (month==6&&day==1)
	{
		cout << "����������һ��ͯ��" << endl;
	}
	if (month==7&&day==1)
	{
		cout << "�������й��������ĵ�����" << endl;
	}
	if (month==8&&day==1)
	{
		cout << "�����ǽ�����" << endl;
	}
	if (month==9&&day==3)
	{
		cout << "�������й�����ս��ʤ��������" << endl;
	}
	if (month==9&&day==10)
	{
		cout << "�����ǽ�ʦ��" << endl;
	}
	if (month==9&&day==18)
	{
		cout << "�����ǡ��š�һ�ˡ��±������" << endl;
		cout << "�������ܣ��ᱲ��ǿ��" << endl;
	}
	if (month==10&&day==1)
	{
		cout << "�����ǹ����"<<endl;
	}
	if (month==12&&day==25)
	{
		cout << "������ʥ����" << endl;
	}
}
bool isleapyear(int year)//�ж��Ƿ�Ϊ����
{
	if (year % 4 ==0)
	{
		if (year%100==0&&year%400!=0)
		{
			return false;
		}
		return true;
	}
	else
		return false;
}
int total_days(int year,int month,int day)//�������������� �� 1800�� 1 �� 1�� ���������
{
	int total_days=0;
	for (int i = 1800; i <year; i++)
	{
		if (isleapyear(i))
		{
			total_days += 366;
		}
		else
			total_days += 365;
	}
	for (int i = 1; i < month; i++)
	{
		total_days += count_month(year, i);
	}
	total_days += (day-1);
	return total_days;
}
int count_month(int year,int month)//�жϴ�С�� �����ظ������� 
{
	if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
	{
		return 31;
	}
	if (month==2)//2�� ƽ�� 28�� ���� 29��
	{
		if (isleapyear(year))
		{
			return 29;
		}
		else
			return 28;
	}	
		return 30;
}
int count_week(int x)//ͨ�������������� 1800 �� 1 �� 1 Ϊ ����
{
	int week = ((x) % 7);
	if (week==0)
	{
		return 3;
	}
	if (week==1)
	{
		return 4;
	}
	if (week==2)
	{
		return 5;
	}
	if (week==3)
	{
		return 6;
	}
	if (week==4)
	{
		return 0;
	}
	if (week==5)
	{
		return 1;
	}
	if (week==6)
	{
		return 2;
	}
}
void print_calender_year(int year)//ÿһ������

{
	cout << "****************" << "��" << year << "��" << "****************" << endl;
	for (int i = 1; i <= 12; i++)
	{
		cout << "****************" << "��" << i << "��" << "****************"<< endl;
		for (int k = 0; k < 7; k++)
		{
			cout<< WEEK[k]<<"  ";
		}
		cout << endl;
		int count = 0;
		int total_fisrt = total_days(year, i, 1);
		int week_first = count_week(total_fisrt);
		if (week_first != 0)//����ÿ���µ�һ�������ڼ� �����������������ո�ֱ����Ӧ���������
		{
			for (int m = 0; m < week_first; m++)
			{
				cout << "     ";
				count++;
			}
		}
		for (int j = 1; j <= count_month(year, i); j++)
		{

			cout << setw(3) << j << "  ";
			count++;
			if (count % 7 == 0)//ÿ���컻��
			{
				cout << endl;
			}
		}
		cout << endl;
	}		
}
void print_calender_month(int year, int month)
{
	cout << "****************" "��" << year << "��"  << "��" << month << "��" << "****************" << endl;
	for (int k = 0; k < 7; k++)
	{
		cout << WEEK[k] << "  ";
	}
	cout << endl;
	int count = 0;
	int total_fisrt = total_days(year, month, 1);
	int week_first = count_week(total_fisrt);
	if (week_first != 0)
	{
		for (int m = 0; m < week_first; m++)
		{
			cout << "     ";
			count++;
		}
	}
	for (int j = 1; j <= count_month(year, month); j++)
	{

		cout << setw(3) << j << "  ";
		count++;
		if (count % 7 == 0)
		{
			cout << endl;
		}
	}
}
void count_time_diff(int year, int month,int day)//�����뵱ǰ������������
{
	int goal = total_days(year, month, day);//����Ŀ��������1800����������
	time_t time_seconds = time(0);//����ϵͳʱ��
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);
	int now_year = (now_time.tm_year+1900);//��ǰ���
	int now_month = now_time.tm_mon+1;//��ǰ�·�
	int now_day = now_time.tm_mday;//��ǰ����
	int nowtime= total_days(now_year, now_month, now_day);//���㵱ǰ��������1800����������
	cout << year << "�� " << month << "�� " << day << "�� ������" << abs(goal - nowtime) << "��"<<endl;//�������
	judege_holiday(month, day);//�ж�Ŀ�������Ƿ�Ϊ�ڼ���
}
void function()//ѡ����
{
	int i = 0;
	cout << "����������������������Ĺ���" << endl;
	cout<< "������1 ���ĳ����������������2 ���ĳ�������� ������3 ���Ŀ����������������죩 �����˳�������" << endl;
	cin >> i;
	if (i==1)
	{
		int year;
		cout << "��������ݣ�";
		cin >> year;
		print_calender_year(year);
		system("pause");
		system("cls");
		return;
	}
	if (i==2)
	{
		int year, month;
		cout << "����������·�";
		cin >> year >> month;
		print_calender_month(year, month);
		system("pause");
		system("cls");
		return;
	}
	if (i==3)
	{
		int year, month, day;
		cout << "������������";
		cin >> year >> month >> day;
		count_time_diff(year, month, day);
		system("pause");
		system("cls");
		return;
	}
	exit(0);
}
int main()
{
	while (1)
	{
		function();
	}
	system("pause");
	return 0;

}