
// Search_Engine_MFCDlg.h: 头文件
//
#pragma once
// CSearchEngineMFCDlg 对话框
class CSearchEngineMFCDlg : public CDialogEx
{
// 构造
public:
	CSearchEngineMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_ENGINE_MFC_DIALOG };
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
	
	afx_msg void OnBnClickedButton1();
	void Total_Initial();
	void Search_Input_Func();
	// CString input;// CString input;
	CString Search_Input;
	CEdit Search_Imagine;
	afx_msg void OnEnChangeInput();
};




