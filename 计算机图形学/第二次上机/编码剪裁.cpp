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
		c = c | 1;  //按位或
	else if (x > xr)
		c = c | 2;
	if (y < yb)
		c = c | 4;
	else if (y > yt)
		c = c | 8;
	return c;
}//给九个区域编码
void clip(float x0, float y0, float x2, float y2)
{
	unsigned char p1, p2, c;
	float x, y, wx, wy;
	p1 = code(x0, y0);
	p2 = code(x2, y2);
	while ((!(p1 == 0)) || (!(p2 == 0)))
	{
		if ((p1& p2))
			return; //两端点逻辑与不为0，则在区域外，裁去
		c = p1;
		if (c == 0)
			c = p2;
		wx = x2 - x0;
		wy = y2 - y0;
		if ((c & 1) == 1)
		{
			y = y0 + wy * (xl - x0) / wx;
			x = xl;
		}//端点在xl左侧，求与xl的交点

		else if ((c & 2) == 2)
		{
			y = y0 + wy * (xr - x0) / wx;
			x = xr;
		} //端点在xr右侧，求与xr的交点

		else if ((c & 4) == 4)
		{
			x = x0 + wx * (yb - y0) / wy;
			y = yb;
		} //端点在yb下方，求与yb的交点

		else if ((c & 8) == 8)
		{
			x = x0 + wx * (yt - y0) / wy;
			y = yt;
		} //端点在yt上方，求与yt的交点

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
		} //用交点代替端点，再返回第一步
	}
	line(int(x0), int(y0), int(x2), int(y2));
}
void define_Cut_Window()
{
	cout << "请输入定义的剪裁矩形大小 左、右、上、下"<<endl         ;
	cin >> xl >> xr >> yt >> yb;

}
void define_Poly()
{
	int num_edge;
	cout << "请输入多边形边数";
	cin >> num_edge;
	cout << "请依次输入多边形的顶点位置"<<endl;
	if (num_edge<3)
	{
		cout << "至少有三个顶点";
		system("cls");
		define_Poly();
	}
	for (int i = 0; i < num_edge; i++)
	{
		cout << "请输入第" << i + 1<<"个顶点";
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