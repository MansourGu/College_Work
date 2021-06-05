#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <list>
using namespace std;
#define k 1024 //页块大小
vector<int>order;   //存放生成的随机指令序列
template<typename T>     //生成范围内随机数
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
	srand((unsigned)time(NULL));   //随机数种子
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

double FIFO(int num) {    //先进先出页面置换算法
	list<int> page;   //创建一个双向链表存放内存中的页块信息
	bool flag = 1;
	int beat = 0; //击中次数
	double ratio;  //击中率
	for (int i = 0;i <num;i++) {   //根据不同内存页块分配List大小
		page.push_back(-1);
	}
	for (int i = 0;i < 320;i++) {
		list<int>::iterator it = find(page.begin(), page.end(), order[i]);   //返回page中order[i]的位置
		if (it == page.end()) {
			page.pop_back();   //如果没有找到 则将其加入，为了保证空间一定，删除第一个头节点
			page.push_front(order[i]);
		}
		else {
			beat++;   //如果找到了 则将击中数+1
		}
	}
	ratio = (beat / 320.0)*100;
	return ratio;
}
 
double LRU(int num) {
	
	bool flag = 1;//记录一个页面自上次被访问以来经历的时间t,每次淘汰t最大的
	list<int>page;
	int beat(0);
	double ratio;
	vector<int>temp(32,32);   //记录未被访问的时间t,凡是被访问了则减1
	for (int i = 0;i < num;i++) {   //根据不同内存页块分配List大小
		page.push_back(-1);
	}
	for (int i = 0;i < 320;i++) {
		flag = 1;
		list<int>::iterator it = find(page.begin(), page.end(), order[i]);   //返回page中order[i]的位置
		if (it == page.end()) {    //如果不在list中
			list<int>::iterator itor;   //迭代器
			itor = page.begin();
			while (itor != page.end()) {    //判断list是否填满
				if (*itor == -1) { 
					flag = 0;
					break;
				}
				itor++;
			}
			if (flag == 0) {    //List未填满
				page.pop_front();
				page.push_back(order[i]);
				temp[order[i]]--;
			}
			else {    //LIST已填满，需淘汰
				//寻找最大值
			int max = 0;    //x需要淘汰（找出最大值）或者list中未装满
			for (int i = 1;i < 32;i++) { 
				if (temp[i-1] > temp[i]&&temp[i-1]>max&&temp[i-1]<32) {
					max = i-1;
					}
				}
			//淘汰
			page.remove(max);
			page.push_back(order[i]);
			temp[max] = 32;
			}
		}
		else {   //被访问元素在list中，则将其未被使用数-1
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
	for (int i = 0; i < num; i++) {   //根据不同内存页块分配List大小
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
				//初始化
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
	random();     //生成指令序列
	cout << "FIFO算法：" << "      LRU算法：" << "      OPTIMAL算法：" << endl;
	for (int i = 8;i <= 32;i++) {
		cout << FIFO(i) << '\t' << '\t';
		cout << LRU(i) << '\t' << '\t';
		cout<< optimal(i) << endl;
	}
	system("pause");
	return 0;
}