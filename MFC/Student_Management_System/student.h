
#include <afxtempl.h>
#define ll long long
using namespace std;
#pragma once

class student
{
public:
	int ID;
	double wuli;      //����ɼ�
	CString name;     //����
	CString Id;      //ѧ��
	double math;     //�����ɼ�
	double Eng;      //��Ӣ�ɼ�
	//void convert();//���洢��CStringת����long long
	student(CString ID, CString Name, double Math, double Wuli, double EngL, double CJJ);
	student();
	virtual ~student();
	double Cjj;   //C++�ɼ�
	friend class Find;
};
