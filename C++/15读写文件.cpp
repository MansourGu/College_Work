#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
vector<int>item;//��������ļ���item
vector<int>value;//��������ļ���value
vector<string>result;//��Ž��
int main()
{
	char data1[100];//���data1�������ַ�
	char data2[100];//���data2�������ַ�
	fstream inf1("E://data1.txt");//��data1 ��ȡ�ļ�
	if (!inf1.is_open())
	{
		cout << "�ļ���ʧ�ܣ�����";
		exit(1);
	}
	while (!inf1.eof())
	{
		inf1.getline(data1, 100);//ֱ���ļ�ĩβ���ж�ȡ
	}
	inf1.close();
	string s1;
	for (int i = 0; i < strlen(data1); i++)
	{
		s1.push_back(data1[i]);//���ַ�����ת��Ϊ�ַ���
	}
	vector<string>vec1;
	string tem1;
	for (int i = 0; i <= s1.size(); i++)//��data1����������ȡ�����ֱ����������
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
		cout << "�ļ���ʧ�ܣ�����";
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
			item.push_back(atoi(vec1[i].c_str()));//��data1��data2��itemȡ��
		}
		if (i%2==1)
		{
			value.push_back(atoi(vec1[i].c_str()));//��data1��data2�е�valueȡ��
		}
	}
	for (int i = 0; i < item.size()-1; i++)
	{
		for (int j = i+1; j < item.size(); j++)
		{
			if (item[i]>=item[j])
			{
				int temp1 = item[i];
				item[i] = item[j];//��item����
				item[j] = temp1;
				int temp2 = value[i];
				value[i] = value[j];//��Ӧ��value����
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
				value[i] += value[j];//��item��ͬ��ȥ��
				item.erase(item.begin() + j);//��item��ͬ��ȥ��
				value.erase(value.begin() + j);
			}
		}
	}
	for (int i = 0; i < item.size(); i++)
	{
		string tem1 = to_string(item[i]);
		string tem2 = to_string(value[i]);
		string tem3 = tem1 + ":" + tem2 + " ";//��item��valueת��Ϊ�ַ�����ʽ
		result.push_back(tem3);
	}
	ofstream outfile;
	outfile.open("E:\\data3.txt", ios::ate);//���
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
	cout << "�ļ�д��ɹ���" << endl;
	system("pause");
	return 0;
}