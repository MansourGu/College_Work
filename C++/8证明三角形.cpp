#include<iostream>
#include<cmath>
using namespace std;
class Point
{
public:
	double x, y;//��ĺ�������
	Point(double x1, double y1)
	{
		x = x1;
		y = y1;
	}
	void show()
	{
		cout << "����Ϊ�� ( " << x << "," << y << " )"<<endl;
	}
};

double cal_k(Point&x, Point&y)//��kֵ
{
	double k = double((y.y - x.y) / (y.x - x.x));//���ݹ�ʽ��������֮����Ժ�����֮�
	return double (k);
}
double cal_distance(Point &x, Point &y)//����������
{
	double distance;
	distance = sqrt((y.y - x.y)*(y.y - x.y) + (y.x - x.x)*(y.x - x.x));
	return double(distance);
}
double cal_point_to_distance(Point &x, Point &y, Point &z)//�㵽ֱ�߾��루��ߣ�
{
	double temp;
	temp = cal_k(x, y);
	double m = temp * z.x - z.y + x.y - temp * x.x;
	double n = sqrt(temp*temp + 1);
	return (fabs (m)/n);
}
double cal_area(Point &x, Point &y, Point &z)//�������
{	
	double height = cal_point_to_distance(x, y, z);//�� �㵽�ױߵľ���
	double line = cal_distance(x, y);//�ױ߳��� 
	return (height*line) / 2;//���
}void find_crossPoint(Point p1, Point p2, Point p3, Point p4, Point &crossPoint) //Ѱ�������ߵĽ��㡣
{
	double a1 = p2.y - p1.y;                        //���ݹ�ʽ
	double b1 = p1.x - p2.x;						//L1:(X1,Y1),(X2,Y2)L2:(X3,Y3),(X4,Y4)L1:Y=K1X+B1,L2:Y=K2X+B2���㣺//[��B2-B1)/(K1-K2),(B2K1-B1K2)/(K1-K2)]
	double c1 = p1.x*p2.y - p2.x*p1.y;				//[��B2-B1)/(K1-K2),(B2K1-B1K2)/(K1-K2)]
	double a2 = p4.y - p3.y;						//���У�k1=(y2-y1)/(x2-y1),k2=(y4-y3)/(x4-x3)b1=y1-k1(B2-B1)/(K1-K2),b2=y3-k2(B2-B1)/(K1-K2)
	double b2 = p3.x - p4.x;
	double c2 = p3.x*p4.y - p4.x*p3.y;
	double det = a1 * b2 - a2 * b1;
	crossPoint.x = (c1*b2 - c2 * b1) / det;
	crossPoint.y = (a1*c2 - a2 * c1) / det;
}
int main()
{
	double L;
	cout << "�������������α߳���";
	cin >> L;
	Point A(0, 0), B(L, 0), C((L / 2), (L / 2)*sqrt(3));//�������ζ�������
	Point A1((2 * L) / 3, ( L*sqrt(3)) / 3), B1(L/6, ( L*sqrt(3)) /6), C1(((2 * L) / 3), 0);//A1 B1 C1 ����
	Point A_A1_Cross_B_B1(0, 0);
	Point A_A1_Cross_C_C1(0, 0);
	Point B_B1_Cross_C_C1(0, 0);
	find_crossPoint(A, A1, B, B1, A_A1_Cross_B_B1);
	find_crossPoint(A, A1, C,C1, A_A1_Cross_C_C1);
	find_crossPoint(B,B1,C,C1, B_B1_Cross_C_C1);
	cout << "���������͵ı߳�Ϊ" << L<<endl;
	cout << "���� A������Ϊ��";
	A.show();
	cout << "���� B������Ϊ��";
	B.show();
	cout << "���� C������Ϊ��";
	C.show();
	cout << "���� A1������Ϊ��";
	A1.show();
	cout << "���� B1������Ϊ��";
	B1.show();
	cout << "���� C1������Ϊ��";
	C1.show();
	cal_area(A_A1_Cross_B_B1, A_A1_Cross_C_C1, B_B1_Cross_C_C1);
	cout << "���� A2������Ϊ��";
	A_A1_Cross_B_B1.show();
	cout << "���� B2������Ϊ��";
	A_A1_Cross_C_C1.show();
	cout << "���� C2������Ϊ��";
	B_B1_Cross_C_C1.show();
	cout << "ABC���ɵ����������Ϊ��" << cal_area(A, C, B)<<endl;
	cout << "A1 B1 C1 ���ɵ����������Ϊ��" << cal_area(A1, B1, C1) << endl;
	cout << "���߶�AA1��BB1��CC1�ཻ���ɵ�������A2B2C2���������������ABC�������:"<<cal_area(A_A1_Cross_B_B1, A_A1_Cross_C_C1, B_B1_Cross_C_C1);
	cout << endl;
	cout << "����ABC�������A2B2C2�����";
	cout << cal_area(A, C, B) / cal_area(A_A1_Cross_B_B1, A_A1_Cross_C_C1, B_B1_Cross_C_C1)<<"��"<<endl;

	system("pause");
	return 0;
}
