
// Search_Engine_MFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Search_Engine_MFC.h"
#include "Search_Engine_MFCDlg.h"
#include "afxdialogex.h"
#include <string>
#include"cppjieba/include/cppjieba/Jieba.hpp"
#include<vector>
#include<iostream>//for cout
#include<Windows.h>
#include<wchar.h>
#include <string>
#include<stdio.h>
#include<map>	
#include<algorithm>
#include <io.h>//for _finddata_t、 _findnext
#include<set>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
const char* const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";
cppjieba::Jieba jieba(DICT_PATH,
	HMM_PATH,
	USER_DICT_PATH,
	IDF_PATH,
	STOP_WORD_PATH);
vector<string> words;
vector<cppjieba::Word> jiebawords;
map<string, vector<string> > indextable;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSearchEngineMFCDlg 对话框
CSearchEngineMFCDlg::CSearchEngineMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCH_ENGINE_MFC_DIALOG, pParent)
	, Search_Input(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchEngineMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT, Search_Input);
	DDX_Control(pDX, IDC_SearchLine, Search_Imagine);
}

BEGIN_MESSAGE_MAP(CSearchEngineMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSearchEngineMFCDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_INPUT, &CSearchEngineMFCDlg::OnEnChangeInput)
END_MESSAGE_MAP()


// CSearchEngineMFCDlg 消息处理程序

BOOL CSearchEngineMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Total_Initial();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSearchEngineMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSearchEngineMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSearchEngineMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string string_To_UTF8(const std::string & str)//将string转换为UTF-8
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
string UTF8_To_string(const std::string & str) //将UTF-8转string
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}
vector<string>Cut_IndexTable(string s)//对索引表做划分
{
	vector<string>output;
	string temp;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ' && i == 0)
		{
			temp += s[i];
			continue;
		}
		if (s[i] == ' ' && i != 0)
		{
			output.push_back(temp);
			temp.clear();
			continue;
		}
		temp += s[i];
	}
	return output;
}
void init() //初始化表
{
	indextable.clear();
}
vector<string> Search_Partition(string s)//对搜索的输入做单词划分
{
	string temp = string_To_UTF8(s);
	vector<string> output;
	string temp1;
	jieba.CutForSearch(temp, words);
	temp = limonp::Join(words.begin(), words.end(), "/");
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == '/')
		{
			output.push_back(UTF8_To_string(temp1));
			temp1.clear();
			continue;
		}
		temp1 += temp[i];
		if (i == temp.size() - 1)
		{
			output.push_back(UTF8_To_string(temp1));
			temp1.clear();
		}
	}
	return output;
}
void Read_IndexTable()//读取索引表
{
	init();
	ifstream fin("result1.txt");
	while (1)
	{
		char buffer[200000];
		string s;
		fin.getline(buffer, 200000);
		s = buffer;
		vector<string>temp;
		temp = Cut_IndexTable(s);

		for (int i = 1; i < temp.size(); i++)
		{
			if (indextable[temp[0]].empty())
			{
				indextable[temp[0]].push_back(temp[i]);
				continue;
			}
			else if (indextable[temp[0]][indextable[temp[0]].size() - 1] == temp[i])
			{
				continue;
			}
			indextable[temp[0]].push_back(temp[i]);

		}
		if (fin.eof())
		{
			break;
		}
	}
	fin.close();
}
vector<string> Cut(string s)//将划分好单词的句子，把单词提取出来
{
	vector<string>temp;
	string s_temp;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == u8'/' || s[i] == u8' ')
		{
			temp.push_back(s_temp);
			s_temp.clear();
			continue;
		}
		s_temp += s[i];
	}
	return temp;
}
vector<string> getFilesList(string dir)//搜索一个目录下的所有文件
{
	vector<string> allPath;
	// 在目录后面加上"\\*.*"进行第一次搜索
	string dir2 = dir + "\\*.*";

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dir2.c_str(), &findData);
	if (handle == -1) {// 检查是否成功
		cout << "can not found the file ... " << endl;
		return allPath;
	}
	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			//若该子目录为"."或".."，则进行下一次循环，否则输出子目录名，并进入下一次搜索
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			string dirNew = dir + "\\" + findData.name;
			vector<string> tempPath = getFilesList(dirNew);
			allPath.insert(allPath.end(), tempPath.begin(), tempPath.end());
		}
		else //不是子目录，即是文件，则输出文件名和文件的大小
		{
			string filePath = dir + "\\" + findData.name;
			allPath.push_back(filePath);
			//cout << filePath << "\t" << findData.size << " bytes.\n";
		}
	} while (_findnext(handle, &findData) == 0);
	_findclose(handle);    // 关闭搜索句柄
	return allPath;
}
void Build_Index()//建立索引表
{
	init();
	vector<string>File_Path = getFilesList("test");
	for (int i = 0; i < File_Path.size(); i++)
	{
		string filepath = File_Path[i]; //文件路径名
		ifstream fin(filepath);//打开文件路径下的文件
		while (1)
		{
			char buffer[20000];
			string s;
			fin.getline(buffer, 20000);
			s = buffer;
			vector<string>temp;
			temp = Cut(s);
			for (int i = 0; i < temp.size(); i++)
			{
				if (indextable[temp[i]].empty())
				{
					indextable[temp[i]].push_back(filepath);
					continue;
				}
				else if (indextable[temp[i]][indextable[temp[i]].size() - 1] == filepath)
				{
					continue;
				}
				indextable[temp[i]].push_back(filepath);
			}

			if (fin.eof())
			{
				break;
			}
		}
	}
	map<string, vector<string> >::iterator map_it;//索引表迭代器
	map_it = indextable.begin();
	ofstream result("result.txt");
	while (map_it != indextable.end())//遍历整个索引表输出，因为MAP的键值是严格弱排序，因此输出是字典序
	{
		string tmp = map_it->first;
		result << tmp << " ";
		for (int i = 0; i != indextable[tmp].size(); i++)
			result << indextable[tmp][i] << " ";
		result << endl;
		map_it++;
	}
	result.close();
}
void Partition()//将所有文件单词做划分
{
	vector<string> FileName = getFilesList("answer");
	vector<string> s;
	for (int i = 0; i < FileName.size(); i++)
	{
		
		string result;
		fstream input;
		input.open(FileName[i]);
		while (1)
		{
			char buffer[20000];
			string temp;
			input.getline(buffer, 20000);
			temp = buffer;
			s.push_back(temp);
			if (input.eof())
			{
				break;
			}
		}
		input.close();
		ofstream output(FileName[i]);
		for (int i = 0; i < s.size(); i++)
		{
			string temp = string_To_UTF8(s[i]);
			jieba.CutForSearch(temp, words);
			output << limonp::Join(words.begin(), words.end(), "/") << endl;
		}
		output.close();
		s.clear();
	}
	
}
void CSearchEngineMFCDlg::OnBnClickedButton1()//搜索
{
	Search_Input_Func();
}
void CSearchEngineMFCDlg::Total_Initial()
{
	Read_IndexTable();
}
void CSearchEngineMFCDlg::Search_Input_Func()
{
	UpdateData();
	vector<string>r_t;//记录结果
	set<string>Set;//记录最终结果（排除重复项）
	string search(Search_Input.GetBuffer());//搜索输入
	vector<string>search_result;//对搜索输入进行划分
	search_result = Search_Partition(search);
	for (int i = 0; i < search_result.size(); i++)
	{
		auto iter = indextable.find(search_result[i]);
		if (iter != indextable.end())
		{
			r_t = iter->second;
		}
	}
	for (int i = 0; i < r_t.size(); i++)
	{
		Set.insert(r_t[i]);
	}
	CString output ;
	r_t.clear();
	for (auto i = Set.begin(); i != Set.end(); i++)
	{
		CString temp;
		r_t.push_back(*i);
	
	}
	string filename = r_t[0].replace(0, 4, "answer");
	ifstream fin(filename);
	string search_input = Search_Input;
	while (1)
	{	
		char buffer[20000];
		string temp;
		fin.getline(buffer, 20000);
		temp = buffer;
		string::size_type idx = temp.find(search_input);
		if (idx != string::npos)
		{
			output = temp.c_str();
			AfxMessageBox(output);

		}
		if (fin.eof())
		{
			break;
		}
	}
	
	// TODO: 在此处添加实现代码.
}
void CSearchEngineMFCDlg::OnEnChangeInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (Search_Input == "")
	{
		Search_Imagine.ShowWindow(false);
	}
	else
	{
		
		vector<string>r_t;//记录结果
		set<string>Set;//记录最终结果（排除重复项）
		string search(Search_Input.GetBuffer());//搜索输入
		vector<string>search_result;//对搜索输入进行划分
		search_result = Search_Partition(search);
		for (int i = 0; i < search_result.size(); i++)
		{
			auto iter = indextable.find(search_result[i]);
			if (iter != indextable.end())
			{
				r_t = iter->second;
			}
		}
		for (int i = 0; i < r_t.size(); i++)
		{
			Set.insert(r_t[i]);
		}
		r_t.clear();
		for (auto i = Set.begin(); i != Set.end(); i++)
		{
			CString temp;
			r_t.push_back(*i);
		}
		int count_line;
		CString output;
		if (r_t.size()>10)
		{
			count_line = 10;
		}
		else
		{
			count_line = r_t.size();
		}
		int line_height = count_line * 20;
		for (int i = 0; i < count_line; i++)
		{
			output += ((r_t[i].replace(0,4,"answer") + "\r\n").c_str());
		}
		Search_Imagine.ShowWindow(true);
		Search_Imagine.SetWindowPos(NULL, 0, 0, 400, line_height, SWP_NOZORDER | SWP_NOMOVE);
		Search_Imagine.SetWindowTextA(output);
	}
	UpdateData(false);

}
