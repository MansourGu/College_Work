#include<easyx.h>
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<easyx.h>
using namespace std;
struct Vertix
{
	int x;
	int y;
	Vertix(int x1, int y1)
	{
		x = x1;
		y = y1;
	}
	Vertix()
	{

	}
};
map<int, vector<Vertix>> m;
map<int, vector<Vertix>> m1;
vector<Vertix> v;//顶点集合
stack<Vertix> s;//栈
void DDA_for_edge(Vertix start, Vertix end)
{
	int dx, dy, epsl;
	float k, xIncrease, yIncrease, x, y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	k = float(end.y - end.x) / float(end.x - start.x);
	x = start.x;
	y = start.y;
	if (abs(dx) > abs(dy))
	{
		epsl = abs(dx);
	}
	else
	{
		epsl = abs(dy);
	}
	xIncrease = float(dx) / float(epsl);
	yIncrease = float(dy) / float(epsl);
	for (int i = 0; i <= epsl; i++)
	{
		Vertix temp(x + 0.5, y + 0.5);
		m[x + 0.5].push_back(temp);
		x += xIncrease;
		y += yIncrease;
	}
	return;
}
void Input()
{
	int row, col , n;
	/*cout << "请输入顶点个数 ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		Vertix temp;
		cin >> temp.x >> temp.y;
		v.push_back(temp);
	}*/
	Vertix v1(0, 0), v2(100, 100), v3(200, 0);
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	for (int i = 0; i < v.size(); i++)
	{
		DDA_for_edge(v[i], v[(i + 1) % v.size()]);
	}
}
bool check_Inside(Vertix v)
{
	int count = 0;
	for (int i = 0; i < m[v.x].size(); i++)
	{
		if (m[v.x][i].y >= v.y)
		{
			count++;
		}
	}
	if (count % 2 == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool check_overlap(Vertix v)
{

	for (int i = 0; i < m1[v.x].size(); i++)
	{
		if (m1[v.x][i].y == v.y)
		{
			return true;
		}
	}
	return false;
}
void fulfill()
{
	Vertix seed;
	seed.x = 30;
	seed.y = 20;
	s.push(seed);
	m1[seed.x].push_back(seed);
	while (!s.empty())
	{
		Vertix temp = s.top();
		s.pop();
		Vertix up(temp.x , temp.y+1);
		Vertix down(temp.x , temp.y - 1);
		Vertix left(temp.x -1, temp.y);
		Vertix right(temp.x +1  , temp.y);
		if (check_Inside(up) && !check_overlap(up))
		{
			s.push(up);
			m1[up.x].push_back(up);
			putpixel(up.x, up.y , RED);
		}
		if (check_Inside(down) && !check_overlap(down))
		{
			s.push(down);
			m1[down.x].push_back(down);
			putpixel(down.x, down.y, RED);
		}
		if (check_Inside(left) && !check_overlap(left))
		{
			s.push(left);
			m1[left.x].push_back(left);
			putpixel(left.x, left.y, RED);
		}
		if (check_Inside(right) && !check_overlap(right))
		{
			s.push(right);
			m1[right.x].push_back(right);
			putpixel(right.x, right.y, RED);
		}
	}

}
int main()
{
	
	initgraph(640, 480);
	setorigin(320, 240);
	system("pause");
	Input();
	fulfill();
	system("pause");
	return 0;
}