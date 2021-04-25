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
	MinmalHeap(MSTEdgeNode arr[], int n)//通过数组建堆
	{
		
		if (MaxHeap_Size < n)
		{
			MaxHeap_Size = n;
		}
		
		heap = new  MSTEdgeNode[MaxHeap_Size];
		if (heap == NULL)
		{
			cout << "堆存储分配失败！" << endl;
			exit(1);
		}
		for (int i = 0; i < MaxHeap_Size; i++)
		{
			heap[i] = arr[i];                 //复制堆数组，建立最小堆
		}
		Current_Size = n;                     //当前最小堆的大小
		int Current_Pos = (Current_Size - 2) / 2;//寻找最初的调整位置，最后的分支节点
		while (Current_Pos>=0)
		{
			SiftDown(Current_Pos, Current_Size - 1);//局部自上向下下滑调整
			Current_Pos--;//在向前换一个分支节点
		}
	}
	~MinmalHeap()
	{
		delete[]heap;
	}
	bool Insert(const  MSTEdgeNode& e)//将元素插入堆中
	{
		if (Current_Size == MaxHeap_Size)//堆满不能在插入
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
		e = heap[0];                        //将堆顶元素取出
		heap[0] = heap[Current_Size - 1];   //将最后一个元素放入堆顶
		Current_Size--;                     //当前元素数减一
		SiftDown(0, Current_Size - 1);      //自上向下开始调整
		return true;                        
	}
	void SiftDown(int start, int m)
	{
		int i = start, j = 2*i + 1;//j是i的左子女位置
		MSTEdgeNode temp = heap[i];
		while (j<= m)              //检查是否到最后的位置
		{
			if (j<m && heap[i] > heap[j + 1])
			{                      
				j++;			   //让j指向两子女的小者
			}
			if (temp <= heap[j])  //小则不做调整
			{
				break;
			}
			else                    
			{
				heap[i] = heap[j];//否则小者上移，i，j下降
				i = j;
				j = 2 * i + 1;
			}
		}
		heap[i] = temp;          //回放temp中的暂存元素
	}
	void SiftUp(int start)//从start上滑到0调整成为最小堆
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
	int MaxHeap_Size; //最小堆的最大元素数
	int Current_Size; //最小堆的当前元素数
	MSTEdgeNode * heap;//存放数组最小堆中元素的数组

};
