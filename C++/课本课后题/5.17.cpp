#include<iostream>
#include<vector>
#include<cmath>
#include<string>
using namespace std;
int main()
{
	char C[36] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	vector<string>innum ;//存放输入的数字
	vector<int>middle;//转换为十进制后的各个位上的数字
	vector<int>trans;//转换为目标进制后各个位上的数字
	vector<char>outnum;//存放输出的数字
	string num;//输入数字的中间量
	int innumform=0, outnumform=0;//输入数字的进制，输出数字的进制
	int sum = 0,reside;//转换为十进制后的值,玉树
	cout << "请输入数字 输入end结束" << endl;
	while (cin >> num)
	{
		if (num=="end")
		{
			break;
		}
		innum.push_back(num);
	}
	
	for (int i = 0; i < 36; i++)
	{
		for (auto &c : innum)
		{
			for (auto &d : c)
			{
				if (d==C[i])
				{
					middle.push_back(i);
				}
			}
		}
	}
	cout << "该数字的进制以及要转换的进制" << endl;
	cin >> innumform >> outnumform;
	for (unsigned int i = 0; i < middle.size(); i++)
	{
		middle[i] = middle[i]*(pow(innumform, (middle.size() - i - 1)));
		sum += middle[i];
	}
	while (sum>0)
	{
		reside = sum % outnumform;
		sum /= outnumform;
		trans.push_back(reside);
	}
	for (unsigned int i = 0; i<(trans.size()/2); i++)
	{
		int tem = trans[i];
		trans[i] = trans[trans.size() - i - 1];
		trans[trans.size() - i - 1] = tem;
	}
	for (unsigned int i = 0; i < (trans.size()); i++)
	{  
		for (int j = 0; j < 36; j++)
		{
			if (trans[i]==j)
			{
				outnum.push_back(C[j]);
			}
		}
	}
	cout << "转换后的数字为:";
	for (auto c : outnum)
	{
		cout << c;
	}
	system("pause");
	return 0;
}
