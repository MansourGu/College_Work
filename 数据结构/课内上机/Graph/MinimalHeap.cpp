#include"Graph.cpp"
#include"MSTTree.cpp"
#pragma once
using namespace std;
#define Size 20;
class MinmalHeap
{
public:
	MinmalHeap(int sz)
	{
		MaxHeap_Size = Size;
		if (MaxHeap_Size<sz)
		{
			MaxHeap_Size = sz;
		}
		heap = new MSTEdgeNode[MaxHeap_Size];
		Current_Size = 0;
	}
	MinmalHeap(MSTEdgeNode arr[], int n)//ͨ�����齨��
	{
		
		if (MaxHeap_Size < n)
		{
			MaxHeap_Size = n;
		}
		
		heap = new  MSTEdgeNode[MaxHeap_Size];
		if (heap == NULL)
		{
			cout << "�Ѵ洢����ʧ�ܣ�" << endl;
			exit(1);
		}
		for (int i = 0; i < MaxHeap_Size; i++)
		{
			heap[i] = arr[i];                 //���ƶ����飬������С��
		}
		Current_Size = n;                     //��ǰ��С�ѵĴ�С
		int Current_Pos = (Current_Size - 2) / 2;//Ѱ������ĵ���λ�ã����ķ�֧�ڵ�
		while (Current_Pos>=0)
		{
			SiftDown(Current_Pos, Current_Size - 1);//�ֲ����������»�����
			Current_Pos--;//����ǰ��һ����֧�ڵ�
		}
	}
	~MinmalHeap()
	{
		delete[]heap;
	}
	bool Insert(const  MSTEdgeNode& e)//��Ԫ�ز������
	{
		if (Current_Size == MaxHeap_Size)//���������ڲ���
		{
			return false;
		}
		heap[Current_Size] = e;
		SiftUp(Current_Size);
		Current_Size++;
		return true;
	}
	bool RemoveMin(MSTEdgeNode &e)
	{
		if (Current_Size==0)
		{
			cout << "Heap is Empty!" << endl;
			return false;
		}
		e = heap[0];                        //���Ѷ�Ԫ��ȡ��
		heap[0] = heap[Current_Size - 1];   //�����һ��Ԫ�ط���Ѷ�
		Current_Size--;                     //��ǰԪ������һ
		SiftDown(0, Current_Size - 1);      //�������¿�ʼ����
		return true;                        
	}
	void SiftDown(int start, int m)
	{
		int i = start, j = 2*i + 1;//j��i������Ůλ��
		MSTEdgeNode temp = heap[i];
		while (j<= m)              //����Ƿ�����λ��
		{
			if (j<m && heap[i] > heap[j + 1])
			{                      
				j++;			   //��jָ������Ů��С��
			}
			if (temp <= heap[j])  //С��������
			{
				break;
			}
			else                    
			{
				heap[i] = heap[j];//����С�����ƣ�i��j�½�
				i = j;
				j = 2 * i + 1;
			}
		}
		heap[i] = temp;          //�ط�temp�е��ݴ�Ԫ��
	}
	void SiftUp(int start)//��start�ϻ���0������Ϊ��С��
	{
		int j = start, i = (j - 1) / 2;
		MSTEdgeNode temp = heap[j];
		while (j > 0)
		{
			if (heap[i] <= temp)
			{
				break;
			}
			else
			{
				heap[j] = heap[i]; j = i; i = (i - 1) / 2;
			}
		}
		heap[j] = temp;
	}
	bool IsEmpty()
	{
		if (Current_Size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


private:
	int MaxHeap_Size; //��С�ѵ����Ԫ����
	int Current_Size; //��С�ѵĵ�ǰԪ����
	MSTEdgeNode * heap;//���������С����Ԫ�ص�����

};
