#include "pch.h"
#include "student.h"
#include "studentmanageA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


student::student()
{

}

student::~student()
{

}


student::student(CString ID, CString Name, double Math, double Wuli, double EngL, double CJJ)
{
	this->Id = ID;
	name = Name;
	math = Math;
	wuli = Wuli;
	Eng = EngL;
	Cjj = CJJ;
}
