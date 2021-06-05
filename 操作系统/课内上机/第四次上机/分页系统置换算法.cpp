#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <list>
using namespace std;
#define k 1024 //ҳ���С
vector<int>order;   //������ɵ����ָ������
template<typename T>     //���ɷ�Χ�������
T RandT(T _min, T _max)
{
	T temp;
	if (_min > _max)
	{
		temp = _max;
		_max = _min;
		_min = temp;
	}
	return rand() / (double)RAND_MAX * (_max - _min) + _min;
}
int random() {
	int num, count(0);
	srand((unsigned)time(NULL));   //���������
	while (1) {
		num = RandT<int>(1, 32 * k - 2);
		order.push_back(num/k);
		order.push_back((num+1)/k);
		count += 2;
		if (count > 320) break;
		num = RandT<int>(0, num - 1);
		order.push_back(num / k);
		order.push_back((num + 1) / k);
		count += 2;
		if (count > 320) break;
		num = RandT<int>(num + 2, 32 * k - 2);
		order.push_back(num / k);
		order.push_back((num + 1) / k);
		count += 2;
		if (count > 320) break;
	}
	return 0;
}

double FIFO(int num) {    //�Ƚ��ȳ�ҳ���û��㷨
	list<int> page;   //����һ��˫���������ڴ��е�ҳ����Ϣ
	bool flag = 1;
	int beat = 0; //���д���
	double ratio;  //������
	for (int i = 0;i <num;i++) {   //���ݲ�ͬ�ڴ�ҳ�����List��С
		page.push_back(-1);
	}
	for (int i = 0;i < 320;i++) {
		list<int>::iterator it = find(page.begin(), page.end(), order[i]);   //����page��order[i]��λ��
		if (it == page.end()) {
			page.pop_back();   //���û���ҵ� ������룬Ϊ�˱�֤�ռ�һ����ɾ����һ��ͷ�ڵ�
			page.push_front(order[i]);
		}
		else {
			beat++;   //����ҵ��� �򽫻�����+1
		}
	}
	ratio = (beat / 320.0)*100;
	return ratio;
}
 
double LRU(int num) {
	
	bool flag = 1;//��¼һ��ҳ�����ϴα���������������ʱ��t,ÿ����̭t����
	list<int>page;
	int beat(0);
	double ratio;
	vector<int>temp(32,32);   //��¼δ�����ʵ�ʱ��t,���Ǳ����������1
	for (int i = 0;i < num;i++) {   //���ݲ�ͬ�ڴ�ҳ�����List��С
		page.push_back(-1);
	}
	for (int i = 0;i < 320;i++) {
		flag = 1;
		list<int>::iterator it = find(page.begin(), page.end(), order[i]);   //����page��order[i]��λ��
		if (it == page.end()) {    //�������list��
			list<int>::iterator itor;   //������
			itor = page.begin();
			while (itor != page.end()) {    //�ж�list�Ƿ�����
				if (*itor == -1) { 
					flag = 0;
					break;
				}
				itor++;
			}
			if (flag == 0) {    //Listδ����
				page.pop_front();
				page.push_back(order[i]);
				temp[order[i]]--;
			}
			else {    //LIST������������̭
				//Ѱ�����ֵ
			int max = 0;    //x��Ҫ��̭���ҳ����ֵ������list��δװ��
			for (int i = 1;i < 32;i++) { 
				if (temp[i-1] > temp[i]&&temp[i-1]>max&&temp[i-1]<32) {
					max = i-1;
					}
				}
			//��̭
			page.remove(max);
			page.push_back(order[i]);
			temp[max] = 32;
			}
		}
		else {   //������Ԫ����list�У�����δ��ʹ����-1
			temp[order[i]]--;
			beat++;
		}
	}
	ratio = (beat / 320.0) * 100;
	return ratio;
}

double optimal(int num) {
	list<int>page;
	int beat(0);
	double ratio;
	for (int i = 0; i < num; i++) {   //���ݲ�ͬ�ڴ�ҳ�����List��С
		page.push_back(-1);
	}
	for (int i = 0; i < 320; i++) 
	{
		list<int>::iterator it = find(page.begin(), page.end(), order[i]);
		if (it == page.end()) {
			int max_id = -1;

			list<int>::iterator ans;
			for (it = page.begin(); it != page.end(); it++) 
			{
				//��ʼ��
				int cur = 0x3f3f3f3f;
				for (int j = i + 1; j < 320; j++) {
					if (order[j] == *it) {
						cur = j;
						break;
					}
				}
				if (cur > max_id) {
					max_id = cur;
					ans = it;
				}
			}
			page.erase(ans);
			page.push_back(order[i]);

		}
		else {
			beat++;
		}
	}
	ratio = (beat / 320.0) * 100;
	return ratio;
}

int main() {
	random();     //����ָ������
	cout << "FIFO�㷨��" << "      LRU�㷨��" << "      OPTIMAL�㷨��" << endl;
	for (int i = 8;i <= 32;i++) {
		cout << FIFO(i) << '\t' << '\t';
		cout << LRU(i) << '\t' << '\t';
		cout<< optimal(i) << endl;
	}
	system("pause");
	return 0;
}