
/*#include<iostream> �˴�����Դ������
#include<vector>
using namespace std;

static int result = 0;
vector<vector<int> > resultNum;
vector<int> resultTemp;

//����㷨�ǿ�������ǰ��ӷ��ŵ��㷨���磺
//-12+3+45-6+78-9=99(û�к���ע�͵���if���)
void sumResult(int A[], int n, int target, int nowValue)
{
	if (n == 0 && nowValue == target)
	{
		resultNum.push_back(resultTemp);
		result++;
		return;
	}
	if (n == 1)
	{
		if (nowValue + 9 == target || nowValue - 9 == target)
		{
			int num = nowValue + 9 == target ? 9 : -9;
			resultTemp.push_back(num);
			resultNum.push_back(resultTemp);
			resultTemp.pop_back();
			result++;
		}
		return;
	}
	int addNum = 0;
	for (int i = 1; i <= n; i++)
	{
		addNum = addNum * 10 + A[i - 1];
		resultTemp.push_back(addNum);
		sumResult(A + i, n - i, target, nowValue + addNum);
		resultTemp.pop_back();
		if (n != 9)//������һ���Ժ󣬵�һ����ǰ�治�ܼ����������ʼ��Ϊ+
		{
			resultTemp.push_back(-addNum);
			sumResult(A + i, n - i, target, nowValue - addNum);
			resultTemp.pop_back();
		}
	}
}

int main()
{
	int A[9] = { 1,2,3,4,5,6,7,8,9 };
	sumResult(A, 9, 99, 0);
	cout << result << endl;

	system("pause");
	return 0;
}*/