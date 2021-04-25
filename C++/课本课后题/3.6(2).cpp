#include<iostream>
using namespace std;
int main()
{
	int k = 0; char c = 'A';
	do
	{
		switch (++c)
		{
		case 'A':k++; break;
		case'B':k--;
		case'C':k += 2; break;
		case'D':k = k % 2; continue;
		case'E':k = k * 10; break;
		default:k = k / 3;
		}
		k++;
	} while (c<'G');
	cout << k << endl;
	system("pause");
	return 0;
}