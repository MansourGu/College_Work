
#include <iostream>
using namespace std;
int n, book[10], a[10], cou = 0;
void dfs(int step) {
	if (step == 10) {
		cou++;
		if (cou == n) {
			for (int i = 0; i <= 9; i++) {
				cout << a[i];
		
			}
		}
		return;
	}

	for (int i = 0; i <= 9; i++) {
		if (book[i] == 0) {
			a[step] = i;
			book[i] = 1;
			dfs(step + 1);
			book[i] = 0;
		}
	}
}

int main() {
	int n = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;
	
	for(int i = 1; i < 5; i++)
	{
		dfs(0);
	}
	system("pause");
	return 0;
}
