#pragma once


// Cchange 对话框

class Cchange : public CDialogEx
{
	DECLARE_DYNAMIC(Cchange)

public:
	Cchange(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cchange();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString c_name;
	CString c_id;
	double c_math;
	double c_wuli;
	double c_Eng;
	double c_Cjj;
};
