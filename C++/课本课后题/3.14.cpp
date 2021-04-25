#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	double x=1, tem;
	int i=1;
	do
	{
		tem = x;
		x += pow(-1, i) / (2 * i + 1);
		i++;
	} while ((4*fabs(tem-x))>=1e-5);
	cout << "¦°µÄÖµÎª" << 4*x;
	system("pause");
	return 0;
}