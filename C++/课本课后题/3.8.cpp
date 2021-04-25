#include<iostream>
using namespace std;
int main()
{
	for (int i = 0; i < 7; i++)
	{   
		if (i > 3)
		{
			cout << "  ***"<<endl;
			continue;
		}
		for (int j = 0; j < 3-i; j++)
		{
			cout << " ";
		}
		for (int k = 0; k <2*i+1 ; k++)
		{
			cout << "*";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}