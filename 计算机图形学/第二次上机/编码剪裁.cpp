#include<easyx.h>
#include<iostream>
#include<vector>
using namespace std;
float xl, xr, yt, yb;
struct Vertix
{
	float x;
	float y;
};
struct Poly
{
	vector<Vertix> v;
};
Poly p;
void initial()
{
	initgraph(640, 480);
	setorigin(320, 240);
	setaspectratio(1, -1);
}
unsigned char code(float x, float y)
{
	unsigned char c = 0;
	if (x < xl)
		c = c | 1;  //��λ��
	else if (x > xr)
		c = c | 2;
	if (y < yb)
		c = c | 4;
	else if (y > yt)
		c = c | 8;
	return c;
}//���Ÿ��������
void clip(float x0, float y0, float x2, float y2)
{
	unsigned char p1, p2, c;
	float x, y, wx, wy;
	p1 = code(x0, y0);
	p2 = code(x2, y2);
	while ((!(p1 == 0)) || (!(p2 == 0)))
	{
		if ((p1& p2))
			return; //���˵��߼��벻Ϊ0�����������⣬��ȥ
		c = p1;
		if (c == 0)
			c = p2;
		wx = x2 - x0;
		wy = y2 - y0;
		if ((c & 1) == 1)
		{
			y = y0 + wy * (xl - x0) / wx;
			x = xl;
		}//�˵���xl��࣬����xl�Ľ���

		else if ((c & 2) == 2)
		{
			y = y0 + wy * (xr - x0) / wx;
			x = xr;
		} //�˵���xr�Ҳ࣬����xr�Ľ���

		else if ((c & 4) == 4)
		{
			x = x0 + wx * (yb - y0) / wy;
			y = yb;
		} //�˵���yb�·�������yb�Ľ���

		else if ((c & 8) == 8)
		{
			x = x0 + wx * (yt - y0) / wy;
			y = yt;
		} //�˵���yt�Ϸ�������yt�Ľ���

		if (c == p1)
		{
			x0 = x;
			y0 = y;
			p1 = code(x0, y0);
		}
		else
		{
			x2 = x;
			y2 = y;
			p2 = code(x2, y2);
		} //�ý������˵㣬�ٷ��ص�һ��
	}
	line(int(x0), int(y0), int(x2), int(y2));
}
void define_Cut_Window()
{
	cout << "�����붨��ļ��þ��δ�С ���ҡ��ϡ���"<<endl         ;
	cin >> xl >> xr >> yt >> yb;

}
void define_Poly()
{
	int num_edge;
	cout << "���������α���";
	cin >> num_edge;
	cout << "�������������εĶ���λ��"<<endl;
	if (num_edge<3)
	{
		cout << "��������������";
		system("cls");
		define_Poly();
	}
	for (int i = 0; i < num_edge; i++)
	{
		cout << "�������" << i + 1<<"������";
		Vertix temp;
		cin >> temp.x >> temp.y;
		p.v.push_back(temp);
	}
}
void Output_result()
{
	initial();
	for (int i = 0; i < p.v.size()-1; i++)
	{
		line(p.v[i+1].x, p.v[i+1].y, p.v[i].x, p.v[i].y);
	}
	line(p.v[0].x, p.v[0].y, p.v[p.v.size() - 1].x, p.v[p.v.size() - 1].y);
	rectangle(xl, yt, xr, yb);
	Sleep(3000);
	cleardevice();
	rectangle(xl, yt, xr, yb);
	for (int i = 0; i < p.v.size() - 1; i++)
	{
		clip(p.v[i + 1].x, p.v[i + 1].y, p.v[i].x, p.v[i].y);
	}
	clip(p.v[0].x, p.v[0].y, p.v[p.v.size() - 1].x, p.v[p.v.size() - 1].y);
}

int main()
{
	define_Cut_Window();
	define_Poly();
	Output_result();
	system("pause");
	return 0;
}