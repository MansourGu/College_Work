#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include<cmath>
using namespace std;
string WEEK[7] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
int count_month(int year, int month);
void judege_holiday(int month, int day)//判断特殊节日
{
	if (month==1&&day==1)
	{
		cout << "该天是元旦"<<endl;
	}
	if (month==2&&day==14)
	{
		cout << "该天是情人节"<<endl;
	}
	if (month==3&&day==5)
	{
		cout << "该天是雷锋纪念日" << endl;
	}
	if (month==3&&day==8)
	{
		cout << "该天是三·八妇女节" << endl;
	}
	if (month==4&&day==1)
	{
		cout << "该天是愚人节" << endl;
	}
	if (month==5&&day==1)
	{
		cout << "该天是五·一劳动节" << endl;
	}
	if (month==5&&day==4)
	{
		cout << "该天是五·四青年节" << endl;
	}
	if (month==6&&day==1)
	{
		cout << "该天是六·一儿童节" << endl;
	}
	if (month==7&&day==1)
	{
		cout << "该天是中国共产党的诞生日" << endl;
	}
	if (month==8&&day==1)
	{
		cout << "该天是建军节" << endl;
	}
	if (month==9&&day==3)
	{
		cout << "该天是中国抗日战争胜利纪念日" << endl;
	}
	if (month==9&&day==10)
	{
		cout << "该天是教师节" << endl;
	}
	if (month==9&&day==18)
	{
		cout << "该天是“九·一八”事变纪念日" << endl;
		cout << "勿忘国耻，吾辈自强！" << endl;
	}
	if (month==10&&day==1)
	{
		cout << "该天是国庆节"<<endl;
	}
	if (month==12&&day==25)
	{
		cout << "该天是圣诞节" << endl;
	}
}
bool isleapyear(int year)//判断是否为闰年
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
int total_days(int year,int month,int day)//算从输入的年月日 到 1800年 1 月 1日 相隔多少天
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
int count_month(int year,int month)//判断大小月 并返回该月天数 
{
	if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
	{
		return 31;
	}
	if (month==2)//2月 平年 28天 闰年 29天
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
int count_week(int x)//通过天数计算星期 1800 年 1 月 1 为 周三
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
void print_calender_year(int year)//每一年日历

{
	cout << "****************" << "第" << year << "年" << "****************" << endl;
	for (int i = 1; i <= 12; i++)
	{
		cout << "****************" << "第" << i << "月" << "****************"<< endl;
		for (int k = 0; k < 7; k++)
		{
			cout<< WEEK[k]<<"  ";
		}
		cout << endl;
		int count = 0;
		int total_fisrt = total_days(year, i, 1);
		int week_first = count_week(total_fisrt);
		if (week_first != 0)//计算每个月的一号是星期几 如果不是星期天输出空格直到对应该天的星期
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
			if (count % 7 == 0)//每七天换行
			{
				cout << endl;
			}
		}
		cout << endl;
	}		
}
void print_calender_month(int year, int month)
{
	cout << "****************" "第" << year << "月"  << "第" << month << "月" << "****************" << endl;
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
void count_time_diff(int year, int month,int day)//计算与当前日期相差的天数
{
	int goal = total_days(year, month, day);//计算目标日期与1800年相距的天数
	time_t time_seconds = time(0);//调用系统时间
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);
	int now_year = (now_time.tm_year+1900);//当前年份
	int now_month = now_time.tm_mon+1;//当前月份
	int now_day = now_time.tm_mday;//当前日期
	int nowtime= total_days(now_year, now_month, now_day);//计算当前日期与与1800年相距的天数
	cout << year << "年 " << month << "月 " << day << "日 相距今天" << abs(goal - nowtime) << "天"<<endl;//两者求差
	judege_holiday(month, day);//判断目标日期是否为节假日
}
void function()//选择功能
{
	int i = 0;
	cout << "请输入数字来决定本程序的功能" << endl;
	cout<< "（输入1 输出某年万年历）（输入2 输出某月月历） （输入3 输出目标日与今天相距多少天） 其他退出本程序" << endl;
	cin >> i;
	if (i==1)
	{
		int year;
		cout << "请输入年份：";
		cin >> year;
		print_calender_year(year);
		system("pause");
		system("cls");
		return;
	}
	if (i==2)
	{
		int year, month;
		cout << "请输入年份月份";
		cin >> year >> month;
		print_calender_month(year, month);
		system("pause");
		system("cls");
		return;
	}
	if (i==3)
	{
		int year, month, day;
		cout << "请输入年月日";
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