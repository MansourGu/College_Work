#include<iostream>
#include<math.h>
#include<easyx.h>
#define PI 3.1415926
using namespace std;
float  ft[3][3];   //复合矩阵
void Shift_Matrix(float tx, float ty, float t[3][3])//平移矩阵
{
	t[0][0] = 1;  t[0][1] = 0;  t[0][2] = 0;
	t[1][0] = 0;  t[1][1] = 1;  t[1][2] = 0;
	t[2][0] = tx; t[2][1] = ty;  t[2][2] = 1;
}
void Scaling_Matrix(float sx, float sy, float  t[3][3])//比例变换矩阵
{
	t[0][0] = sx;  t[0][1] = 0;   t[0][2] = 0;
	t[1][0] = 0;   t[1][1] = sy;  t[1][2] = 0;
	t[2][0] = 0;   t[2][1] = 0;    t[2][2] = 1;
}
void Cuoqie_Matrix(float c, float b, float t[3][3])
{
	t[0][0] = 1;  t[0][1] = b;   t[0][2] = 0;
	t[1][0] = c;   t[1][1] = 1;  t[1][2] = 0;
	t[2][0] = 0;   t[2][1] = 0;    t[2][2] = 1;
}
void Duichen_Matrix(float a, float b, float d, float e, float t[3][3])
{
	t[0][0] = a;  t[0][1] = d;   t[0][2] = 0;
	t[1][0] = b;   t[1][1] = e;  t[1][2] = 0;
	t[2][0] = 0;   t[2][1] = 0;    t[2][2] = 1;
}
void  Rotation_matrix(float angel, float  t[3][3])//旋转矩阵
{
	t[0][0] = cos(angel);   t[0][1] = sin(angel);   t[0][2] = 0;
	t[1][0] = -sin(angel);  t[1][1] = cos(angel);  t[1][2] = 0;
	t[2][0] = 0;   t[2][1] = 0;    t[2][2] = 1;
}
void WV_matrix(float  wx1, float wy1, float wx2, float wy2,int  vx1, int vy1, int vx2, int vy2, float t[3][3])//窗口到视区的变换
{
	float  sx, sy;
	sx = (vx2 - vx1) / (wx2 - wx1);
	sy = (vy1 - vy2) / (wy1 - wy2);
	t[0][0] = sx;  t[0][1] = 0;   t[0][2] = 0;
	t[1][0] = 0;   t[1][1] = sy;  t[1][2] = 0;
	t[2][0] = -wx1 * sx + vx1;
	t[2][1] = -wy2 * sy + vy2;
	t[2][2] = 1;
}
void Matrix_Multiply(float a[3][3], float b[3][3], float c[3][3])//两个矩阵相乘结果放入第三个矩阵
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < 3; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}
void  Vector_Multiply_Matrix(float v[3], float  a[3][3], float c[3])//向量与矩阵相乘结果放入c
{
	for (int i = 0; i < 3; i++)
	{
		c[i] = 0;
		for (int k = 0; k < 3; k++)
		{
			
			c[i] += v[k] * a[k][i];

		}
	}
}
void  Draw_ploy(float  x[], float y[], int n)
{
	for (int i = 0; i < n-1; i++)
	{
		line(x[i], y[i], x[i + 1], y[i + 1]);
	}
	line(x[n - 1], y[n - 1], x[0], y[0]);
}
void  Init_ft()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == j) ft[i][j] = 1;
			else  ft[i][j] = 0;
}
void  AppToft(float  t[3][3]) //合并矩阵
{
	int i, j;
	float  tmp[3][3];
	Matrix_Multiply(ft, t, tmp);
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) ft[i][j] = tmp[i][j];
}
void  Transfer(float  x[], float  y[], int n)// 坐标变换操作
{
	int i, j, k;
	float  v[3], p[3];
	for (i = 0; i < n; i++)
	{
		v[0] = x[i]; v[1] = y[i]; v[2] = 1;
		Vector_Multiply_Matrix(v, ft, p);
		x[i] = p[0]; y[i] = p[1];
	}
}  
void Shift_Translation(float  tx, float  ty)//平移操作
{
	float  t[3][3];
	Shift_Matrix(tx, ty, t);
	AppToft(t);
}
void Cuoqie(float b, float c)
{
	float t[3][3];
	Cuoqie_Matrix(b, c, t);
	AppToft(t);
}
void Duichen(float a, float b, float d, float e)
{
	float t[3][3];
	Duichen_Matrix(a, b, d, e, t);
	AppToft(t);
}
void Scale(float  sx, float  sy)//缩放操作
{
	float  t[3][3];
	Scaling_Matrix(sx, sy, t);
	AppToft(t);
}
void Rotate(float  alf)//旋转操作
{
	float  t[3][3];
	Rotation_matrix(alf*PI / 180, t);
	AppToft(t);
}
void Define_WV(float wx1, float wy1,float wx2, float wy2,int vx1, int vy1, int vx2, int vy2)
{
	float  t[3][3];
	WV_matrix(wx1, wy1, wx2, wy2, vx1, vy1, vx2, vy2, t);
	AppToft(t);
}
int main()
{
	initgraph(640, 480);
	setorigin(320,240);
	setaspectratio(1 ,-1);
	line(-320, 0, 320, 0);
	line(0, -240, 0, 240);
	float px[3] = { -100,20,100 };
	float py[3] = { 0,100,0};
	Draw_ploy(px, py, 3);
	Init_ft();
	//Shift_Translation(50.0, 30.0);
	//Rotate(30.0);
	//Scale(2.0, 1.5);
	//Define_WV(100.0, 100.0, 400.0, 300.0, 300, 100, 500, 300);
	//Cuoqie(2, 0);//沿着x方向错切
	//Duichen(1, 0, 0, -1);//关于x轴对称
	//Duichen(-1, 0, 0, 1);//关于y轴对称
	//Duichen(-1, 0, 0, -1);//关于原点对称
	//Duichen(0, 1, 1, 0);//关于y=x对称
	Duichen(0, -1, -1, 0);//关于y=-x对称
	Transfer(px, py, 3);
	Draw_ploy(px, py, 3);
	system("pause");
	return 0;
}



