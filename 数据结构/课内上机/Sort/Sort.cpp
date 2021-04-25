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
using namespace chrono;//time library ���ڼ�ʱ
struct linknode
{
	int data;
	linknode*llink = NULL;
	linknode*rlink = NULL;
};
void swap(int*& arr, int a, int b)//��������ָ���±������
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}
void inilinkdata(linknode*head, int range)//�����������
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
void output(int* arr, int len, string textName)//������������ļ�
{
	cout << "���ڽ����ݴ����ļ�......\r";
	ofstream output(textName + ".txt");
	if (output.is_open())
	{
		for (int i = 0; i < len; i++)
			output << arr[i] << "\n";
		output.close();
	}
	cout << "���ݴ������......         \r";
	system("pause");
}
int* initData(int range)//�����������
{
	int* data = new int[range]; //��̬���鴢������
	srand((int)time(0));
	for (int i = 0; i < range; i++)
	{
		int rand1 = rand() % 10000;
		int rand2 = rand() % 10000;
		data[i] = ((rand1 * 10000 + rand2) % (MAX - MIN + 1) + MIN);
	}
	return data;
}
int* initPositiveData(int range)//���ɻ�����������
{
	int* data = new int[range]; //��̬���鴢������
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
int* initReverseData(int range)//���ɻ�����������
{
	int* data = new int[range]; //��̬���鴢������
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
void insertSort_link(linknode*head)//��������ֱ�Ӳ�������
{
	if (head->rlink == head)
		return;
	linknode* current = new linknode;
	current = head->rlink;
	while (current != head)
	{
		int value = current->data;//�洢current��ֵ
		linknode* pivot = current->llink;// ���Ҳ����λ�� �Ӻ���ǰ�Ƚ�
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
void Bubble_sort_link(linknode*head)//�����ð������
{
	linknode* current = head->llink; //��������һλ
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
{//ֱ�Ӳ�������
	if (length <= 1 || arr == nullptr)
		return;
	for (int i = 1; i < length; i++)
	{
		int value = arr[i];//�洢arr[i]��ֵ
		int j = i - 1;
		// ���Ҳ����λ�� �Ӻ���ǰ�Ƚ�
		for (; j >= 0; j--)
		{
			if (arr[j] > value)
				arr[j + 1] = arr[j]; // �����ƶ� 
			else
				break;
		}
		arr[j + 1] = value; // �������� 
	}
}
int	partition(int arr[], int left, int right)//�������յķָ��
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
	arr[pivotpos] = pivot;//����׼����������غϵĵط�
	return pivotpos;
}
void quickSort(int* arr, int left, int right)
{
	if (left >= right)
		return;
	if (right - left + 1 < 15) //�����г���С��15ʱʹ��ֱ�Ӳ�������
	{
		int* start = arr + left;
		insertSort(start, right - left + 1);
		return;
	}
	int q = partition(arr, left, right);//�����µķָ��
	quickSort(arr, left, q - 1);
	quickSort(arr, q + 1, right);
}
void quickSort(int*& arr, int length)
{//��������
	if (length <= 1 || arr == nullptr)
		return;
	quickSort(arr, 0, length - 1);
}
void merge(int*& arr, int L, int M, int R)//�ϲ�
{
	int* cent = new int[R - L + 1];//�����µĸ����ռ���Ԫ��
	int i = 0;
	int pFirst = L, pSecond = M + 1;
	while (pFirst <= M && pSecond <= R)//��ʼ�ϲ�
		cent[i++] = arr[pFirst] < arr[pSecond] ? arr[pFirst++] : arr[pSecond++];
	while (pFirst <= M)//δ�Ƚ�������ݴ浽cent������
		cent[i++] = arr[pFirst++];
	while (pSecond <= R)//δ�Ƚ�������ݴ浽cent������
		cent[i++] = arr[pSecond++];
	for (int j = 0; j < (R - L + 1); j++)//���ź���������з��������ԭλ��
		arr[L + j] = cent[j];
}
void mergeSort(int*& arr, int L, int R)//�ָ�
{
	if (L == R)//�����±�����Ѿ�������
		return;
	int mid = (L + R) / 2;//���ֳ�����������
	mergeSort(arr, L, mid);
	mergeSort(arr, mid + 1, R);
	merge(arr, L, mid, R);
}
void mergeSort(int*& arr, int length)//�鲢����
{
	if (arr == nullptr || length < 2)
		return;
	mergeSort(arr, 0, length - 1);
}
void heapInsert(int arr[], int index)//�Ѳ���
{
	while (arr[index] > arr[(index - 1) / 2])//�����׽ڵ����Ƚ�
	{
		swap(arr, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}
void heapify(int*& arr, int index, int size)
{
	int leftChild = index * 2 + 1;//���ӵ���
	while (leftChild < size)//���Ӵ���
	{
		int maxChild = leftChild + 1 < size && arr[leftChild + 1] > arr[leftChild] ? leftChild + 1 : leftChild;//ȡ������ӵ��±�
		int maxAll = arr[maxChild] > arr[index] ? maxChild : index;//���ӵ����ֵ���ڵ㱾���
		if (maxAll == index)
			break;
		swap(arr, maxAll, index);//�����Ӵ��ڸýڵ��򽻻�
		index = maxAll;
		leftChild = index * 2 + 1;//����
	}
}
void heapSort(int*& arr, int length)//������
{
	if (length <= 1 || arr == nullptr)
		return;
	for (int i = 0; i < length; i++)//������
		heapInsert(arr, i);
	int size = length;
	while (size > 0)
	{
		swap(arr, 0, --size);//�ѶѶ�Ԫ�طŵ����
		heapify(arr, 0, size);//���µ�����
	}
}
int main()
{
	linknode *head = new linknode;
	int range, datamode;
	cout << "�������������ݹ�ģ......" << endl;
	cin >> range;
	if (range>10000000)
	{
		range = 10000000;
	}
	cout << "ѡ�����飺\n1.���\n2.����˳��\n3.����\n" << endl;
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
		cout << "���������������������ѡ������ʽ������������" << endl;
		cout << "\t\t 1.��������" << endl;
		cout << "\t\t 2.����ð������" << endl;
		cout << "\t\t 3.�鲢����" << endl;
		cout << "\t\t 4.������" << endl;
		cout << "\t\t 5.��������" << endl;
		cout << "\t\t 6.�����������" << endl;
		cout << "\t\t else.�˳�" << endl;
		cout << "����������������������������������������������" << endl;
		int sortWay;
		cin >> sortWay;
		cout << "������Ҫ���ҵ�ǰd��������\nd=";
		int d;
		cin >> d;
		system("cls");
		cout << "������......\r";
		auto start = system_clock::now(); //��ʼ��ʱ
		switch (sortWay)
		{
		case 3:
		{
			mergeSort(usingdata, range);
			auto duration = duration_cast<microseconds>(system_clock::now() - start);
			cout << "�鲢�����ʱ:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
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
			cout << "���������ʱ:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
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
			cout << "�������ʱ:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
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
				cout << "����ð�������ʱ:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
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
			cout << "���������ʱ:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
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
			cout << "������������ʱ:" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
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