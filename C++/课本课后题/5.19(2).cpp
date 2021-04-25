#include<iostream>
#include<vector>//此代码会将全排列重复部分抹除
using namespace std;
vector<char>result;
void CAL(vector<char>x)
{	
	if (x.size()==1)
	{
		result.push_back(x[0]);
		for (auto c : result)
		{
			cout << c;
		}
		cout << endl;
		result.clear();
		return;
	}
	for (int i = 0; i < x.size(); i++)
	{
		result.push_back(x[i]);
		vector<char>tem = x;
		tem.erase(tem.begin() + i);
		CAL(tem);
	}

}

int main()
{
	vector<char>input{ '1','2','3','4','5','6','7','8','9'};
	CAL(input);
	system("pause");
	return 0;
}