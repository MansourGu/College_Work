#include<iostream>
#include<cmath>
using namespace std;
class Point
{
public:
	double x, y;//点的横纵坐标
	Point(double x1, double y1)
	{
		x = x1;
		y = y1;
	}
	void show()
	{
		cout << "坐标为： ( " << x << "," << y << " )"<<endl;
	}
};

double cal_k(Point&x, Point&y)//求k值
{
	double k = double((y.y - x.y) / (y.x - x.x));//根据公式（纵坐标之差除以横坐标之差）
	return double (k);
}
double cal_distance(Point &x, Point &y)//求两点间距离
{
	double distance;
	distance = sqrt((y.y - x.y)*(y.y - x.y) + (y.x - x.x)*(y.x - x.x));
	return double(distance);
}
double cal_point_to_distance(Point &x, Point &y, Point &z)//点到直线距离（求高）
{
	double temp;
	temp = cal_k(x, y);
	double m = temp * z.x - z.y + x.y - temp * x.x;
	double n = sqrt(temp*temp + 1);
	return (fabs (m)/n);
}
double cal_area(Point &x, Point &y, Point &z)//计算面积
{	
	double height = cal_point_to_distance(x, y, z);//高 点到底边的距离
	double line = cal_distance(x, y);//底边长度 
	return (height*line) / 2;//面积
}void find_crossPoint(Point p1, Point p2, Point p3, Point p4, Point &crossPoint) //寻找两条线的交点。
{
	double a1 = p2.y - p1.y;                        //根据公式
	double b1 = p1.x - p2.x;						//L1:(X1,Y1),(X2,Y2)L2:(X3,Y3),(X4,Y4)L1:Y=K1X+B1,L2:Y=K2X+B2交点：//[（B2-B1)/(K1-K2),(B2K1-B1K2)/(K1-K2)]
	double c1 = p1.x*p2.y - p2.x*p1.y;				//[（B2-B1)/(K1-K2),(B2K1-B1K2)/(K1-K2)]
	double a2 = p4.y - p3.y;						//其中：k1=(y2-y1)/(x2-y1),k2=(y4-y3)/(x4-x3)b1=y1-k1(B2-B1)/(K1-K2),b2=y3-k2(B2-B1)/(K1-K2)
	double b2 = p3.x - p4.x;
	double c2 = p3.x*p4.y - p4.x*p3.y;
	double det = a1 * b2 - a2 * b1;
	crossPoint.x = (c1*b2 - c2 * b1) / det;
	crossPoint.y = (a1*c2 - a2 * c1) / det;
}
int main()
{
	double L;
	cout << "请输入正三角形边长：";
	cin >> L;
	Point A(0, 0), B(L, 0), C((L / 2), (L / 2)*sqrt(3));//正三角形顶点坐标
	Point A1((2 * L) / 3, ( L*sqrt(3)) / 3), B1(L/6, ( L*sqrt(3)) /6), C1(((2 * L) / 3), 0);//A1 B1 C1 坐标
	Point A_A1_Cross_B_B1(0, 0);
	Point A_A1_Cross_C_C1(0, 0);
	Point B_B1_Cross_C_C1(0, 0);
	find_crossPoint(A, A1, B, B1, A_A1_Cross_B_B1);
	find_crossPoint(A, A1, C,C1, A_A1_Cross_C_C1);
	find_crossPoint(B,B1,C,C1, B_B1_Cross_C_C1);
	cout << "设正三角型的边长为" << L<<endl;
	cout << "所以 A点坐标为：";
	A.show();
	cout << "所以 B点坐标为：";
	B.show();
	cout << "所以 C点坐标为：";
	C.show();
	cout << "所以 A1点坐标为：";
	A1.show();
	cout << "所以 B1点坐标为：";
	B1.show();
	cout << "所以 C1点坐标为：";
	C1.show();
	cal_area(A_A1_Cross_B_B1, A_A1_Cross_C_C1, B_B1_Cross_C_C1);
	cout << "所以 A2点坐标为：";
	A_A1_Cross_B_B1.show();
	cout << "所以 B2点坐标为：";
	A_A1_Cross_C_C1.show();
	cout << "所以 C2点坐标为：";
	B_B1_Cross_C_C1.show();
	cout << "ABC构成的三角形面积为：" << cal_area(A, C, B)<<endl;
	cout << "A1 B1 C1 构成的三角形面积为：" << cal_area(A1, B1, C1) << endl;
	cout << "由线段AA1、BB1、CC1相交而成的三角形A2B2C2的面积是正三角形ABC的面积是:"<<cal_area(A_A1_Cross_B_B1, A_A1_Cross_C_C1, B_B1_Cross_C_C1);
	cout << endl;
	cout << "所以ABC的面积是A2B2C2面积的";
	cout << cal_area(A, C, B) / cal_area(A_A1_Cross_B_B1, A_A1_Cross_C_C1, B_B1_Cross_C_C1)<<"倍"<<endl;

	system("pause");
	return 0;
}
