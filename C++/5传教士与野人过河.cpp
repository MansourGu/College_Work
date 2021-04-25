#include<iostream>
using namespace std;
bool trans_right_to_left(int boat_m, int boat_w, int left_m, int left_w, int right_m, int right_w, int capacity);//判断从左向右的行驶的穿上传教士和野人的数量
bool trans_left_to_right(int boat_m, int boat_w, int left_m, int left_w, int right_m,int right_w,int capacity)//判断从右向左的行驶的穿上传教士和野人的数量
{						//船上传教士    船上野人    左岸传教士   左岸野人   右岸传教士   右岸野人    船的容量
	for (int i = left_m; i >=0; i--)//左岸的传教士个数
	{
		for (int j = left_m; j >=0; j--)//左岸的野人数
		{
			if (i+j>=1&&i+j<=capacity&&(left_m-i)>=(left_w-j)&&i>=j&&(right_m+i>=right_w+j))
			{	//船上至少一个人且小于船的承载量 并且左岸走掉传教士与野人之后传教士人数要大于等于野人人数 右岸在船到达时传教士的个数应该大于等于野人个数
				cout << "从左向右的船上有" << i+boat_m << "个传教士" << j+boat_w << "个野人"<<endl;
				if(trans_right_to_left(i, j, left_m - i, left_w - j, right_m+i, right_w+j, capacity))
						return true;

			}
			continue;
		}

	}
	return false;
}
bool trans_right_to_left(int boat_m, int boat_w, int left_m, int left_w, int right_m, int right_w, int capacity)
{
	if (left_m==0&&left_w==0&&boat_m>=boat_w&&right_m>=right_w)
	{	//如果左岸的没有传教士与野人 船上的传教士大于等于野人个数 右岸的传教士大于等于野人个数 则成功运送
		cout << "运送完毕！";
		return true;
	}
	for (int i = 0; i <= right_m; i++)
	{
		for (int j = 0; j <= right_w; j++)
		{
			if (i>=j&&i+j>=1&&i+j<=capacity&&i+j<=right_m+right_w&&right_m-i>=right_w-j&&left_m+i>=left_w+j)
			{
				cout << "从右向左运送" << i << "个传教士" << j << "个野人"<<endl;
				if (trans_left_to_right(i,j,left_m,left_w,right_m-i,right_w-j,capacity))
					return true;
			}
			continue;
		}
	}
	return false;
}
int main()
{
	int missionary,wild,left,right,boat;
	cout << "请输入传教士和野人的人数：";
	cin >> wild;
	missionary = wild;
	cout << "请输入船的乘客量：";
	cin >> boat;
	trans_left_to_right(0, 0, missionary, wild, 0, 0, boat);
	system("pause");
	return 0;

}