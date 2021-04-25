#include<iostream>
using namespace std;
int main()
{
	int k = 1, m = 0;
	for ( ; k <=50; k++)
	{
		if (m >= 10)
			break;
		if (m%2 ==0)
		{
			m += 5;
		    continue;
		}
		m -= 3;
	}
	cout << m << endl;
	system("pause");
	return 0;
}