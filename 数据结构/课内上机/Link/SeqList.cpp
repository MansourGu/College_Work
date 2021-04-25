#include "stdafx.h"
#include "SeqList.h"


SeqList::SeqList()
{
	
	maxsize = 25;
	data = new int[maxsize];
	end = -1;
	if (data == NULL)
	{
		cout << "�洢�������";
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
	AfxMessageBox("����˳�����û�����Ԫ��ֵ��");
	return -1; 
}
void SeqList::Add(int x)
{
	if (maxsize == end+1)
	{
		cout << "����������ӣ�" << endl;
	}
	data[end + 1] = x;
	end++;
}
void SeqList::Insert(int x,int y)
{
	int i = Locate(y);
	if (maxsize == end+1)
	{
		AfxMessageBox("�������ܲ��룡");
		return;
	}
	if (i<0||i>end+1)
	{
		AfxMessageBox("δ�ҵ���Ԫ��");
		return;
	}
	for (int j = end; j >i ; j--)
	{
		data[j+1] = data[j];
	}
	data[i+1] = x;
	end++;
	AfxMessageBox("����ɹ���");
	return;
}
void SeqList::Delete(int x)
{
	int judge = 0;

	if (end==-1)
	{
		AfxMessageBox("��ղ���ɾ����");
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
		AfxMessageBox("ɾ���ɹ���");
		return;
	}
	AfxMessageBox("δ�ҵ���Ԫ�أ�");
}
CString SeqList::Show()
{
	CString output="";
	if (end==-1)
	{
		AfxMessageBox("����޷������");
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

