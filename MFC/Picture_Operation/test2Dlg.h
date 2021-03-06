
// test2Dlg.h: 头文件
//
#include <iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<string>

using namespace std;
using namespace cv;


// Ctest2Dlg 对话框
class Ctest2Dlg : public CDialogEx
{
// 构造
public:
	Ctest2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST2_DIALOG };
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
	void show_image(Mat& imgSrc, HWND hwnd,int judge);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	BITMAPINFO bitInfo;
	afx_msg void OnBnClickedButton3();
	CRect rect;
	char path1[100];
//	void show_image_reverse(Mat& imgSrc, HWND hwnd);
	int judge=-1;
	CString m_edit;
};
