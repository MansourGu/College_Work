#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<math.h>
#include<easyx.h>
#include<algorithm>
#define Radius 637.1 //地球半径
#define Pi 3.14
using namespace std;
struct Time_Window //时间窗口
{
	int start_time;
	int end_time;
	Time_Window(int s, int e)
	{
		start_time = s;
		end_time = e;
	}
	Time_Window()
	{
	}
};
struct Coordinates//三维坐标
{
	double x;
	double y;
	double z;
	Coordinates(double x_, double y_, double z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	Coordinates(){}
};
struct Long_la//经纬度
{
	double longitude;//经度
	double latitude;//纬度
	Long_la(double longit, double lati)
	{
		longitude = longit;
		latitude = lati;
	}
	Long_la()
	{

	}
};
struct Satelite//卫星
{
	int ID;//卫星编号
	vector<vector<Coordinates>> time_coordinates;//时间与坐标的对应关系
	vector<vector<Long_la>>time_long_la;//时间与经纬度之间的关系
	vector<Coordinates> time_center;//时间与圆心对应
	vector<double>alpha;//时间与角度的对应
};
struct City
{
	string name;//城市名
	Long_la loc_long_la;//城市的经纬度
	Coordinates loc_coordinates;//城市的坐标
	vector<Time_Window> Time_Gap_Satelite;//对于每个卫星的时间窗口
	vector<Time_Window> Gap;//时间间隙
	Time_Window max_gap;
	Time_Window max_time_window;//最大时间窗口
	City(string n, double longi, double lati)
	{
		name = n;
		loc_long_la.longitude = longi;
		loc_long_la.latitude = lati;
	}
};
struct Area//区域
{
	Long_la left_bottom;
	Long_la left_top;
	Long_la right_top;
	Long_la right_bottom;
	vector<Time_Window> Time_Gap_Satelite;
	Time_Window max_gap;
	double Square = 0;
	vector<Time_Window> Gap;//时间间隙
	Area(Long_la l_b, Long_la l_t, Long_la r_t, Long_la r_b)
	{
		left_bottom = l_b;
		left_top = l_t;
		right_top = r_t;
		right_bottom = r_b;
	}
	Area() {}
};
struct Grid
{
	Long_la left_bottom;
	Long_la left_top;
	Long_la right_top;
	Long_la right_bottom;
	int flag;//表示网格状态 1：在 2：不在 3：不确定
	Grid(Long_la l_b, Long_la l_t, Long_la r_t, Long_la r_b)
	{
		left_bottom = l_b;
		left_top = l_t;
		right_top = r_t;
		right_bottom = r_b;
	}
	Grid(){}
};
struct Point
{
	Long_la loc_long_la;//经纬度
	vector<Time_Window> Time_Gap_Satelite;
	Time_Window max_gap;
	double Square;
	vector<Time_Window> Gap;//时间间隙
	Point(double longi, double lati)
	{
		loc_long_la.longitude = longi;
		loc_long_la.latitude = lati;
	}
};
City c_0("坎普尔",80.14,26.27), c_1("堪萨斯城",-94.33,39.02), c_2("高雄",120.27,23.03), c_3("卡拉奇",67.02,24.51),
c_4("加德满都餐厅",85.19,27.42), c_5("考纳斯",23.54,54.54), c_6("川崎",139.43,35.32), c_7("喀山",49.1,55.45), 
c_8("喀士穆",32.36,15.34), c_9("孔敬",102.5,16.25), c_10("库尔纳",89.34,22.49), c_11("基加利",30.05,-1.59),
c_12("京斯顿",167.58,-29.03);
Satelite s_0, s_1, s_2, s_3, s_4, s_5, s_6, s_7, s_8;
vector<Satelite> list_of_satelite;//卫星列表
vector<City>list_of_City;//城市列表
vector<Grid>list_of_Grid;//网格列表
vector<Area>list_of_Area;//区域列表
vector<Point>list_of_Point;//点列表
string Second_to_Hour_minites(int second)//秒数转时、分、秒
{
	int hour = second / 3600;
	int minites = (second % 3600) / 60;
	int second_s = (second % 3600) % 60;
	string result = "";
	result = to_string(hour) + " 时" + to_string(minites) + " 分" + to_string(second_s) + " 秒";
	return result;
}
double to_rad(double reg)//转为弧度
{
	return (reg / 180) * Pi;
}
Coordinates long_lati_to_coordinates(Long_la l_a)//经纬度转坐标
{
	double longi = to_rad(l_a.longitude);
	double lati = to_rad(l_a.latitude);
	double x = Radius * cos(lati) * cos(longi);
	double y = Radius * cos(lati) * sin(longi);
	double z = Radius * sin(lati);
	Coordinates c(x, y, z);
	return c;
}
Long_la pre_process(string s)
{
	double longitude;
	double latitude;
	string temp = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\t')
		{
			if (temp.size()!=0)
			{
				longitude = stod(temp);
				temp = "";
				continue;
			}
			else
			{
				continue;
			}
		}
		if (i == s.size()-1)
		{
			latitude = stod(temp);
		}
		temp += s[i];
	}
	Long_la l_a(longitude,latitude);
	return l_a;
}
double Cal_Included_Angle(Coordinates start , Coordinates end)
{
	double result = ((start.x * end.x) + (start.y * end.y) + (start.z * end.z)) / (sqrt((start.x * start.x) + (start.y * start.y) + (start.z * start.z)) * sqrt((end.x * end.x) + (end.y * end.y) + (end.z * end.z)));
	return abs(acos(result)* 180 / Pi);//转化为角度的绝对值
}
void Cal_Center()
{
	for (int i = 0; i < list_of_satelite.size(); i++)
	{
		
		for (int j = 0; j < list_of_satelite[i].time_coordinates.size(); j++)
		{
			double t_x = 0;
			double t_y = 0;
			double t_z = 0;
			for (int k = 0; k < list_of_satelite[i].time_coordinates[j].size(); k++)
			{
				t_x += list_of_satelite[i].time_coordinates[j][k].x;
				t_y += list_of_satelite[i].time_coordinates[j][k].y;
				t_z += list_of_satelite[i].time_coordinates[j][k].z;
			}
			t_x /= 21;
			t_y /= 21;
			t_z /= 21;
			Coordinates c(t_x, t_y, t_z);
			list_of_satelite[i].time_center.push_back(c);
			list_of_satelite[i].alpha.push_back(Cal_Included_Angle(list_of_satelite[i].time_coordinates[j][0], c));
		}

	}
}
void Initial_City()
{
	list_of_City.clear();
	list_of_City.push_back(c_0);
	list_of_City.push_back(c_1);
	list_of_City.push_back(c_2);
	list_of_City.push_back(c_3);
	list_of_City.push_back(c_4);
	list_of_City.push_back(c_5);
	list_of_City.push_back(c_6);
	list_of_City.push_back(c_7);
	list_of_City.push_back(c_8);
	list_of_City.push_back(c_9);
	list_of_City.push_back(c_10);
	list_of_City.push_back(c_11);
	list_of_City.push_back(c_12);
	for (int i = 0; i < list_of_City.size(); i++)
	{
		list_of_City[i].loc_coordinates = long_lati_to_coordinates(list_of_City[i].loc_long_la);
	}
}
void Initial_satelite()
{
	list_of_satelite.clear();
	list_of_satelite.push_back(s_0);
	list_of_satelite.push_back(s_1);
	list_of_satelite.push_back(s_2);
	list_of_satelite.push_back(s_3);
	list_of_satelite.push_back(s_4);
	list_of_satelite.push_back(s_5);
	list_of_satelite.push_back(s_6);
	list_of_satelite.push_back(s_7);
	list_of_satelite.push_back(s_8);
}
void Read_File()//读取文件
{
	for (int i = 0; i < 9; i++)
	{
		fstream fin;
		string Filename = "SatCoverInfo_" + to_string(i);
		Filename += ".txt";
		fin.open(Filename);
		string buffer;//缓冲区
		int k = 0;//记录当前行数
		vector<Long_la> temp;
		vector<Coordinates> temp1;
		while (!fin.eof())
		{
			getline(fin, buffer);
			if (k%22 == 0)
			{
				if (k == 0)
				{
					k++;
					continue;
				}
				list_of_satelite[i].time_long_la.push_back(temp);
				list_of_satelite[i].time_coordinates.push_back(temp1);
				list_of_satelite[i].ID = 0;
				temp.clear();
				temp1.clear();
			} 
			else
			{
				Long_la temp_l_a = pre_process(buffer);
				Coordinates temp_c = long_lati_to_coordinates(temp_l_a);
				temp.push_back(temp_l_a);
				temp1.push_back(temp_c);
			}
			k++;
		}
		fin.close();
	}
}
void Time_Window_Quchong()//时间窗口去重
{
	for (int i = 0; i < list_of_City.size(); i++)
	{
		for (int j = 0; j < list_of_City[i].Time_Gap_Satelite.size(); j++)
		{
			for (int k = 0; k < list_of_City[i].Time_Gap_Satelite.size(); k++)
			{
				int start_1 = list_of_City[i].Time_Gap_Satelite[j].start_time;
				int end_1 = list_of_City[i].Time_Gap_Satelite[j].end_time;
				int start_2 = list_of_City[i].Time_Gap_Satelite[k].start_time;
				int end_2 = list_of_City[i].Time_Gap_Satelite[k].end_time;
				if (k == j)
				{
					continue;
				}

				if (end_1 < start_2) //两个区间无交集
				{
					continue;
				}
				else if (end_2 < start_1)//两个区间无交集
				{
					continue;
				}
				else if (start_1 <= start_2 && end_2 <= end_1)//两个区间相互包含
				{
					list_of_City[i].Time_Gap_Satelite.erase(list_of_City[i].Time_Gap_Satelite.begin() + k);
					k -= 1;
				}
				else if (start_2<=start_1 && end_1 <= end_2)//两个区间相互包含
				{
					list_of_City[i].Time_Gap_Satelite.erase(list_of_City[i].Time_Gap_Satelite.begin() + j);
					j -= 1;
				}
				else if (end_1 >= start_2)//两个区间相交
				{
					int new_start = start_1;
					int new_end = end_2;
					list_of_City[i].Time_Gap_Satelite.erase(list_of_City[i].Time_Gap_Satelite.begin() + k);
					list_of_City[i].Time_Gap_Satelite.erase(list_of_City[i].Time_Gap_Satelite.begin() + j);
					k -= 1;
					j -= 1;
					Time_Window new_tw(new_start, new_end);
					list_of_City[i].Time_Gap_Satelite.push_back(new_tw);
				}
				else if (end_2 >= start_1)//两个区间相交
				{
					int new_start = start_2;
					int new_end = end_1;
					list_of_City[i].Time_Gap_Satelite.erase(list_of_City[i].Time_Gap_Satelite.begin() + k);
					list_of_City[i].Time_Gap_Satelite.erase(list_of_City[i].Time_Gap_Satelite.begin() + j);
					k -= 1;
					j -= 1;
					Time_Window new_tw(new_start, new_end);
					list_of_City[i].Time_Gap_Satelite.push_back(new_tw);
				}
			}

		}

	}

}
void Cal_Time_Window_City()//计算星座对每个城市的时间窗口
{
	for (int i = 0; i < list_of_City.size(); i++)
	{
		Coordinates city = list_of_City[i].loc_coordinates;
		for (int j = 0; j < list_of_satelite.size(); j++)
		{
			int check = 0;
			int start_time = 0;
			int end_time = 0;
			for (int k = 0; (k < list_of_satelite[j].time_center.size()); k++)
			{
				double beta = Cal_Included_Angle(list_of_satelite[j].time_center[k], city);
				if (beta <= list_of_satelite[j].alpha[k])
				{
					if (check == 0)
					{
						start_time = k;
						check = 1;
						continue;
					}
				}
				else
				{
					if (check == 1)
					{
						end_time = k;
						Time_Window t_w(start_time, end_time);
						list_of_City[i].Time_Gap_Satelite.push_back(t_w);
						check = 0;
						continue;
					}
				}
			}
		}
	}
	//for (int i = 0; i < list_of_City.size(); i++)
	//{
	//	int gap = 0;
	//	int max_gap = 0;
	//	int start = 0;
	//	int end = 0;
	//	for (int j = 0; j < list_of_City[i].Time_Gap_Satelite.size(); j++)
	//	{
	//		if (j == list_of_City[i].Time_Gap_Satelite.size() - 1 )
	//		{
	//			if (j==0)
	//			{
	//				gap = list_of_City[i].Time_Gap_Satelite[j].start_time - 0;
	//				start = 0;
	//				end = list_of_City[i].Time_Gap_Satelite[j].start_time;
	//				Time_Window temp(start, end);
	//				list_of_City[i].Gap.push_back(temp);
	//				if (gap > max_gap)
	//				{
	//					max_gap = gap;
	//					list_of_City[i].max_gap.start_time = start;
	//					list_of_City[i].max_gap.end_time = end;
	//				}
	//			}
	//			gap = 86400 - list_of_City[i].Time_Gap_Satelite[j].end_time;
	//			start = list_of_City[i].Time_Gap_Satelite[j].end_time;
	//			end = 86400;
	//			Time_Window temp(start, end);
	//			list_of_City[i].Gap.push_back(temp);
	//		}
	//		else if (j == 0)
	//		{
	//			gap = list_of_City[i].Time_Gap_Satelite[j].start_time - 0;
	//			start = 0;
	//			end = list_of_City[i].Time_Gap_Satelite[j].start_time;
	//			Time_Window temp(start, end);
	//			list_of_City[i].Gap.push_back(temp);
	//			if (list_of_City[i].Time_Gap_Satelite[j + 1].start_time - list_of_City[i].Time_Gap_Satelite[j].end_time > gap)
	//			{
	//				start = list_of_City[i].Time_Gap_Satelite[j].end_time;
	//				end = list_of_City[i].Time_Gap_Satelite[j + 1].start_time;
	//				gap = end - start;
	//				Time_Window temp(start, end);
	//				list_of_City[i].Gap.push_back(temp);
	//			}
	//			
	//		}
	//		/*else if (list_of_City[i].Time_Gap_Satelite[j].end_time >= list_of_City[i].Time_Gap_Satelite[j + 1].start_time)
	//		{
	//			list_of_City[i].Time_Gap_Satelite[j].end_time = max(list_of_City[i].Time_Gap_Satelite[j + 1].end_time, list_of_City[i].Time_Gap_Satelite[j].end_time);
	//			list_of_City[i].Time_Gap_Satelite.erase(list_of_City[i].Time_Gap_Satelite.begin() + (j + 1));
	//			j -= 1;

	//		}*/
	//		else
	//		{
	//			gap = list_of_City[i].Time_Gap_Satelite[j + 1].start_time - list_of_City[i].Time_Gap_Satelite[j].end_time;
	//			start = list_of_City[i].Time_Gap_Satelite[j].end_time;
	//			end = list_of_City[i].Time_Gap_Satelite[j + 1].start_time;
	//			Time_Window temp(start, end);
	//			list_of_City[i].Gap.push_back(temp);
	//		}
	//		if (gap > max_gap)
	//		{
	//			max_gap = gap;
	//			list_of_City[i].max_gap.start_time = start;
	//			list_of_City[i].max_gap.end_time = end;
	//		}

	//	}
	//}
	//for (int i = 0; i < list_of_City.size(); i++)
	//{
	//	int max = 0;
	//	for (int j = 0; j < list_of_City[i].Time_Gap_Satelite.size(); j++)
	//	{
	//		if (list_of_City[i].Time_Gap_Satelite[j].end_time - list_of_City[i].Time_Gap_Satelite[j].start_time > max)
	//		{
	//			max = list_of_City[i].Time_Gap_Satelite[j].end_time - list_of_City[i].Time_Gap_Satelite[j].start_time;
	//			list_of_City[i].max_time_window.start_time = list_of_City[i].Time_Gap_Satelite[j].start_time;
	//			list_of_City[i].max_time_window.end_time = list_of_City[i].Time_Gap_Satelite[j].end_time;
	//		}

	//	}

	//}
	//int max_time_window = 0;
	//int max_time_gap = 0;
	//int max_time_window_index = 0;
	//int max_time_gap_index = 0;
	//for (int i = 0; i < list_of_City.size(); i++)
	//{
	//	if ((list_of_City[i].max_time_window.end_time - list_of_City[i].max_time_window.start_time) > max_time_window)
	//	{
	//		max_time_window = list_of_City[i].max_time_window.end_time - list_of_City[i].max_time_window.start_time;
	//		max_time_window_index = i;
	//	}
	//	if ((list_of_City[i].max_gap.end_time - list_of_City[i].max_gap.start_time) > max_time_gap)
	//	{
	//		max_time_gap = list_of_City[i].max_gap.end_time - list_of_City[i].max_gap.start_time;
	//		max_time_gap_index = i;
	//	}
	//}


	//cout << "最大时间窗口是：" << list_of_City[max_time_window_index].name<<endl;
	//cout << "覆盖时间是从：" << Second_to_Hour_minites(list_of_City[max_time_window_index].max_time_window.start_time) << " 到 " << Second_to_Hour_minites(list_of_City[max_time_window_index].max_time_window.end_time) << endl;
	//cout << "共：" << Second_to_Hour_minites(max_time_window)<<endl;
	//cout << "最大时间空隙是：" << list_of_City[max_time_gap_index].name << endl;
	//cout << "覆盖时间是从：" << Second_to_Hour_minites(list_of_City[max_time_gap_index].max_gap.start_time) << " 到 " << Second_to_Hour_minites(list_of_City[max_time_gap_index].max_gap.end_time) << endl;
	//cout << "共：" << Second_to_Hour_minites(max_time_gap);
}
int check_Area_inside(Coordinates center, double alpha, Area g)//判断网格是否在范围内 1：在 2：不在 3：部分在
{
	if (Cal_Included_Angle(center, long_lati_to_coordinates(g.left_bottom)) <= alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.left_top)) <= alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.right_bottom)) <= alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.right_top)) <= alpha)
	{
		return 1;
	}
	else if (Cal_Included_Angle(center, long_lati_to_coordinates(g.left_bottom)) > alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.left_top)) > alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.right_bottom)) > alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.right_top)) > alpha)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}
void Initial_List_of_Area()
{
	list_of_Area.clear();
	for (double i = 75; i <= 130; i += 5)
	{
		for (double j = 0; j <= 50; j += 5)
		{
			Area a(Long_la(i, j), Long_la(i, j + 5), Long_la(i + 5, j + 5), Long_la(i + 5, j));
			list_of_Area.push_back(a);
		}
	}
}
vector<int> Cal_Time_Window_Area()
{
	for (int i = 0; i < list_of_Area.size(); i++)
	{
		Area a = list_of_Area[i];
		for (int j = 0; j < list_of_satelite.size(); j++)
		{
			int start_time = 0;
			int end_time = 0;
			int check = 0;
			for (int k = 0; k < list_of_satelite[j].alpha.size(); k++)
			{
				Coordinates center_temp = list_of_satelite[j].time_center[k];
				double alpha_temp = list_of_satelite[j].alpha[k];
				if (check_Area_inside(center_temp , alpha_temp ,a ) == 1)
				{
					if (check == 0)
					{
						start_time = k;
						check = 1;
						continue;
					}
				}
				else
				{
					if (check == 1)
					{
						end_time = k;
						Time_Window t_w(start_time, end_time);
						list_of_Area[i].Time_Gap_Satelite.push_back(t_w);
						check = 0;
						continue;
					}
				}
			}
		}
	}
	for (int i = 0; i < list_of_Area.size(); i++)
	{
		for (int j = 0; j < list_of_Area[i].Time_Gap_Satelite.size(); j++)
		{
			for (int k = j; k < list_of_Area[i].Time_Gap_Satelite.size(); k++)
			{
				if (list_of_Area[i].Time_Gap_Satelite[j].start_time > list_of_Area[i].Time_Gap_Satelite[k].start_time)
				{
					Time_Window temp;
					temp.start_time = list_of_Area[i].Time_Gap_Satelite[j].start_time;
					temp.end_time = list_of_Area[i].Time_Gap_Satelite[j].end_time;
					list_of_Area[i].Time_Gap_Satelite[j].start_time = list_of_Area[i].Time_Gap_Satelite[k].start_time;
					list_of_Area[i].Time_Gap_Satelite[j].end_time = list_of_Area[i].Time_Gap_Satelite[k].end_time;
					list_of_Area[i].Time_Gap_Satelite[k].start_time = temp.start_time;
					list_of_Area[i].Time_Gap_Satelite[k].end_time = temp.end_time;
				}
			}
		}
	}
	for (int i = 0; i < list_of_Area.size(); i++)
	{
		int gap = 0;
		int max_gap = 0;
		int start = 0;
		int end = 0;
		for (int j = 0; j < list_of_Area[i].Time_Gap_Satelite.size(); j++)
		{
			if (j == list_of_Area[i].Time_Gap_Satelite.size()-1)
			{
				gap = 86400 - list_of_Area[i].Time_Gap_Satelite[j].end_time;
				start = list_of_Area[i].Time_Gap_Satelite[j].end_time;
				end = 86400;
				Time_Window temp(start , end);
				list_of_Area[i].Gap.push_back(temp);
				if (j == 0)
				{
					Time_Window temp(0, list_of_Area[i].Time_Gap_Satelite[j].start_time);
					list_of_Area[i].Gap.push_back(temp);
					if (list_of_Area[i].Time_Gap_Satelite[j].start_time - 0 > gap)
					{
						gap = list_of_Area[i].Time_Gap_Satelite[j].start_time - 0;
						start = 0;
						end = list_of_Area[i].Time_Gap_Satelite[j].start_time;
					}
				}
			}
			else if (j == 0 )
			{
				gap = list_of_Area[i].Time_Gap_Satelite[j].start_time - 0;
				start = 0;
				end = list_of_Area[i].Time_Gap_Satelite[j].start_time;
				Time_Window temp(start, end);
				list_of_Area[i].Gap.push_back(temp);
				Time_Window temp_1(list_of_Area[i].Time_Gap_Satelite[j].end_time, list_of_Area[i].Time_Gap_Satelite[j + 1].start_time);
				list_of_Area[i].Gap.push_back(temp_1);
				if (list_of_Area[i].Time_Gap_Satelite[j + 1].start_time - list_of_Area[i].Time_Gap_Satelite[j].end_time > gap)
				{
					start = list_of_Area[i].Time_Gap_Satelite[j].end_time;
					end = list_of_Area[i].Time_Gap_Satelite[j + 1].start_time;
					gap = end - start;
					
				}
			}
			/*else if (list_of_Area[i].Time_Gap_Satelite[j].end_time >= list_of_Area[i].Time_Gap_Satelite[j+1].start_time)
			{
				list_of_Area[i].Time_Gap_Satelite[j].end_time = max(list_of_Area[i].Time_Gap_Satelite[j + 1].end_time , list_of_Area[i].Time_Gap_Satelite[j].end_time);
				list_of_Area[i].Time_Gap_Satelite.erase(list_of_Area[i].Time_Gap_Satelite.begin() + (j + 1));
				j -= 1;
			}*/
			else
			{
				gap = list_of_Area[i].Time_Gap_Satelite[j + 1].start_time - list_of_Area[i].Time_Gap_Satelite[j].end_time;
				start = list_of_Area[i].Time_Gap_Satelite[j].end_time;
				end = list_of_Area[i].Time_Gap_Satelite[j + 1].start_time;
				Time_Window temp(start, end);
				list_of_Area[i].Gap.push_back(temp);
			}
			if (gap > max_gap )
			{
				max_gap = gap;
				list_of_Area[i].max_gap.start_time = start;
				list_of_Area[i].max_gap.end_time = end;
			}
		}
	}
	int max_gap_index = 0;
	int max_gap = 99999;
	for (int i = 0; i < list_of_Area.size(); i++)
	{
		if ((list_of_Area[i].max_gap.end_time-list_of_Area[i].max_gap.start_time) < max_gap)
		{
			max_gap = (list_of_Area[i].max_gap.end_time - list_of_Area[i].max_gap.start_time);
			max_gap_index = i;
		}
	}
	vector<int>result;
	result.push_back(max_gap_index);
	for (int i = 0; i < list_of_Area.size(); i++)
	{
		double sqare = 0;
		for (int j = 0; j < list_of_Area[i].Gap.size(); j++)
		{
			sqare += (double (list_of_Area[i].Gap[j].end_time / 1000.0) - double (list_of_Area[i].Gap[j].start_time) /1000.0) * (double (list_of_Area[i].Gap[j].end_time) /1000.0 -(double (list_of_Area[i].Gap[j].start_time) /1000.0));
		}
		list_of_Area[i].Square = sqare;
	}
	double max_sqare = 999999.0;
	int max_sqare_index = 0;
	for (int i = 0; i < list_of_Area.size(); i++)
	{
		if (list_of_Area[i].Square < max_sqare)
		{
			max_sqare = list_of_Area[i].Square;
			max_sqare_index = i;
		}
	}
	result.push_back(max_sqare_index);
	return result;
}
vector<int> Cal_Time_Window_Point(vector <int> index)
{
	Area temp = list_of_Area[index[0]];
	list_of_Point.clear();
	for (double i = temp.left_bottom.longitude; i <= temp.right_bottom.longitude; i+= 1)
	{
		for (double j = temp.left_bottom.latitude; j <= temp.right_top.latitude ; j+= 1)
		{
			Point new_one(i, j);
			list_of_Point.push_back(new_one);
		}
	}
	for (int i = 0; i < list_of_Point.size(); i++)
	{
		Point temp = list_of_Point[i];
		for (int j = 0; j < list_of_satelite.size(); j++)
		{
			int check = 0;
			int start = 0;
			int end = 0;
			for (int k = 0; k < list_of_satelite[j].alpha.size(); k++)
			{
				double beta = Cal_Included_Angle(list_of_satelite[j].time_center[k], long_lati_to_coordinates (temp.loc_long_la));
				if (beta <= list_of_satelite[j].alpha[k])
				{
					if (check == 0)
					{
						start = k;
						check = 1;
						continue;
					}
				}
				else
				{
					if (check == 1)
					{
						end = k;
						Time_Window t_w(start, end);
						list_of_Point[i].Time_Gap_Satelite.push_back(t_w);
						check = 0;
						continue;
					}
				}
			}	
		}
	}
	for (int i = 0; i < list_of_Point.size(); i++)
	{
		for (int j = 0; j < list_of_Point[i].Time_Gap_Satelite.size(); j++)
		{
			for (int k = j; k < list_of_Point[i].Time_Gap_Satelite.size(); k++)
			{
				if (list_of_Point[i].Time_Gap_Satelite[j].start_time > list_of_Point[i].Time_Gap_Satelite[k].start_time)
				{
					Time_Window temp;
					temp.start_time = list_of_Point[i].Time_Gap_Satelite[j].start_time;
					temp.end_time = list_of_Point[i].Time_Gap_Satelite[j].end_time;
					list_of_Point[i].Time_Gap_Satelite[j].start_time = list_of_Point[i].Time_Gap_Satelite[k].start_time;
					list_of_Point[i].Time_Gap_Satelite[j].end_time = list_of_Point[i].Time_Gap_Satelite[k].end_time;
					list_of_Point[i].Time_Gap_Satelite[k].start_time = temp.start_time;
					list_of_Point[i].Time_Gap_Satelite[k].end_time = temp.end_time;
				}
			}
		}
	}
	for (int i = 0; i < list_of_Point.size(); i++)
	{
		int gap = 0;
		int max_gap = 0;
		int start = 0;
		int end = 0;
		for (int j = 0; j < list_of_Point[i].Time_Gap_Satelite.size(); j++)
		{
			if (j == list_of_Point[i].Time_Gap_Satelite.size() - 1)
			{
				gap = 86400 - list_of_Point[i].Time_Gap_Satelite[j].end_time;
				start = list_of_Point[i].Time_Gap_Satelite[j].end_time;
				end = 86400;
				Time_Window temp(start, end);
				list_of_Point[i].Gap.push_back(temp);
				if (j == 0)
				{
					Time_Window temp(0, list_of_Point[i].Time_Gap_Satelite[j].start_time);
					list_of_Point[i].Gap.push_back(temp);
					if (gap < list_of_Point[i].Time_Gap_Satelite[j].start_time - 0)
					{
						start = 0;
						end = list_of_Point[i].Time_Gap_Satelite[j].start_time;
						gap = list_of_Point[i].Time_Gap_Satelite[j].start_time - 0;
						
					}
				}
			}
			else if (j == 0)
			{
				gap = list_of_Point[i].Time_Gap_Satelite[j].start_time - 0;
				start = 0;
				end = list_of_Point[i].Time_Gap_Satelite[j].start_time;
				Time_Window temp(start, end);
				list_of_Point[i].Gap.push_back(temp);
				Time_Window temp_1(list_of_Point[i].Time_Gap_Satelite[j].end_time, list_of_Point[i].Time_Gap_Satelite[j + 1].start_time);
				list_of_Point[i].Gap.push_back(temp_1);
				if (list_of_Point[i].Time_Gap_Satelite[j + 1].start_time - list_of_Point[i].Time_Gap_Satelite[j].end_time > gap)
				{
					start = list_of_Point[i].Time_Gap_Satelite[j].end_time;
					end = list_of_Point[i].Time_Gap_Satelite[j + 1].start_time;
					gap = end - start;
				
				}
			}
			/*else if (list_of_Point[i].Time_Gap_Satelite[j].end_time >= list_of_Point[i].Time_Gap_Satelite[j + 1].start_time)
			{
				list_of_Point[i].Time_Gap_Satelite[j].end_time = max(list_of_Point[i].Time_Gap_Satelite[j + 1].end_time, list_of_Point[i].Time_Gap_Satelite[j].end_time);
				list_of_Point[i].Time_Gap_Satelite.erase(list_of_Point[i].Time_Gap_Satelite.begin() + (j + 1));
				j -= 1;
			}*/
			else
			{
				gap = list_of_Point[i].Time_Gap_Satelite[j + 1].start_time - list_of_Point[i].Time_Gap_Satelite[j].end_time;
				start = list_of_Point[i].Time_Gap_Satelite[j].end_time;
				end = list_of_Point[i].Time_Gap_Satelite[j + 1].start_time;
				Time_Window temp(start, end);
				list_of_Point[i].Gap.push_back(temp);
			}
			if (gap > max_gap)
			{
				max_gap = gap;
				list_of_Point[i].max_gap.start_time = start;
				list_of_Point[i].max_gap.end_time = end;
			}
		}
	}
	int max_index = 0;
	int max_gap = 99999;
	for (int i = 0; i < list_of_Point.size(); i++)
	{
		if ((list_of_Point[i].max_gap.end_time - list_of_Point[i].max_gap.start_time) < max_gap)
		{
			max_gap = (list_of_Point[i].max_gap.end_time - list_of_Point[i].max_gap.start_time);
			max_index = i;
		}
	}
	vector<int>result;
	result.push_back(max_index);
	for (int i = 0; i < list_of_Point.size(); i++)
	{
		double sqare = 0;
		for (int j = 0; j < list_of_Point[i].Gap.size(); j++)
		{
			sqare += ((double (list_of_Point[i].Gap[j].end_time)/1000.0 - double( list_of_Point[i].Gap[j].start_time)/1000.0) * (double (list_of_Point[i].Gap[j].end_time)/1000.0 - double(list_of_Point[i].Gap[j].start_time)/1000.0));
		}
		list_of_Point[i].Square = sqare;
	}
	double max_sqare = 999999.0;
	int max_sqare_index = 0;
	for (int i = 0; i < list_of_Point.size(); i++)
	{
		if (list_of_Point[i].Square < max_sqare)
		{
			max_sqare = list_of_Point[i].Square;
			max_sqare_index = i;
		}
	}
	result.push_back(max_sqare_index);
	return result;
}
void Initial_List_of_Grid()
{
	list_of_Grid.clear();
	for (double i = 75; i < 135; i+=5)
	{
		for (double j = 0; j < 55; j+=5)
		{
			Grid g( Long_la(i,j), Long_la(i,j+5), Long_la(i+5,j+5), Long_la(i+5,j)) ;
			list_of_Grid.push_back(g);
		}

	}
}
int check_grid_inside(Coordinates center, double alpha, Grid g)//判断网格是否在范围内 1：在 2：不在 3：部分在
{
	if (Cal_Included_Angle(center,long_lati_to_coordinates(g.left_bottom)) <= alpha 
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.left_top)) <= alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.right_bottom)) <= alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.right_top)) <= alpha)
	{
		return 1;
	}
	else if (Cal_Included_Angle(center, long_lati_to_coordinates(g.left_bottom)) > alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.left_top)) > alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.right_bottom)) > alpha
		&& Cal_Included_Angle(center, long_lati_to_coordinates(g.right_top)) > alpha)
	{
		return 2;
	}
	else
	{
		return 3;
	}

}
vector<Grid> Tear_Grid_Apart(Grid G)//将网格一分为四
{
	Long_la l_b = G.left_bottom;  
	Long_la l_t = G.left_top;
	Long_la r_t = G.right_top;
	Long_la r_b = G.right_bottom;
	Grid left_top(Long_la(l_b.longitude , (l_b.latitude + l_t.latitude)/2), l_t, Long_la((l_b.longitude + r_b.longitude)/2,l_t.latitude), Long_la(((l_b.longitude + r_b.longitude) / 2), ((l_b.latitude + l_t.latitude) / 2)));
	Grid left_bottom(l_b, Long_la(l_b.longitude, (l_b.latitude + l_t.latitude) / 2), Long_la(((l_b.longitude + r_b.longitude) / 2), ((l_b.latitude + l_t.latitude) / 2)), Long_la((((l_b.longitude + r_b.longitude) / 2)) , l_b.latitude));
	Grid right_top(Long_la(((l_b.longitude + r_b.longitude) / 2), ((l_b.latitude + l_t.latitude) / 2)), Long_la((l_b.longitude + r_b.longitude) / 2, l_t.latitude), r_t, Long_la(r_b.longitude , ((l_b.latitude + l_t.latitude) / 2)));
	Grid right_bottom(Long_la((((l_b.longitude + r_b.longitude) / 2)), l_b.latitude), Long_la(((l_b.longitude + r_b.longitude) / 2), ((l_b.latitude + l_t.latitude) / 2)), Long_la(r_b.longitude, ((l_b.latitude + l_t.latitude) / 2)), r_b);
	vector<Grid>result;
	result.push_back(left_top);
	result.push_back(left_bottom);
	result.push_back(right_top);
	result.push_back(right_bottom);
	return result;
}
double Cal_Grid_Area( Grid G)
{
	double row = G.left_top.latitude - G.left_bottom.latitude;
	double col = G.right_bottom.longitude - G.left_bottom.longitude;
	return row * col;

}
bool check_already_have(Grid g)
{
	for (int i = 0; i < list_of_Grid.size(); i++)
	{
		Grid temp = list_of_Grid[i];
		if (g.left_bottom.longitude >= temp.left_bottom.longitude && g.left_bottom.latitude >= temp.left_bottom.latitude
			&& g.right_top.longitude <= temp.right_bottom.longitude && g.right_top.latitude <= temp.right_top.latitude && temp.flag == 1)
		{
			return true;
		}

	}
	return false;

}
double check_grid_rate( int time)
{
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < list_of_Grid.size(); i++)
		{
			Grid temp = list_of_Grid[i];
			if (list_of_Grid[i].flag == 1)
			{
				continue;
			}
			else if (check_grid_inside(list_of_satelite[j].time_center[time], list_of_satelite[j].alpha[time], temp) == 1)
			{
				list_of_Grid[i].flag = 1;//标记置为覆盖
				continue;
			}
			else if (check_grid_inside(list_of_satelite[j].time_center[time], list_of_satelite[j].alpha[time], temp) == 2)
			{
				list_of_Grid[i].flag = 2;//标记置为没有覆盖
				continue;
			}
			else
			{
				list_of_Grid[i].flag = 3;//标记置为不确定
				if (Cal_Grid_Area(temp) / 25.0 < 0.01)
				{
					continue;
				}
				else
				{
					vector<Grid>temp_Grid = Tear_Grid_Apart(temp);
					list_of_Grid.erase(list_of_Grid.begin() + i);
					i -= 1;
					for (int k = 0; k < temp_Grid.size(); k++)
					{
						if (!check_already_have(temp_Grid[k]))
						{
							temp_Grid[k].flag = 3;
							list_of_Grid.push_back(temp_Grid[k]);

						}
					}
				}
				
			}
		}
	}
	double result = 0.0;
	for (int i = 0; i < list_of_Grid.size(); i++)
	{
		if (list_of_Grid[i].flag == 1)
		{
			result += Cal_Grid_Area(list_of_Grid[i]);
		}
	}
	return result / (60.0 * 55.0);
}
void Curve_Grid_Rate()//画出瞬时覆盖率计算曲线
{
	initgraph(1080, 720);
	setorigin(0, 360);
	setaspectratio(1, -1);
	setbkcolor(WHITE);
	cleardevice();
	for (int i = 0; i < list_of_satelite[0].alpha.size(); i+=80)
	{
		Initial_List_of_Grid();
		int x = i / 80;
		int y = check_grid_rate(i) * 500;
		putpixel(x, y, RED);
	}
	saveimage(_T("C:\\Users\\23645\\Desktop\\瞬时覆盖率计算.jpg"));
	system("pause");
	closegraph();
}
void Graph_Grid_Rate(int time , int flag)
{
	initgraph(1080, 715);
	setbkcolor(WHITE);
	setorigin(0, 715);
	setaspectratio(1, -1);
	cleardevice();
	setlinecolor(BLACK);
	for (int i = 0; i <= 1080; i+=90)
	{
		line(i, 0, i, 720);
	}
	for (int i = 0; i <= 715; i += 65)
	{
		line(0, i, 1080, i);
	}
	for (int i = 0; i < list_of_Grid.size(); i++)
	{
	Grid g = list_of_Grid[i];
		if (g.flag == 1)
		{
			setfillcolor(RED);
			fillrectangle((g.left_bottom.longitude-75) * 18, (g.left_top.latitude-0) * 13, (g.right_top.longitude-75) * 18, (g.right_bottom.latitude-0) * 13);
		}
		if (g.flag == 3)
		{
			setfillcolor(BLUE);
			fillrectangle((g.left_bottom.longitude - 75) * 18, (g.left_top.latitude - 0) * 13, (g.right_top.longitude - 75) * 18, (g.right_bottom.latitude - 0) * 13);
		}
	}
	string filename;
	if (flag == 1)//瞬时
	{
		filename = "C:\\Users\\23645\\Desktop\\" + to_string(time) + "时刻覆盖率.jpg";
	}
	if (flag == 2)//累计
	{
		filename = "C:\\Users\\23645\\Desktop\\" + to_string(time) + "小时累计覆盖率.jpg";
	}
	saveimage(filename.c_str());
	system("pause");
	closegraph();
}
void Paint_Gante()//绘制甘特图
{
	initgraph(1080, 720);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setlinecolor(BLACK);
	outtextxy(500, 30, "各城市时间窗口");
	for (int i = 0; i <= 24; i++)
	{
		line(110+(i*40), 50, 110 + (i * 40), 670);
		outtextxy(105 + (i * 40), 675, to_string(i).c_str());
	}
	for (int i = 0; i < 13; i++)
	{
		outtextxy(10, 50*(i+1), list_of_City[i].name.c_str());
	}
	
	setfillcolor(GREEN);
	for (int i = 0; i < list_of_City.size(); i++)
	{
		for (int j = 0; j < list_of_City[i].Time_Gap_Satelite.size(); j++)
		{
			int left = ((float)list_of_City[i].Time_Gap_Satelite[j].start_time / 3600.0) * 40 + 110;
			int right = ((float)list_of_City[i].Time_Gap_Satelite[j].end_time / 3600.0) * 40 + 110;
			int top = 50 * (i + 1);
			int bottom = top + 30;
			fillrectangle(left,top,right,bottom);
		}

	}
	saveimage(_T("C:\\Users\\23645\\Desktop\\时间窗口甘特图.jpg"));
	system("pause");
	closegraph();
}
void Menu();
void Initial_All()
{
	cout << "正在载入数据。。。"<<endl;
	Initial_satelite();
	Initial_City();
	Read_File();
	Cal_Center();
	Initial_List_of_Grid();
	Initial_List_of_Area();
	cout << "载入完成！ 按任意键进入系统！";
	system("pause");
	Menu();
}
void First_Question()
{
	int choice;
	system("cls");
	cout << "**********第一题*********"<<endl;
	cout << "1、第一问" << endl;
	cout << "2、第二问" << endl;
	cout << "3、回到主菜单" << endl;
	cout << "请输入选择： ";
	cin >> choice;
	if (choice == 1)
	{
		system("cls");
		Cal_Time_Window_City();
		Paint_Gante();
	}
	 if (choice == 2)
	{
		system("cls");
		vector<int> index = Cal_Time_Window_Area();
		vector<int> result=Cal_Time_Window_Point(index);
		cout << "时间间隙最大值最小的点的坐标:"<<endl;
		cout << "经度为 ：" << list_of_Point[result[0]].loc_long_la.longitude << endl;
		cout<<"纬度为 ："<< list_of_Point[result[0]].loc_long_la.latitude<<endl;
		cout << "最大时间间隙为：" << Second_to_Hour_minites(list_of_Point[result[0]].max_gap.end_time - list_of_Point[result[0]].max_gap.start_time)<<endl;
	}
	 if (choice == 3)
	 {
		 Menu();
	 }
	 system("pause");
	 cout <<endl<< "按任意键返回本菜单";
	 First_Question();

}
void Second_Question()
{
	int choice;
	system("cls");
	cout << "**********第二题*********"<<endl;
	cout << "1、第一问" << endl;
	cout << "2、第二问" << endl;
	cout << "3、第三问：" << endl;
	cout << "4、第四问" << endl;
	cout << "5、回到主菜单" << endl;
	cout << "请输入选择：";
	cin >> choice;
	if (choice == 1)
	{
		Initial_List_of_Grid();
		Curve_Grid_Rate();
	}
	if (choice == 2)
	{
		int input;
		cout << "请输入所求时刻 单位为秒";
		cin >> input;
		Initial_List_of_Grid();
		check_grid_rate(input);
		Graph_Grid_Rate(input ,1);
	}
	if (choice == 3)
	{
		Initial_List_of_Grid();
		for (int i = 1; i <= 10800; i++)
		{
			check_grid_rate(i-1);
			if (i % 3600 == 0 && i != 0)
			{
				cout << "第" << Second_to_Hour_minites(i)<<"的累计覆盖率为 :" << check_grid_rate(i) * 100 << "%" << endl;
			}
		}
	}
	if (choice == 4)
	{
		Initial_List_of_Grid();
		for (int i = 1; i <= 10800; i++)
		{
			check_grid_rate(i - 1);
			if (i % 3600 == 0 && i != 0)
			{
				Graph_Grid_Rate((i / 3600), 2);
			}
		}
	}
	if (choice == 5)
	{
		Menu();
	}
	system("pause");
	cout << endl << "按任意键返回本菜单";
	Second_Question();
}
void Menu()
{
	system("cls");
	int choice;
	cout << "**********菜单***********"<<endl;
	cout << "1、第一题" << endl;
	cout << "2、第二题" << endl;
	cout << "3、退出系统" << endl;
	cin >> choice;
	if (choice == 1)
	{
		First_Question();
	}
	if (choice == 2)
	{
		Second_Question();
	}
	if (choice == 3)
	{
		exit(0);
	}
	system("pause");
	cout<<endl << "按任意键返回主菜单";
}
int main()
{
	Initial_All();
	system("pause");
	return 0;

}
