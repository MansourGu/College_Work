#pragma once


// Tong 对话框

class Tong : public CDialogEx
{
	DECLARE_DYNAMIC(Tong)

public:
	Tong(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Tong();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double t_math;
	double t_Eng;
	double t_Cjj;
	double t_wuli;
	CString t_id;
	CString t_name;
	CListCtrl m_list2;
	virtual BOOL OnInitDialog();
};
