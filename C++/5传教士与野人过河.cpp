#include<iostream>
using namespace std;
bool trans_right_to_left(int boat_m, int boat_w, int left_m, int left_w, int right_m, int right_w, int capacity);//�жϴ������ҵ���ʻ�Ĵ��ϴ���ʿ��Ұ�˵�����
bool trans_left_to_right(int boat_m, int boat_w, int left_m, int left_w, int right_m,int right_w,int capacity)//�жϴ����������ʻ�Ĵ��ϴ���ʿ��Ұ�˵�����
{						//���ϴ���ʿ    ����Ұ��    �󰶴���ʿ   ��Ұ��   �Ұ�����ʿ   �Ұ�Ұ��    ��������
	for (int i = left_m; i >=0; i--)//�󰶵Ĵ���ʿ����
	{
		for (int j = left_m; j >=0; j--)//�󰶵�Ұ����
		{
			if (i+j>=1&&i+j<=capacity&&(left_m-i)>=(left_w-j)&&i>=j&&(right_m+i>=right_w+j))
			{	//��������һ������С�ڴ��ĳ����� �������ߵ�����ʿ��Ұ��֮�󴫽�ʿ����Ҫ���ڵ���Ұ������ �Ұ��ڴ�����ʱ����ʿ�ĸ���Ӧ�ô��ڵ���Ұ�˸���
				cout << "�������ҵĴ�����" << i+boat_m << "������ʿ" << j+boat_w << "��Ұ��"<<endl;
				if(trans_right_to_left(i, j, left_m - i, left_w - j, right_m+i, right_w+j, capacity))
						return true;

			}
			continue;
		}

	}
	return false;
}
bool trans_right_to_left(int boat_m, int boat_w, int left_m, int left_w, int right_m, int right_w, int capacity)
{
	if (left_m==0&&left_w==0&&boat_m>=boat_w&&right_m>=right_w)
	{	//����󰶵�û�д���ʿ��Ұ�� ���ϵĴ���ʿ���ڵ���Ұ�˸��� �Ұ��Ĵ���ʿ���ڵ���Ұ�˸��� ��ɹ�����
		cout << "������ϣ�";
		return true;
	}
	for (int i = 0; i <= right_m; i++)
	{
		for (int j = 0; j <= right_w; j++)
		{
			if (i>=j&&i+j>=1&&i+j<=capacity&&i+j<=right_m+right_w&&right_m-i>=right_w-j&&left_m+i>=left_w+j)
			{
				cout << "������������" << i << "������ʿ" << j << "��Ұ��"<<endl;
				if (trans_left_to_right(i,j,left_m,left_w,right_m-i,right_w-j,capacity))
					return true;
			}
			continue;
		}
	}
	return false;
}
int main()
{
	int missionary,wild,left,right,boat;
	cout << "�����봫��ʿ��Ұ�˵�������";
	cin >> wild;
	missionary = wild;
	cout << "�����봬�ĳ˿�����";
	cin >> boat;
	trans_left_to_right(0, 0, missionary, wild, 0, 0, boat);
	system("pause");
	return 0;

}