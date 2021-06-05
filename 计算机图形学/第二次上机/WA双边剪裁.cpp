#include<iostream>
#include<graphics.h>
#include<utility>
using namespace std;

struct vertex
{
	float x;
	float y;
};

vertex cw[40], sp[40];
int n_cw, n_sp;

void draw_poly(vertex vlist[], int n)
{
	for (int i = 0; i < n; i++)
		line(vlist[i].x, vlist[i].y, vlist[(i + 1) % n].x, vlist[(i + 1) % n].y);
}

int in_out(float x, float y, int x1, int y1, int x2, int y2)
{
	float p = (y - y1)*(x2 - x1) - (x - x1)*(y2 - y1);
	if (p < 0)
		return 0; 
	return 1;   
}

void intersection_lineseg(float &x, float &y, int x1, int y1, int x2, int y2, int xa, int ya, int xb, int yb)//�󽻵㣬�߶ηֶ�
{
	x = -1;
	y = -1;
	if (x2 == x1 && xb == xa)
		return;
	else if (x2 == x1)
	{
		float k2 = (yb - ya) / (float)(xb - xa);
		x = x1;
		y = ya - k2 * (xa - x1);
	}
	else if (xb == xa)
	{
		float k1 = (y2 - y1) / (float)(x2 - x1);
		x = xa;
		y = y1 + k1 * (xa - x1);
	}
	else
	{
		float k1 = (y2 - y1) / (float)(x2 - x1);//������ֱ�ߵ�б��
		float k2 = (yb - ya) / (float)(xb - xa);
		if (k1 == k2)//б�����ƽ�����޽���
			return;
		x = (ya - y1 + k1 * x1 - k2 * xa) / (k1 - k2);
		y = (k1*k2*(xa - x1) + k2 * y1 - k1 * ya) / (k2 - k1);
	}

	if ((x1 >= x2 && (x<x2 || x>x1)) || (x2 >= x1 && (x > x2 || x < x1)) || (y1 >= y2 && (y<y2 || y>y1)) || (y2 >= y1 && (y > y2 || y < y1))
		|| (xa >= xb && (x<xb || x>xa)) || (xb >= xa && (x > xb || x < xa)) || (ya >= yb && (y<yb || y>ya)) || (yb >= ya && (y > yb || y < ya)))
	{
		x = -1;
		y = -1;
	}
}

void WA_Clip()
{
	vertex tempcw[40], tempsp[40];//��ʱ���������Լ���ʱ�ü�Ŀ������
	int tag_sp[40], tag_cw[40], trav_sp[40], trav_cw[40];
	float x, y;
	int entry_list[10];   //��¼�������   
	int e = -1;

	
	int kc = -1;  
	for (int i = 0; i < n_cw; i++)
	{
		vertex tempi[20][2];          
		int ti = -1;
		for (int j = 0; j < n_sp; j++)
		{
			intersection_lineseg(x, y, cw[i].x, cw[i].y, cw[(i + 1) % n_cw].x, cw[(i + 1) % n_cw].y,
				sp[j].x, sp[j].y, sp[(j + 1) % n_sp].x, sp[(j + 1) % n_sp].y);
			if (x == -1)  //or y==-1
				continue;
			ti++;
			tempi[ti][0].x = x;
			tempi[ti][0].y = y;
			int p1 = in_out(sp[j].x, sp[j].y, cw[i].x, cw[i].y, cw[(i + 1) % n_cw].x, cw[(i + 1) % n_cw].y);
			int p2 = in_out(sp[(j + 1) % n_sp].x, sp[(j + 1) % n_sp].y, cw[i].x, cw[i].y, cw[(i + 1) % n_cw].x, cw[(i + 1) % n_cw].y);
			if (p1 == 1 && p2 == 0)
				tempi[ti][1].x = 1;
			else
				tempi[ti][1].x = 0;
		}
		if (ti != -1)
		{
			if (cw[(i + 1) % n_cw].x > cw[i].x)            //��������
			{
			
				int min_idx;//����x����������
				for (int k = 0; k < ti; k++)
				{
					min_idx = k;
					for (int m = k + 1; m < ti + 1; m++)
					{
						if (tempi[m][0].x < tempi[min_idx][0].x)
							min_idx = m;
					}
					float temp = tempi[min_idx][0].x;
					tempi[min_idx][0].x = tempi[k][0].x;
					tempi[k][0].x = temp;
					temp = tempi[min_idx][0].y;
					tempi[min_idx][0].y = tempi[k][0].y;
					tempi[k][0].y = temp;
					temp = tempi[min_idx][1].x;
					tempi[min_idx][1].x = tempi[k][1].x;
					tempi[k][1].x = temp;
				}
			}
			else if (cw[(i + 1) % n_cw].x < cw[i].x)
			{
			
				int max_idx;//����x�Ľ�������
				for (int k = 0; k < ti; k++)
				{
					max_idx = k;
					for (int m = k + 1; m < ti + 1; m++)
					{
						if (tempi[m][0].x > tempi[max_idx][0].x)
							max_idx = m;
					}
					float temp = tempi[max_idx][0].x;
					tempi[max_idx][0].x = tempi[k][0].x;
					tempi[k][0].x = temp;
					temp = tempi[max_idx][0].y;
					tempi[max_idx][0].y = tempi[k][0].y;
					tempi[k][0].y = temp;
					temp = tempi[max_idx][1].x;
					tempi[max_idx][1].x = tempi[k][1].x;
					tempi[k][1].x = temp;
				}
			}
			else if (cw[(i + 1) % n_cw].y > cw[i].y)
			{
				//����y������
				int min_idx;
				for (int k = 0; k < ti; k++)
				{
					min_idx = k;
					for (int m = k + 1; m < ti + 1; m++)
					{
						if (tempi[m][0].y < tempi[min_idx][0].y)
							min_idx = m;
					}
					float temp = tempi[min_idx][0].x;
					tempi[min_idx][0].x = tempi[k][0].x;
					tempi[k][0].x = temp;
					temp = tempi[min_idx][0].y;
					tempi[min_idx][0].y = tempi[k][0].y;
					tempi[k][0].y = temp;
					temp = tempi[min_idx][1].x;
					tempi[min_idx][1].x = tempi[k][1].x;
					tempi[k][1].x = temp;
				}

			}
			else
			{
				//����y�Ľ���
				int max_idx;
				for (int k = 0; k < ti; k++)
				{
					max_idx = k;
					for (int m = k + 1; m < ti + 1; m++)
					{
						if (tempi[m][0].y > tempi[max_idx][0].y)
							max_idx = m;
					}
					float temp = tempi[max_idx][0].x;
					tempi[max_idx][0].x = tempi[k][0].x;
					tempi[k][0].x = temp;
					temp = tempi[max_idx][0].y;
					tempi[max_idx][0].y = tempi[k][0].y;
					tempi[k][0].y = temp;
					temp = tempi[max_idx][1].x;
					tempi[max_idx][1].x = tempi[k][1].x;
					tempi[k][1].x = temp;
				}
			}

			for (int k = 0; k <= ti; k++)              //���ź���Ľ����������Ķ������
			{
				kc++;
				tempcw[kc].x = tempi[k][0].x;
				tempcw[kc].y = tempi[k][0].y;
				tag_cw[kc] = tempi[k][1].x;
				trav_cw[kc] = 0;
			}
		}

		kc++;
		tempcw[kc].x = cw[(i + 1) % n_cw].x;
		tempcw[kc].y = cw[(i + 1) % n_cw].y;
		tag_cw[kc] = -1;
		trav_cw[kc] = 0;
	}

	
	int ks = -1;  
	for (int i = 0; i < n_sp; i++)
	{
		vertex tempi[20][2];           
		int ti = -1;
		for (int j = 0; j < n_cw; j++)
		{
			intersection_lineseg(x, y, cw[j].x, cw[j].y, cw[(j + 1) % n_cw].x, cw[(j + 1) % n_cw].y,
				sp[i].x, sp[i].y, sp[(i + 1) % n_sp].x, sp[(i + 1) % n_sp].y);
			if (x == -1)  //or y==-1
				continue;
			ti++;
			tempi[ti][0].x = x;
			tempi[ti][0].y = y;
			int p1 = in_out(sp[i].x, sp[i].y, cw[j].x, cw[j].y, cw[(j + 1) % n_cw].x, cw[(j + 1) % n_cw].y);
			int p2 = in_out(sp[(i + 1) % n_sp].x, sp[(i + 1) % n_sp].y, cw[j].x, cw[j].y, cw[(j + 1) % n_cw].x, cw[(j + 1) % n_cw].y);
			if (p1 == 1 && p2 == 0) {
				tempi[ti][1].x = 0;
			}
			else {
				tempi[ti][1].x = 1;
			}
		}

		if (ti != -1)
		{
			if (sp[(i + 1) % n_sp].x > sp[i].x)            
			{
				
				int min_idx;
				for (int k = 0; k < ti; k++)
				{
					min_idx = k;
					for (int m = k + 1; m < ti + 1; m++)
					{
						if (tempi[m][0].x < tempi[min_idx][0].x)
							min_idx = m;
					}
					float temp = tempi[min_idx][0].x;
					tempi[min_idx][0].x = tempi[k][0].x;
					tempi[k][0].x = temp;
					temp = tempi[min_idx][0].y;
					tempi[min_idx][0].y = tempi[k][0].y;
					tempi[k][0].y = temp;
					temp = tempi[min_idx][1].x;
					tempi[min_idx][1].x = tempi[k][1].x;
					tempi[k][1].x = temp;
				}
			}
			else if (sp[(i + 1) % n_sp].x < sp[i].x)
			{
				
				int max_idx;
				for (int k = 0; k < ti; k++)
				{
					max_idx = k;
					for (int m = k + 1; m < ti + 1; m++)
					{
						if (tempi[m][0].x > tempi[max_idx][0].x)
							max_idx = m;
					}
					float temp = tempi[max_idx][0].x;
					tempi[max_idx][0].x = tempi[k][0].x;
					tempi[k][0].x = temp;
					temp = tempi[max_idx][0].y;
					tempi[max_idx][0].y = tempi[k][0].y;
					tempi[k][0].y = temp;
					temp = tempi[max_idx][1].x;
					tempi[max_idx][1].x = tempi[k][1].x;
					tempi[k][1].x = temp;
				}
			}
			else if (sp[(i + 1) % n_sp].y > sp[i].y)
			{
				
				int min_idx;
				for (int k = 0; k < ti; k++)
				{
					min_idx = k;
					for (int m = k + 1; m < ti + 1; m++)
					{
						if (tempi[m][0].y < tempi[min_idx][0].y)
							min_idx = m;
					}
					float temp = tempi[min_idx][0].x;
					tempi[min_idx][0].x = tempi[k][0].x;
					tempi[k][0].x = temp;
					temp = tempi[min_idx][0].y;
					tempi[min_idx][0].y = tempi[k][0].y;
					tempi[k][0].y = temp;
					temp = tempi[min_idx][1].x;
					tempi[min_idx][1].x = tempi[k][1].x;
					tempi[k][1].x = temp;
				}

			}
			else
			{
				
				int max_idx;
				for (int k = 0; k < ti; k++)
				{
					max_idx = k;
					for (int m = k + 1; m < ti + 1; m++)
					{
						if (tempi[m][0].y > tempi[max_idx][0].y)
							max_idx = m;
					}
					float temp = tempi[max_idx][0].x;
					tempi[max_idx][0].x = tempi[k][0].x;
					tempi[k][0].x = temp;
					temp = tempi[max_idx][0].y;
					tempi[max_idx][0].y = tempi[k][0].y;
					tempi[k][0].y = temp;
					temp = tempi[max_idx][1].x;
					tempi[max_idx][1].x = tempi[k][1].x;
					tempi[k][1].x = temp;
				}
			}

			for (int k = 0; k <= ti; k++)                       
			{
				ks++;
				tempsp[ks].x = tempi[k][0].x;
				tempsp[ks].y = tempi[k][0].y;
				tag_sp[ks] = tempi[k][1].x;
				if (tag_sp[ks] == 1) {
					e++;
					entry_list[e] = ks;
				}
				trav_sp[ks] = 0;
			}
		}

		ks++;
		tempsp[ks].x = sp[(i + 1) % n_sp].x;
		tempsp[ks].y = sp[(i + 1) % n_sp].y;
		tag_sp[ks] = -1;
		trav_sp[ks] = 0;
	}

	n_cw = kc + 1;
	n_sp = ks + 1;

	
	for (int i = 0; i <= e; i++)
	{
		bool done = false;
		int j = entry_list[i];
		while (!done)
		{
			if (trav_sp[j] == 1)
				done = true;
			else if (tag_sp[j] == 1 || tag_sp[j] == -1)
			{
				line(tempsp[j].x, tempsp[j].y, tempsp[(j + 1) % n_sp].x, tempsp[(j + 1) % n_sp].y);
				trav_sp[j] = 1;
				j++;
			}
			else if (tag_sp[j] == 0)
			{
				trav_sp[j] = 1;
				
				for (int k = 0; k < n_cw; k++)     
				{
					if (tempcw[k].x == tempsp[j].x && tempcw[k].y == tempsp[j].y)
					{
						j = k;
						break;
					}
				}

				swap(tempcw, tempsp);
				swap(tag_cw, tag_sp);
				swap(trav_cw, trav_sp);

				int n = n_cw;
				n_cw = n_sp;
				n_sp = n_cw;
			}
		}
	}
}
void Initial()
{
	initgraph(640, 480);
	setorigin(320, 240);
	setaspectratio(1, -1);
}
int main()
{	
	cout << "����ü����ڵĶ�����" << endl;
	cin >> n_cw;
	cout << "����˳ʱ�����봰�ڶ���" << endl;
	for (int i = 0; i < n_cw; i++)
		cin >> cw[i].x >> cw[i].y;
	Initial();
	draw_poly(cw, n_cw);
	system("pause");
	closegraph();
	cout << "����Ҫ����ͼ�εĶ�����" << endl;
	cin >> n_sp;
	cout << "����˳ʱ�����������ͼ�εĶ�������" << endl;
	for (int i = 0; i < n_sp; i++)
		cin >> sp[i].x >> sp[i].y;
	Initial();
	draw_poly(sp, n_sp);
	system("pause");
	closegraph();
	cout << "�����������ʼ����" << endl;
	system("pause");
	Initial();
	draw_poly(cw, n_cw);
	draw_poly(sp, n_sp);
	system("pause");
	cleardevice();
	draw_poly(cw, n_cw);
	WA_Clip();
	system("pause");
	closegraph();
	return 0;
}