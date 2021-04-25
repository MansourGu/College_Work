#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int>num;
	int m;
	int count = 1;
	int k = 0;
	cout << "请输入总人数：";
	cin >> m;
	cout << "请输入k值"  ;
	cin >> k;
	for (int i = 0; i < m; i++)
	{
		num.push_back(i + 1);
	}
	while (!num.empty())
	{
		if (count == k)
		{
			for (int i = 0; i < k-1; i++)
			{
				num.push_back(num[i]);
			}
			
			for (int j = 0; j < k; j++)
			{
				num.erase(num.begin());
			}
			count = 1;
			for (auto c : num)
			{
				cout << c<<"  ";
			}
			cout << endl;
			continue;
		}
		count++;
			if (num.size()==1)
			{
				break;
			}
	}
	system("pause");
		return 0;
}