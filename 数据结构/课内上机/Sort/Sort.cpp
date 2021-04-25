#include <iostream>
#include <conio.h>
#include <fstream>
#include <string> 
#include <chrono>
#include <algorithm> 
#include <cmath>
#include <ctime>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <assert.h>
#include <stack>
const int MAX = 10000000;
const int MIN = 0;
using namespace std;
using namespace chrono;//time library 用于计时
struct linknode
{
	int data;
	linknode*llink = NULL;
	linknode*rlink = NULL;
};
void swap(int*& arr, int a, int b)//交换数组指定下标的内容
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}
void inilinkdata(linknode*head, int range)//生成随机链表
{
	linknode*current = new linknode;
	head->rlink = current;
	current->llink = head;
	srand((int)time(0));
	for (int i = 0; i < range; i++)
	{
		int rand1 = rand() % 10000;
		int rand2 = rand() % 10000;
		current->data = ((rand1 * 10000 + rand2) % (MAX - MIN + 1) + MIN);
		linknode*temp = new linknode;
		current->rlink = temp;
		temp->llink = current;
		current = current->rlink;
	}
	current->llink->rlink = head;
	head->llink = current->llink;
	delete current;
}
void output(int* arr, int len, string textName)//把数据输出到文件
{
	cout << "正在将数据存入文件......\r";
	ofstream output(textName + ".txt");
	if (output.is_open())
	{
		for (int i = 0; i < len; i++)
			output << arr[i] << "\n";
		output.close();
	}
	cout << "数据存入完毕......         \r";
	system("pause");
}
int* initData(int range)//生成随机数组
{
	int* data = new int[range]; //动态数组储存数据
	srand((int)time(0));
	for (int i = 0; i < range; i++)
	{
		int rand1 = rand() % 10000;
		int rand2 = rand() % 10000;
		data[i] = ((rand1 * 10000 + rand2) % (MAX - MIN + 1) + MIN);
	}
	return data;
}
int* initPositiveData(int range)//生成基本正序数组
{
	int* data = new int[range]; //动态数组储存数据
	srand((int)time(0));
	int start = rand();
	int i = 0;
	while (i < range)
	{
		data[i] = start;
		start += (rand() % 10);
		i++;
	}
	return data;
}
int* initReverseData(int range)//生成基本逆序数组
{
	int* data = new int[range]; //动态数组储存数据
	srand((int)time(0));
	int start = rand();
	int i = range - 1;
	while (i >= 0)
	{
		data[i] = start;
		start += (rand() % 10);
		i--;
	}
	return data;
}
void insertSort_link(linknode*head)//基于链表直接插入排序
{
	if (head->rlink == head)
		return;
	linknode* current = new linknode;
	current = head->rlink;
	while (current != head)
	{
		int value = current->data;//存储current的值
		linknode* pivot = current->llink;// 查找插入的位置 从后向前比较
		while (pivot != head)
		{
			if (pivot->data > value)
			{
				pivot->rlink->data = pivot->data;
			}
			else
			{
				break;
			}
			pivot = pivot->llink;
		}
		pivot->rlink->data = value;
		current = current->rlink;
	}

}
void Bubble_sort_link(linknode*head)//链表的冒泡排序
{
	linknode* current = head->llink; //链表的最后一位
	while (current != head)
	{
		int exchange = 0;
		linknode* left = current->llink;
		linknode* right = current;
		while (left != head)
		{
			if (left->data > right->data)
			{
				int temp;
				temp = left->data;
				left->data = right->data;
				right->data = temp;
				exchange = 1;
			}
			left = left->llink;
			right = right->llink;
		}
		if (exchange == 0)
		{
			return;
		}
		else
		{
			current = current->llink;
		}
	}

}
void insertSort(int*& arr, int length)
{//直接插入排序
	if (length <= 1 || arr == nullptr)
		return;
	for (int i = 1; i < length; i++)
	{
		int value = arr[i];//存储arr[i]的值
		int j = i - 1;
		// 查找插入的位置 从后向前比较
		for (; j >= 0; j--)
		{
			if (arr[j] > value)
				arr[j + 1] = arr[j]; // 数据移动 
			else
				break;
		}
		arr[j + 1] = value; // 插入数据 
	}
}
int	partition(int arr[], int left, int right)//返回最终的分割点
{
	int pivot = arr[left];
	int pivotpos = left;
	for (int i = left + 1; i < right; i++)
	{
		if (arr[i] < pivot)
		{
			pivotpos++;
			if (pivotpos != i)
			{
				swap(arr, pivotpos, i);
			}
		}
	}
	arr[left] = arr[pivotpos];
	arr[pivotpos] = pivot;//将基准点放入左右重合的地方
	return pivotpos;
}
void quickSort(int* arr, int left, int right)
{
	if (left >= right)
		return;
	if (right - left + 1 < 15) //当序列长度小于15时使用直接插入排序
	{
		int* start = arr + left;
		insertSort(start, right - left + 1);
		return;
	}
	int q = partition(arr, left, right);//返回新的分割点
	quickSort(arr, left, q - 1);
	quickSort(arr, q + 1, right);
}
void quickSort(int*& arr, int length)
{//快速排序
	if (length <= 1 || arr == nullptr)
		return;
	quickSort(arr, 0, length - 1);
}
void merge(int*& arr, int L, int M, int R)//合并
{
	int* cent = new int[R - L + 1];//创建新的辅助空间存放元素
	int i = 0;
	int pFirst = L, pSecond = M + 1;
	while (pFirst <= M && pSecond <= R)//开始合并
		cent[i++] = arr[pFirst] < arr[pSecond] ? arr[pFirst++] : arr[pSecond++];
	while (pFirst <= M)//未比较完的数据存到cent数组中
		cent[i++] = arr[pFirst++];
	while (pSecond <= R)//未比较完的数据存到cent数组中
		cent[i++] = arr[pSecond++];
	for (int j = 0; j < (R - L + 1); j++)//把排好序的子序列放入数组的原位置
		arr[L + j] = cent[j];
}
void mergeSort(int*& arr, int L, int R)//分割
{
	if (L == R)//左右下标相等已经排完了
		return;
	int mid = (L + R) / 2;//划分成两个子序列
	mergeSort(arr, L, mid);
	mergeSort(arr, mid + 1, R);
	merge(arr, L, mid, R);
}
void mergeSort(int*& arr, int length)//归并排序
{
	if (arr == nullptr || length < 2)
		return;
	mergeSort(arr, 0, length - 1);
}
void heapInsert(int arr[], int index)//堆插入
{
	while (arr[index] > arr[(index - 1) / 2])//跟父亲节点作比较
	{
		swap(arr, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}
void heapify(int*& arr, int index, int size)
{
	int leftChild = index * 2 + 1;//左孩子调整
	while (leftChild < size)//左孩子存在
	{
		int maxChild = leftChild + 1 < size && arr[leftChild + 1] > arr[leftChild] ? leftChild + 1 : leftChild;//取出最大孩子的下标
		int maxAll = arr[maxChild] > arr[index] ? maxChild : index;//孩子的最大值跟节点本身比
		if (maxAll == index)
			break;
		swap(arr, maxAll, index);//若孩子大于该节点则交换
		index = maxAll;
		leftChild = index * 2 + 1;//递推
	}
}
void heapSort(int*& arr, int length)//堆排序
{
	if (length <= 1 || arr == nullptr)
		return;
	for (int i = 0; i < length; i++)//构建堆
		heapInsert(arr, i);
	int size = length;
	while (size > 0)
	{
		swap(arr, 0, --size);//把堆顶元素放到最后
		heapify(arr, 0, size);//重新调整堆
	}
}
int main()
{
	linknode *head = new linknode;
	int range, datamode;
	cout << "请输入生成数据规模......" << endl;
	cin >> range;
	if (range>10000000)
	{
		range = 10000000;
	}
	cout << "选择数组：\n1.随机\n2.基本顺序\n3.逆序\n" << endl;
	cin >> datamode;
	int *dataR, *dataP, *data, *usingdata;
	data = initData(range);
	dataR = initReverseData(range);
	dataP = initPositiveData(range);
	if (datamode == 1)
	{
		usingdata = data;
	}
	else if (datamode == 3)
	{
		usingdata = dataR;
	}
	else
	{
		usingdata = dataP;
	}
	while (1)
	{
		system("cls");
		cout << "——————请输入序号选择排序方式——————" << endl;
		cout << "\t\t 1.快速排序" << endl;
		cout << "\t\t 2.链表冒泡排序" << endl;
		cout << "\t\t 3.归并排序" << endl;
		cout << "\t\t 4.堆排序" << endl;
		cout << "\t\t 5.插入排序" << endl;
		cout << "\t\t 6.链表插入排序" << endl;
		cout << "\t\t else.退出" << endl;
		cout << "———————————————————————" << endl;
		int sortWay;
		cin >> sortWay;
		cout << "请输入要查找的前d个最大的数\nd=";
		int d;
		cin >> d;
		system("cls");
		cout << "排序中......\r";
		auto start = system_clock::now(); //开始计时
		switch (sortWay)
		{
		case 3:
		{
			mergeSort(usingdata, range);
			auto duration = duration_cast<microseconds>(system_clock::now() - start);
			cout << "归并排序耗时:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
			output(usingdata, range, "mergeSort");
			cout << endl;
			for (int i = range - 1; i > range - d; i--)
				cout << usingdata[i] << endl;
			break;
		}
		case 1:
		{
			quickSort(usingdata, range);
			auto duration = duration_cast<microseconds>(system_clock::now() - start);
			cout << "快速排序耗时:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
			output(usingdata, range, "quickSort");
			cout << endl;
			for (int i = range - 1; i > range - d; i--)
				cout << usingdata[i] << endl;
			break;
		}
		case 4:
		{
			heapSort(usingdata, range);
			auto duration = duration_cast<microseconds>(system_clock::now() - start);
			cout << "堆排序耗时:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
			output(usingdata, range, "heapSort");
			cout << endl;
			for (int i = range - 1; i > range - d; i--)
				cout << usingdata[i] << endl;
			break;
		}
		case 2:
			{
				inilinkdata(head,range);
				Bubble_sort_link(head);
				auto duration = duration_cast<microseconds>(system_clock::now() - start);
				cout << "链表冒泡排序耗时:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
				output(usingdata, range, "Bubble_sort_link");
				cout << endl;
				linknode* current = head->rlink;
				for (int i = range - 1; i > range - d&&current!=head; i--)
				{
					cout <<current->data << endl;
					current = current->rlink;
				}
				break;
			}
		case 5:
		{
			insertSort(usingdata, range);
			auto duration = duration_cast<microseconds>(system_clock::now() - start);
			cout << "插入排序耗时:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
			output(usingdata, range, "insertSort");
			cout << endl;
			for (int i = range - 1; i > range - d; i--)
				cout << usingdata[i] << endl;
			break;
		}
		case 6:
		{
			inilinkdata(head, range);
			insertSort_link(head);
			auto duration = duration_cast<microseconds>(system_clock::now() - start);
			cout << "链表插入排序耗时:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
			output(usingdata, range, "insertSort_link");
			cout << endl;
			linknode* current = head->rlink;
			for (int i = range - 1; i > range - d && current != head; i--)
			{
				cout << current->data << endl;
				current = current->rlink;
			}
			break;
		}
		default:
			goto a;
		}
		system("pause");

	}


a:system("pause"); 
	return 0;
}