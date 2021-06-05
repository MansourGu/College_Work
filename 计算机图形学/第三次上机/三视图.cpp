#include<iostream>
#include<math.h>
#include<easyx.h>
#define PI 3.1415926
using namespace std;
float  ft[4][4];   //复合矩阵
void Matrix_Main(float t[4][4])//主视图
{
	t[0][0] = 1;  t[0][1] = 0;  t[0][2] = 0; t[0][3]=0;
	t[1][0] = 0;  t[1][1] = 0;  t[1][2] = 0; t[1][3]=0;
	t[2][0] = 0;  t[2][1] = 0;  t[2][2] = 1; t[2][3]=0;
	t[3][0] = 0;  t[3][1] = 0;  t[3][2] = 0; t[3][3] = 1;

}
void Matrix_Side(float t[4][4])//左视图
{
	t[0][0] = 0;  t[0][1] = 0;  t[0][2] = 0; t[0][3] = 0;
	t[1][0] = -1;  t[1][1] = 0;  t[1][2] = 0; t[1][3] = 0;
	t[2][0] = 0;  t[2][1] = 0;  t[2][2] = 1; t[2][3] = 0;
	t[3][0] = -1;  t[3][1] = 0;  t[3][2] = 0; t[3][3] = 1;
}
void Matrix_Down(float t[4][4])//俯视图
{
	t[0][0] = 1;  t[0][1] = 0;  t[0][2] = 0; t[0][3] = 0;
	t[1][0] = 0;  t[1][1] = 0;  t[1][2] = -1; t[1][3] = 0;
	t[2][0] = 0;  t[2][1] = 0;  t[2][2] = 0; t[2][3] = 0;
	t[3][0] = 0;  t[3][1] = 0;  t[3][2] = -1; t[3][3] = 1;
}
void Matrix_Multiply(float a[4][4], float b[4][4], float c[4][4])//两个矩阵相乘结果放入第三个矩阵
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}
void  Vector_Multiply_Matrix(float v[4], float  a[4][4], float c[4])//向量与矩阵相乘结果放入c
{
	for (int i = 0; i < 4; i++)
	{
		c[i] = 0;
		for (int k = 0; k < 4; k++)
		{

			c[i] += v[k] * a[k][i];

		}
	}
}
void  Draw_ploy(float  x[], float z[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			line(x[i], z[i], x[j], z[j]);
		}
		
	}
}
void  Init_ft()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j) ft[i][j] = 1;
			else  ft[i][j] = 0;
}
void  AppToft(float  t[4][4]) //合并矩阵
{
	int i, j;
	float  tmp[4][4];
	Matrix_Multiply(ft, t, tmp);
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) ft[i][j] = tmp[i][j];
}
void  Transfer(float  x[], float  y[], float z[], int n)// 坐标变换操作
{
	int i, j, k;
	float  v[4], p[4];
	for (i = 0; i < n; i++)
	{
		v[0] = x[i]; v[1] = y[i]; v[2] = z[i]; v[3] = 1;
		Vector_Multiply_Matrix(v, ft, p);
		x[i] = p[0]; y[i] = p[1]; z[i] = p[2];
	}
}
void Main_View()
{
	float t[4][4];
	Matrix_Main(t);
	AppToft(t);
}
void Side_view()
{
	float t[4][4];
	Matrix_Side(t);
	AppToft(t);
}
void Down_View()
{
	float t[4][4];
	Matrix_Down(t);
	AppToft(t);
}
void Initial_Graph()
{
	initgraph(640, 480);
	setorigin(320, 240);
	setaspectratio(-1, -1);
	line(-320, 0, 320, 0);
	line(0, -240, 0, 240);
}
void Three_View()
{
	float px_1[4] = { 200,200,0,100 };
	float py_1[4] = { 0,100,100,100 };
	float pz_1[4] = { 0,0,0,100 };
	Init_ft();
	Main_View();
	Transfer(px_1, py_1, pz_1, 4);
	Draw_ploy(px_1, pz_1, 4);
	float px_2[4] = { 200,200,0,100 };
	float py_2[4] = { 0,100,100,100 };
	float pz_2[4] = { 0,0,0,100 };
	Init_ft();
	Side_view();
	Transfer(px_2, py_2, pz_2, 4);
	Draw_ploy(px_2, pz_2, 4);
	float px[4] = { 200,200,0,100 };
	float py[4] = { 0,100,100,100 };
	float pz[4] = { 0,0,0,100 };
	Init_ft();
	Down_View();
	Transfer(px, py, pz, 4);
	Draw_ploy(px, pz, 4);
}
int main()
{
	Initial_Graph();
	Three_View();
	system("pause");
	return 0;
}



