#include<iostream>
#include<string>
#include<graphics.h>
#include<easyx.h>
#include<cmath>
#include<vector>
#define PI 3.1415026
using namespace std;
void menu();
struct TreeNode
{
	string data;
	TreeNode* Left_child = NULL;
	TreeNode* Right_child = NULL;
};
string glue(vector<string>x)
{
	string temp;
	for (int i = 0; i < x.size(); i++)
	{
		temp += x[i];
	}
	return temp;
}
vector<string> transform(string input)
{
	vector<string>temp;
	string temp1 = "";
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] != ' ')
		{
			temp1 += input[i];
			continue;
		}
		if (input[i] == ' ')
		{
			temp.push_back(temp1);
			temp1.clear();
			continue;
		}
	}
	temp.push_back(temp1);
	return temp;
}
int FindPos(vector<string> s, string x)
{
	int Pos;
	int count = 0;
	for (int i = 0; i < int (s.size()); i++)
	{
		if (x == s[i])
		{
			Pos = i;
			count++;
		}
	}
	if (count == 0)
	{
		closegraph();
		cout << "先序序列与中序序列不匹配！请重新输入！";
		system("pause");
		system("cls");
		menu();
	}
	if (count > 1)
	{
		closegraph();
		cout << "序列中出现重复元素！ 请重新输入！";
		system("pause");
		system("cls");
		menu();
	}
	return Pos;
}

void In_Mid_BuildTree(vector<string> in, vector<string> mid, TreeNode* node,int x ,int y , int judge,double i)//x,y 为横纵坐标 judge用来判断 该节点是左孩子还是右孩子
{
	if (in.empty() && mid.empty())
	{
		return;
	}
	if (in.size()!=mid.size())
	{
		closegraph();
		cout << "序列不匹配！";
		system("pause");
		system("cls");
		menu();
	}
	if (in.size()==1&&mid.size()==1&&in[0]!=mid[0])
	{
		closegraph();
		cout << "序列不匹配！";
		system("pause");
		system("cls");
		menu();
	}
	clearrectangle(0, 0, 200, 80);
	circle(x, y, 20);
	outtextxy(x-4, y-7, in[0].c_str());
	int Pos = FindPos(mid, in[0]);
	node->data = in[0];
	vector<string> L_in(in.begin() + 1, in.begin() + Pos + 1);
	vector<string> L_mid(mid.begin(), mid.begin() + Pos);
	vector<string> R_in(in.begin() + Pos + 1, in.end());
	vector<string> R_mid(mid.begin() + Pos + 1, mid.end());
	string output_node = "当前节点：" + in[0];
	string output_in = "当前先序："+glue(in);
	string output_mid = "当前中序："+glue(mid);
	outtextxy(0, 0, output_node.c_str());
	outtextxy(0, 20, output_in.c_str());
	outtextxy(0, 40, output_mid.c_str());
	Sleep(1000);
	if (!L_in.empty() && !L_mid.empty())
	{
		TreeNode * Left_child = new TreeNode;
		node->Left_child = Left_child;
		int x1 = x - 80 * sin(i);
		int y1 = y + 80 * cos(i);
		int x_start = x - int (20 * sin(i));
		int y_start = y + 20 * cos(i);
		int x_end = x1 + 20 * sin(i);
		int y_end = y1 - 20 * cos(i);
		line(x_start, y_start, x_end, y_end);
		Sleep(2000);
		In_Mid_BuildTree(L_in, L_mid, Left_child,x1,y1,-1,i/1.5);
		
	}
	if (!R_in.empty() && !R_mid.empty())
	{
		TreeNode * Right_child = new TreeNode;
		node->Right_child = Right_child;
		int x1 = x + 80 * sin(i);
		int y1 = y + 80 * cos(i);
		int x_start = x + 20 * sin(i);
		int y_start = y + 20 * cos(i);
		int x_end = x1 - 20 * sin(i);
		int y_end = y1 - 20 * cos(i);
		line(x_start, y_start, x_end, y_end);
		Sleep(2000);
		In_Mid_BuildTree(R_in, R_mid, Right_child,x1,y1,1,i/1.5);
		
	}
}
void Mid_Last_BuildTree(vector<string> mid, vector<string> last, TreeNode* node, int x, int y, int judge, double i)
{
	if (mid.empty() && last.empty())
	{
		return;
	}
	if (last.size() != mid.size())
	{
		closegraph();
		cout << "序列不匹配！";
		system("pause");
		system("cls");
		menu();
	}
	if (last.size() == 1 && mid.size() == 1 && last[0] != mid[0])
	{
		closegraph();
		cout << "序列不匹配！";
		system("pause");
		system("cls");
		menu();
	}
	clearrectangle(0, 0, 200, 80);
	circle(x, y, 20);
	outtextxy(x - 4, y - 7, last[last.size() - 1].c_str());
	string output_node = "当前节点：" + last[last.size() - 1];
	string output_mid = "中序：" + glue(mid);
	string output_last = "后序：" + glue(last);
	outtextxy(0, 0, output_node.c_str());
	outtextxy(0, 20, output_mid.c_str());
	outtextxy(0, 40, output_last.c_str());
	Sleep(1000);
	int Pos = FindPos(mid, last[last.size() - 1]);
	node->data = last[last.size() - 1];
	vector<string> L_last(last.begin(), last.begin() + Pos);
	vector<string> L_mid(mid.begin(), mid.begin() + Pos);
	vector<string> R_last(last.begin() + Pos, last.end() - 1);
	vector<string> R_mid(mid.begin() + Pos + 1, mid.end());
	if (!L_last.empty() && !L_mid.empty())
	{
		TreeNode * Left_child = new TreeNode;
		node->Left_child = Left_child;
		int x1 = x - 80 * sin(i);
		int y1 = y + 80 * cos(i);
		int x_start = x - int(20 * sin(i));
		int y_start = y + 20 * cos(i);
		int x_end = x1 + 20 * sin(i);
		int y_end = y1 - 20 * cos(i);
		line(x_start, y_start, x_end, y_end);
		Sleep(2000);
		Mid_Last_BuildTree(L_mid, L_last, Left_child, x1, y1, 1, i / 1.5);
	}
	if (!R_last.empty() && !R_mid.empty())
	{
		TreeNode * Right_child = new TreeNode;
		node->Right_child = Right_child;
		int x1 = x + 80 * sin(i);
		int y1 = y + 80 * cos(i);
		int x_start = x + 20 * sin(i);
		int y_start = y + 20 * cos(i);
		int x_end = x1 - 20 * sin(i);
		int y_end = y1 - 20 * cos(i);
		line(x_start, y_start, x_end, y_end);
		Sleep(2000);
		Mid_Last_BuildTree(R_mid, R_last, Right_child, x1, y1, 1, i / 1.5);
	}
}
void output(TreeNode * node)
{
	if (node==NULL)
	{
		return;
	}
	cout << node->data;
	output(node->Left_child);
	output(node->Right_child);
}
void menu()
{
	int judge = 0;
	cout << "请选择功能：" << endl << "（1）根据先序和中序构建二叉树" << endl << "（2）根据后序和中序构建二叉树" << endl << "（3）退出系统" << endl;
	cin >> judge;
	if (judge == 1)
	{
		string in_order, mid_order;
		cout << "请输入先序序列：";
		getchar();
		getline(cin,in_order);
		cout << "请输入中序序列：";
		getline(cin, mid_order);
		vector<string>in = transform(in_order);
		vector<string>mid = transform(mid_order);

		if (in_order.size()!=mid_order.size())
		{
			cout << "先序序列与中序序列所含结点数不同！ 请重新输入！";
			system("pause");
			system("cls");
			menu();
		}
		TreeNode* root = new TreeNode;
		initgraph(640, 480);
		In_Mid_BuildTree(in, mid, root, 320 ,50 , 0, PI/3);
		system("pause");
		closegraph();
		output(root);
	}
	if (judge == 2)
	{
		string last_order, mid_order;
		cout << "请输入中序序列：";
		getchar();
		getline(cin, mid_order);
		cout << "请输入后序序列：";
		getline(cin, last_order);
		vector<string>last = transform(last_order);
		vector<string>mid = transform(mid_order);
		if (last_order.size() != mid_order.size())
		{
			cout << "先序序列与中序序列所含结点数不同！ 请重新输入！";
			system("pause");
			system("cls");
			menu();
		}
		TreeNode* root = new TreeNode;
		initgraph(640, 480);
		Mid_Last_BuildTree(mid, last, root, 320, 50, 0, PI / 3);
		system("pause");
		closegraph();
		output(root);
	}
	if (judge == 3)
	{
		exit(0);
	}
	system("pause");
	system("cls");
	menu();
}
int main()
{   
	menu();
	system("pause");
	return 0;
}