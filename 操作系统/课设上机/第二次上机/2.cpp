#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<list>
#include<fstream>
using namespace std;
struct track {
	string name;
	int id;
	int dis;
};
vector<track>ve;
int cur = 90;
bool cmp_id(const track& t1, const track& t2) {
	return t1.id < t2.id;
}
bool cmp_dis(const track& t1, const track& t2) {
	return t1.dis > t2.dis;
}
void fcfs() {
	vector<track>temp;
	temp = ve;
	int pos = cur;
	double ave = 0;
	cout << "名字       " << "磁道号         " << "移动道数\n";
	for (int i = 0; i < temp.size(); i++) {
		temp[i].dis = abs(pos - temp[i].id);
		ave += temp[i].dis;
		pos = temp[i].id;
		cout << setw(4) << temp[i].name << setw(8) << temp[i].id << setw(8) << temp[i].dis << endl;
	}
	ave /= temp.size();
	cout << "FCFS平均移动道数:" << ave << endl << endl;
}
void sstf() {
	vector<track>temp;
	temp = ve;
	int pos = cur;
	double ave = 0;
	cout << "名字       " << "磁道号         " << "移动道数\n";
	while (temp.size())
	{
		for (int i = 0; i < temp.size(); i++) {
			temp[i].dis = abs(pos - temp[i].id);
		}
		sort(temp.begin(), temp.end(), cmp_dis);
		int i = temp.size() - 1;
		ave += temp[i].dis;
		cout << setw(4) << temp[i].name << setw(8) << temp[i].id << setw(8) << temp[i].dis << endl;
		pos = temp[i].id;
		temp.pop_back();
	}
	ave /= ve.size();
	cout << "SSTF优先平均移动道数:" << ave << endl << endl;
}
void scan() {
	int pos = cur;
	double ave = 0;
	cout << "名字       " << "磁道号         " << "移动道数\n";
	list<track>l, g;//小于和大于cur的位置
	for (int i = 0; i < ve.size(); i++) {
		if (ve[i].id < pos)l.push_back(ve[i]);
		else g.push_back(ve[i]);
	}
	l.sort(cmp_id);
	g.sort(cmp_id);
	l.reverse();
	g.splice(g.end(), l);
	for (list<track>::iterator it = g.begin(); it != g.end(); it++) {
		it->dis = abs(pos - it->id);
		pos = it->id;
		ave += it->dis;
		cout << setw(4) << it->name << setw(8) << it->id << setw(8) << it->dis << endl;
	}
	ave /= ve.size();
	cout << "LOOK算法平均移动道数:" << ave << endl << endl;
}
int main()
{
	ifstream ifile;
	ifile.open("磁盘调度.txt");
	if (!ifile)
	{
		cout << "文件不存在." << endl;
		return 0;
	}
	while (true)
	{
		track t;
		ifile >> t.name >> t.id;

		if (t.name == "")
		{
			break;
		}

		ve.push_back(t);
	}
	ifile.close();

	int choice = 1;
	while (choice != 0)
	{
		cout << "选择磁盘调度算法:" << endl;
		cout << "1.先来先服务算法" << endl;
		cout << "2.最短寻道优先" << endl;
		cout << "3.电梯调度算法" << endl;
		cout << endl;
		cin >> choice;      cout << endl;
		switch (choice)
		{
		case 1:
			fcfs();
			break;
		case 2:
			sstf();
			break;
		case 3:
			scan();
			break;
		case 0:
			return 0;
		default:
			cout << "input error!" << endl;
			break;
		}
	}

	return 0;
	system("pause");
}