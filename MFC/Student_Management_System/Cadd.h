#pragma once


// Cadd 对话框

class Cadd : public CDialogEx
{
	DECLARE_DYNAMIC(Cadd)

public:
	Cadd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cadd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_id;
	double m_math;
	double m_wuli;
	double m_Eng;
	double m_Cjj;
};
