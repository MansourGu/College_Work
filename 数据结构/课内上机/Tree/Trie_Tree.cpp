#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>
using namespace std; 
int count1 = 0;
struct word
{
	
	string key;
	string value;
};
struct Node
{
	Node* Child[36] = { NULL };
	char key;
	string value ="";
};
vector<word>Dictionary;
void BuildTree(Node* node, string key, string translation)
{

	int index = key[0] - 'a';
	if (index < 0)
	{
		index += 75;
	}
	if (node->Child[index] == NULL)
	{
		node->Child[index] = new Node;
		node->Child[index]->key = key[0];
	}
	key.erase(key.begin());
	if (key.empty())
	{
		node->Child[index]->value = translation;
		return;
	}
	else
	{
		BuildTree(node->Child[index], key, translation);
	}
}
void searchsequece(string key)
{
	int index = 0;
	for (; index < Dictionary.size(); index++)
	{
		string temp = Dictionary[index].key.substr(0, key.size());
		if (temp == key && Dictionary[index].key.size()==key.size())
		{
			cout << Dictionary[index].value;
			break;
		}
	}
}
void imaginesequece(string key)
{
	int count = 0;
	int index = 0;
	for (; index < Dictionary.size(); index++)
	{
		string temp = Dictionary[index].key.substr(0, key.size());
		if (temp == key)
		{
			cout <<Dictionary[index].key<<"  "<< Dictionary[index].value<<endl;
			count++;
		}
		else if (temp != key&&count!=0)
		{
			break;
		}
		if (count == 10)
		{
			break;
		}
	}
}
void ReadData(Node* root)
{
	ifstream txt("C:\\Users\\hasee\\Desktop\\2.txt");
	string currentline;
	string key, translation;
	
	while (!txt.eof())
	{
		int index = 1;
		getline(txt,currentline);
		for (; currentline[index]!='"'; index++)
		{
			key.push_back(currentline[index]);
		}
		index += 3;
		for (; currentline[index] != '"'; index++)
		{
			translation.push_back(currentline[index]);
		}
		BuildTree(root, key, translation);
		word temp;
		temp.key = key;
		temp.value = translation;
		Dictionary.push_back(temp);
		key.clear();
		translation.clear();
	}
	
}
void Search(Node* node, string key)
{
	int index = key[0] - 'a';
	if (node->Child[index] == NULL)
	{
		
	}
	else
	{
		key.erase(key.begin());
		if (key.empty())
		{
			cout << node->Child[index]->value;
			return;
		}
		else
		{
			Search(node->Child[index], key);
		}
	}
}
void find(Node * node , string text)
{
	if (count1 >= 9)
	{
		return;
	}
	for (int i = 0; i < 36; i++)
	{
		if (node->Child[i] != NULL)
		{			
			find(node->Child[i],text+node->Child[i]->key);	
		}
	}
	if (!node->value.empty())
	{
		cout <<text<<"  "<< node->value << endl;
		count1++;
	}
}
void imagine(Node* node, string key ,string text)
{
	
	int index = key[0] - 'a';
	if (node->Child[index] == NULL)
	{

	}
	else
	{
		key.erase(key.begin());
		if (key.empty())
		{
			find(node->Child[index],text);
		}
		else
		{
			imagine(node->Child[index], key ,text);
		}
	}
}
int main()
{
	Node* root = new Node;
	ReadData(root);
	cout << "1";
	system("pause");
	//Search(root, "zymotechnics");
	imagine(root, "aaa","aaa");
	//searchsequece("zymotechnics");
	imaginesequece("aaa");
	system("pause");
	return 0;
}