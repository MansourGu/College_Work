
// CalculatorDlg.h: 头文件
//

#pragma once


// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSubtract();
//	double m_result;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDivide();
	afx_msg void OnBnClickedMultiple();
	int m_judge;
//	double m_input;
//	double m_output;
	afx_msg void OnBnClickedEqual();
	CEdit m_editin;
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	CString m_string;
//	CString m_stroutput;
//	CString m_strinput;
//	afx_msg void OnBnClickedNum1();
	CString m_strinput;
	CString m_stroutput;
	double m_input;
	double m_output;
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnBnClickedNum1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
//	afx_msg void OnEnChangeInput();
};
