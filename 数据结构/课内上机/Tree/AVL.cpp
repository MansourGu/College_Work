#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;
struct AVLNode
{
	string word;
	string translation;
	AVLNode*Left_Child = NULL;
	AVLNode*Right_Child = NULL;
	int height = 0;
	int balancefactor = 0;
	AVLNode() {};
	AVLNode(string w, string trans)
	{
		word = w;
		translation = trans;
		AVLNode*Left_Child = NULL;
		AVLNode*Right_Child = NULL;
		int height = 0;
		int balancefactor = 0;
	}
};
vector<AVLNode>avl;
AVLNode* root_avl = NULL;
int Get_height(AVLNode* node)
{
	if (node == NULL)
	{
		return 0;
	}
	if (Get_height(node->Left_Child)> Get_height(node->Right_Child))
	{
		return Get_height(node->Left_Child) + 1;
	}
	else return Get_height(node->Right_Child)+1;
}
int Get_BalanceFactor(AVLNode * node)
{
	if (node == NULL)
	{
		return 0;
	}
	else return Get_height(node->Right_Child) - Get_height(node->Left_Child);
}
bool Balance_Judge(AVLNode* node)
{
	if (node == NULL)
	{
		return true;
	}
	int left = Get_height(node);
	int right = Get_height(node);
	if (abs(left-right)>1)
	{
		return false;
	}
	else return true;
}
void LLRotate(AVLNode *& ptr)
{
	AVLNode *node = ptr;
	ptr = node->Left_Child;
	node->Left_Child = ptr->Right_Child;
	ptr->Right_Child = node;
	ptr->balancefactor = node->balancefactor = 0;
	return;
}
void RRRotate(AVLNode*& ptr)
{
	AVLNode* node = ptr;
	ptr = node->Right_Child;
	node->Right_Child = ptr->Left_Child;
	ptr->Left_Child = node;
	ptr->balancefactor = node->balancefactor = 0;
	return ;
}
void* LRRotate(AVLNode*& ptr)
{
	AVLNode* node_left = ptr;             //B
	AVLNode* node_left_right = node_left->Right_Child; //C
	node_left->Right_Child = node_left_right->Left_Child;
	node->Left_Child = node_left_right->Right_Child;
	node_left_right->Left_Child = node_left;
	node_left_right->Right_Child = node;

	return node_left_right;
}
AVLNode* RLRotate(AVLNode*& node)
{
	AVLNode* node_right = node->Right_Child;          //B
	AVLNode* node_right_left = node_right->Left_Child;//C
	node_right->Left_Child = node_right_left->Right_Child;
	node->Right_Child = node_right_left->Left_Child;
	node_right_left->Left_Child = node;
	node_right_left->Right_Child = node_right;
	return node_right_left;
}
AVLNode* Insert(AVLNode node, AVLNode* root)
{
	if (root == NULL)
	{
		root = new AVLNode(node.word,node.translation);
		return root;
	}


}
void Readdata()
{
	ifstream txt("C:\\Users\\hasee\\Desktop\\2.txt");
	string currentline;
	string key, translation;

	while (!txt.eof())
	{
		int index = 1;
		getline(txt, currentline);
		for (; currentline[index] != '"'; index++)
		{
			key.push_back(currentline[index]);
		}
		index += 3;
		for (; currentline[index] != '"'; index++)
		{
			translation.push_back(currentline[index]);
		}
		AVLNode temp;
		temp.word = key;
		temp.translation = translation;
		avl.push_back(temp);
		key.clear();
		translation.clear();
	}
	txt.close();
	cout << "×°ÔØÍê±Ï£¡";
}
int main()
{
	Readdata();
	system("pause");
	return 0;
}