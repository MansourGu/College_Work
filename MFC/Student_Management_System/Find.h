#pragma once

#include "student.h"
// Find 对话框

class Find : public CDialogEx
{
	DECLARE_DYNAMIC(Find)

public:
	Find(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Find();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_left;
//	double m;
	double m_right;
	CComboBox m_cb;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	CArray <student, student&> m_stuArr;
	afx_msg void OnBnClickedButton3();
};
