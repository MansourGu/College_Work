#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int>v1;
	int num;
	cout << "请输入一组整数 输入字母结束" << endl;
	while (cin>>num)
	{
		v1.push_back(num);
	}
	cout << "将相邻两数相加输出为：" << endl;
	for (int i = 0; i < v1.size(); )
	{
		if (i+1==v1.size())
		{
			cout << "最后一个元素没有参与求和运算 这个数是" << v1[i];
			break;
		}
		cout << v1[i] + v1[i + 1]<<"  ";
		i += 2;
	}
	cout <<endl<< "将头尾元素两两配对输出为：" << endl;
	for (int i = 0; i < v1.size()/2+1; i++)
	{
		if (i == (v1.size()-i-1))
		{
			cout << "该列数有奇数个数字中间的数字没有参与配对该数是：" << v1[i];
			break;
	    }
		cout << v1[i] + v1[v1.size() - i - 1]<<"  ";
	}
	system("pause");
	return 0;
}