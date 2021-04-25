#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
vector<int>item;//存放两个文件的item
vector<int>value;//存放两个文件的value
vector<string>result;//存放结果
int main()
{
	char data1[100];//存放data1的所有字符
	char data2[100];//存放data2的所有字符
	fstream inf1("E://data1.txt");//打开data1 读取文件
	if (!inf1.is_open())
	{
		cout << "文件打开失败！！！";
		exit(1);
	}
	while (!inf1.eof())
	{
		inf1.getline(data1, 100);//直到文件末尾逐行读取
	}
	inf1.close();
	string s1;
	for (int i = 0; i < strlen(data1); i++)
	{
		s1.push_back(data1[i]);//将字符数组转化为字符串
	}
	vector<string>vec1;
	string tem1;
	for (int i = 0; i <= s1.size(); i++)//将data1的所有数字取出并分别放入向量中
	{
		if (s1[i]==' '||s1[i]==':' || s1[i] == '\0')
		{
		vec1.push_back(tem1);
		tem1.clear();
		continue;
		}	
		tem1.push_back(s1[i]);
	}
	fstream inf2("E://data2.txt");
	if (!inf2.is_open())
	{
		cout << "文件打开失败！！！";
		exit(1);
	}

	while (!inf2.eof())
	{
		inf2.getline(data2, 100);
	}
	inf2.close();
	string s2;
	for (int i = 0; i < strlen(data2); i++)
	{
		s2.push_back(data2[i]);
	}
	tem1.clear();
	for (int i = 0; i <= s2.size(); i++)
	{
		if (s2[i] == ' ' || s2[i] == ':' || s2[i] =='\0')
		{
			vec1.push_back(tem1);
			tem1.clear();
			continue;
		}
		tem1.push_back(s2[i]);
	}
	for (int i = 0; i < vec1.size(); i++)
	{
		if (i%2==0)
		{
			item.push_back(atoi(vec1[i].c_str()));//将data1与data2的item取出
		}
		if (i%2==1)
		{
			value.push_back(atoi(vec1[i].c_str()));//将data1与data2中的value取出
		}
	}
	for (int i = 0; i < item.size()-1; i++)
	{
		for (int j = i+1; j < item.size(); j++)
		{
			if (item[i]>=item[j])
			{
				int temp1 = item[i];
				item[i] = item[j];//将item排序
				item[j] = temp1;
				int temp2 = value[i];
				value[i] = value[j];//对应的value排序
				value[j] = temp2;
			}

		}
	}
	for (int i = 0; i < item.size()-1; i++)
	{
		for (int j = i+1; j < item.size(); j++)
		{
			if (item[i]==item[j])
			{
				value[i] += value[j];//将item相同组去掉
				item.erase(item.begin() + j);//将item相同组去掉
				value.erase(value.begin() + j);
			}
		}
	}
	for (int i = 0; i < item.size(); i++)
	{
		string tem1 = to_string(item[i]);
		string tem2 = to_string(value[i]);
		string tem3 = tem1 + ":" + tem2 + " ";//将item与value转化为字符串格式
		result.push_back(tem3);
	}
	ofstream outfile;
	outfile.open("E:\\data3.txt", ios::ate);//输出
	int count = 0;
	for (int i = 0; i < result.size(); i++)
	{
		outfile << result[i];
		count++;
		if (count==10)
		{
			outfile << endl;
		}
	}
	outfile.close();
	cout << "文件写入成功！" << endl;
	system("pause");
	return 0;
}