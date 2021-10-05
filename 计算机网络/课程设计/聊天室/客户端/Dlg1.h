
// Dlg1 对话框
#pragma comment(lib,"ws2_32.lib")
#include<vector>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <thread>
#include <cstdio>
#include<string>
#include<vector>
#define   WM_UPDATEDATA   WM_USER + 5
using namespace std;
class Dlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg1)

public:
	Dlg1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString username_value;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
//	void recvMessage();
	static void recvMessage();
//	CEdit OUTPUT;
//	CEdit INPUT;
	afx_msg void OnBnClickedSend();
//	string OUTPUT;
//	CString OUTPUT;
	CString INPUT;
	afx_msg void OnBnClickedOk();
	LRESULT OnUpdateData(WPARAM wParam, LPARAM lParam);
//	CEdit OUTPUT;
	CString OUTPUT;
};
extern vector<CString> Recv_msg;