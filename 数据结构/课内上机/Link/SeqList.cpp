#include "stdafx.h"
#include "SeqList.h"


SeqList::SeqList()
{
	
	maxsize = 25;
	data = new int[maxsize];
	end = -1;
	if (data == NULL)
	{
		cout << "存储分配出错！";
		exit(1);
	}
}
SeqList::~SeqList()
{
	delete[] data;
}
int SeqList::Locate(int x)
{
	for (int i = 0; i <= end; i++)
	{
		if (data[i]==x)
		{
			return i;
		}
	}
	AfxMessageBox("错误！顺序表中没有这个元素值！");
	return -1; 
}
void SeqList::Add(int x)
{
	if (maxsize == end+1)
	{
		cout << "表满不能添加！" << endl;
	}
	data[end + 1] = x;
	end++;
}
void SeqList::Insert(int x,int y)
{
	int i = Locate(y);
	if (maxsize == end+1)
	{
		AfxMessageBox("表满不能插入！");
		return;
	}
	if (i<0||i>end+1)
	{
		AfxMessageBox("未找到该元素");
		return;
	}
	for (int j = end; j >i ; j--)
	{
		data[j+1] = data[j];
	}
	data[i+1] = x;
	end++;
	AfxMessageBox("插入成功！");
	return;
}
void SeqList::Delete(int x)
{
	int judge = 0;

	if (end==-1)
	{
		AfxMessageBox("表空不能删除！");
	}
	for (int j = 0; j <= end; j++)
	{
		if (data[j] == x)
		{
			judge = 1;
			if (j == end)
			{
				end--;
				break;
			}
			for (int k = j; k < end; k++)
			{
				data[k] = data[k + 1];

			}
			end--;
			j--;
		}
		
	}
	if (judge==1)
	{
		AfxMessageBox("删除成功！");
		return;
	}
	AfxMessageBox("未找到该元素！");
}
CString SeqList::Show()
{
	CString output="";
	if (end==-1)
	{
		AfxMessageBox("表空无法输出！");
		return"";
	}
	for (int i = 0; i <= end; i++)
	{
		CString temp;
		temp.Format(_T("%d"), data[i]);
		output += ("[" + temp + "]" + " ");
	}
	return output;
}
bool SeqList::IsEmpty()
{
	if (end == -1)
	{
		return true;
	}
	return false;
}
void SeqList::Reverse()
{	
	int n = end + 1;
	for (int i = 0; i < int((n / 2)); i++)
	{
		int temp;
		temp = data[i];
		data[i] = data[n - i - 1];
		data[n - i - 1] = temp;
	}
}

