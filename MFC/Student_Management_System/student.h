
#include <afxtempl.h>
#define ll long long
using namespace std;
#pragma once

class student
{
public:
	int ID;
	double wuli;      //大物成绩
	CString name;     //姓名
	CString Id;      //学号
	double math;     //高数成绩
	double Eng;      //大英成绩
	//void convert();//将存储的CString转换成long long
	student(CString ID, CString Name, double Math, double Wuli, double EngL, double CJJ);
	student();
	virtual ~student();
	double Cjj;   //C++成绩
	friend class Find;
};
