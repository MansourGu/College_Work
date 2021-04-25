#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
void swap(vector<string>&x)
{
	int ran = rand() % 51;
	string tem = x[0];
	x[0] = x[ran];
	x[ran] = tem;
};
int main()
{
	vector<string>color{ "S","H","D","C" };//花色
	vector<string>num{ "1","2","3","4","5","6","7","8","9","10","J","Q","K" };//数字
	vector<string>card;//总牌数
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			card.push_back(color[i] + num[j]);
		}
	}
	cout << "所有牌为：" << endl;
	for (auto c : card)
	{
		cout <<setw(4)<< c;
	}
	int n;
	cout <<endl<< "现在开始洗牌 (请输入1)" << endl;
	while (cin >> n)
	{
		if (n == 1) 
		{
			for (int i = 0; i < 500; i++)//洗牌
			{
				swap(card);
			}
			for (int i = 0; i < 4; i++)//发牌
			{
				cout << "第" << (i + 1) << "个人的牌是：";
				for (int j = i * 13; j < (i + 1) * 13; j++)
				{
					cout << setw(4) << card[j];
				}
				cout << endl;
			}
			cout << "如果需要重新洗牌请输入1，不需要则输入0" << endl;
		}
		else break;
	}

	system("pause");
	return 0;
}