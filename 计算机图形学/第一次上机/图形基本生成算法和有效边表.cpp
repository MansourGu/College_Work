#include<easyx.h>
#include<math.h>
#include<vector>
#include<iostream>
#include<stack>
using namespace std;
struct Vertix
{
	int x;
	int y;
	Vertix(int x1, int y1)
	{
		x = x1;
		y = y1;
	}
	Vertix()
	{
		
	}
};
struct Edge_Item//边表元素
{

	float low_x;
	int y_max;
	float reverse_k;
	Edge_Item * next = NULL;
};
struct Edge_Link //边表头（桶）
{
	int Scanline_No;
	Edge_Item * Item;
};
struct Polygon_//多边形
{
	Vertix * Point; //以后创建动态数组存放顶点
	int num_Vertix;//顶点个数
	int y_Max;
	int y_Min; //用来计算扫描线个数 ymax-ymin+1 = num-scanline
};
struct Polygon_edge_fulfill //多边形边界填充
{
	int y_max;
	int y_min;
	int x_max;
	int x_min;
	Vertix *v;
	int **Point_Matrix;
	int row_line;
	int colum_line;
};
Polygon_edge_fulfill p_edge;//边界填充算法使用
stack<Vertix> fulfill_stack;
vector<Vertix> DDA_for_edge(Vertix start , Vertix end )
{
	int dx, dy, epsl;
	vector<Vertix> v_output;
	float k, xIncrease, yIncrease, x, y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	k = float(end.y - end.x) / float(end.x - start.x);
	x = start.x;
	y = start.y;
	if (abs(dx) > abs(dy))
	{
		epsl = dx;
	}
	else
	{
		epsl = dy;
	}
	xIncrease = float(dx) / float(epsl);
	yIncrease = float(dy) / float(epsl);
	for (int i = 0; i <= epsl; i++)
	{
		Vertix temp(x + 0.5 - p_edge.x_min, y + 0.5 - p_edge.y_min);//放入时减去最低值相对值
		v_output.push_back(temp);
		x += xIncrease;
		y += yIncrease;
	}
	return v_output;
}
void Initial_edge_fulfill_Polygon()
{
	int n;
	cout << "请输入多边形顶点个数：";
	cin >> n;
	p_edge.v = new Vertix[n];
	p_edge.y_max = INT_MIN;
	p_edge.y_min = INT_MAX;
	p_edge.x_max = INT_MIN;
	p_edge.x_min = INT_MAX;
	int x, y;
	for (int i = 0; i < n; i++)
	{
		cout << "请输入第" << (i + 1) << "个坐标 : ";
		cin >> x >> y;
		p_edge.v[i].x = x;
		p_edge.v[i].y = y;
		if (p_edge.y_max < y)
		{
			p_edge.y_max = y;
		}
		if (p_edge.y_min > y)
		{
			p_edge.y_min = y;
		}//记录y的最大最小值
		if (p_edge.x_max < x)
		{
			p_edge.x_max = x;
		}
		if (p_edge.x_min > x)
		{
			p_edge.x_min = x;
		}//记录x的最大最小值
	}
	p_edge.row_line = p_edge.y_max - p_edge.y_min;
	p_edge.colum_line = p_edge.x_max - p_edge.x_min;
	p_edge.Point_Matrix = new int*[p_edge.colum_line];
	for (int i = 0; i < p_edge.colum_line; i++)
	{
		p_edge.Point_Matrix[i] = new int[p_edge.row_line];
	}
	for (int i = 0; i < p_edge.colum_line; i++)
	{
		for (int j = 0; j < p_edge.row_line; j++)
		{
			p_edge.Point_Matrix[i][j] = -2;//初始化为-2 此时所有点都没有涂色
		}
	}

	for (int i = 0; i < n; i++)
	{
		vector<Vertix>out_put_1;
		vector<Vertix>out_put_2;
		int i_1 = (i - 1 + n) % n;
		int i_2 = (i + 1) % n;
		out_put_1 = DDA_for_edge(p_edge.v[i_1], p_edge.v[i]);
		out_put_2 = DDA_for_edge(p_edge.v[i], p_edge.v[i_2]);
		for (int i = 0; i < out_put_1.size(); i++)
		{
			p_edge.Point_Matrix[out_put_1[i].x][out_put_1[i].y] = -1;//将算出的边界点放入矩阵中
		}
		for (int i = 0; i < out_put_2.size(); i++)
		{
			p_edge.Point_Matrix[out_put_2[i].x][out_put_2[i].y] = -1;//将算出的边界点放入矩阵中
		}
	}
	for (int i = 0; i < p_edge.colum_line; i++)
	{
		for (int j = 0; j < p_edge.row_line; j++)
		{
			cout << p_edge.Point_Matrix[i][j];//初始化为-2 此时所有点都没有涂色
		}
		cout << endl;
	}
	system("pause");
}
Polygon_ p;//边表填充时用
Edge_Link * ET;//边表
Edge_Link * AET;//活性边表
Vertix * Limitation; // 边界表
void Initial()
{
	initgraph(1280, 720);
	setorigin(640, 360);//设置坐标原点
	line(-640, 0, 640, 0);
	line(0, -360, 0, 360);
}
void Print_Pixel(Vertix v)
{
	putpixel(v.x, -v.y, RED);
	//cout <<'('<< v.x<<","<<v.y<<")";

}
void Initial_Polygon()
{
	int n;
	cout << "请输入顶点个数：";
	cin >> n;
	if (n<3)
	{
		cout << "顶点少于三个不能构成多边形！";
	}
	p.Point = new Vertix[n];
	p.y_Max = INT_MIN;
	p.y_Min = INT_MAX;
	p.num_Vertix = n;
	int x, y;
	for (int i = 0; i < n; i++)
	{
		cout << "请输入第" << i << "个点的坐标：";
		cin >> x >> y;
		p.Point[i].x = x;
		p.Point[i].y = y;
		if (p.y_Max < y)
		{
			p.y_Max = y;
		}
		if (p.y_Min > y)
		{
			p.y_Min = y;
		}//记录y的最大最小值
	}
}
float Cal_ReverseK(Vertix v1, Vertix v2)
{
	return (float(v2.x - v1.x) / float(v2.y - v1.y));

}
void Sort_Edge_Link(Edge_Link & e)
{
	Edge_Item * current = e.Item;
	Edge_Item * next;
	Edge_Item * temp;
	while (current)
	{
		next = current->next;
		temp = current;
		while (next)
		{
			if (temp->low_x > next->low_x)
			{
				temp = next;
			}
			next = next->next;
		}
		if (temp!=current)//temp != cuurent 说明后面的 x值比 current 小 进行交换 x , yMax , ReverseK
		{
			float temp_x = current->low_x;
			current->low_x = temp->low_x;
			temp->low_x = temp_x;

			int temp_yMax = current->y_max;
			current->y_max = temp->y_max;
			temp->y_max = temp_yMax;

			float temp_reverse_k = current->reverse_k;
			current->reverse_k = temp->reverse_k;
			temp->reverse_k = temp_reverse_k;
		}
		current = current->next;
	}
	current = e.Item;
	Edge_Item *Start = NULL;
	Edge_Item *End = NULL;
	while (current)
	{
		Start = End = current;
		next = Start->next;
		while (next && next->low_x == Start->low_x)
		{
			End = next;
			next = next->next;
		}
		while (Start != End)
		{
			temp = Start;
			next = temp->next;
			while (next != End->next && next )
			{
				if (next->reverse_k < temp->reverse_k)
				{
					temp = next;
				}
				next = next->next;
			}
			if (temp != Start) // 交换值
			{
				float temp_x = Start->low_x;
				Start->low_x = temp->low_x;
				temp->low_x = temp_x;

				int temp_yMax = Start->y_max;
				Start->y_max = temp->y_max;
				temp->y_max = temp_yMax;

				float temp_reverse_k = Start->reverse_k;
				Start->reverse_k = temp->reverse_k;
				temp->reverse_k = temp_reverse_k;
			}
			Start = Start->next;
		} 
		current = End->next;
	}
}
void Construct_ET()//构建边表
{
	int Scanline_num = p.y_Max - p.y_Min + 1;// 扫描线个数
	ET = new Edge_Link[Scanline_num];//动态创建ET表
	memset(ET, 0, sizeof(Edge_Link) * Scanline_num);//内存初始化
	Vertix * v = p.Point;//多边形点的集合
	int n_scanline = p.y_Min;//第n行扫描线
	Edge_Item * E_item = NULL;
	for (int i = 0 ; i < Scanline_num; i++ , n_scanline++ )
	{
		ET[i].Scanline_No = n_scanline;//边表表头输入当前扫描线行号
		for (int j = 0; j < p.num_Vertix; j++)
		{
			if (p.Point[j].y == n_scanline)//当前点的y值等于扫描线行号
			{
				int j1 = (j + p.num_Vertix - 1) % p.num_Vertix; // 所有点是按照多边形顺时针或逆时针输入 J1为前一位
				int j2 = (j + 1) % p.num_Vertix;//J2 为后一位输入 所以J1 J or J J2 构成两条边
				if (p.Point[j1].y > n_scanline)//如果J1的y值大于此条扫描线行号证明 J1 J 这条边y值最低点在J 将J入边表
				{
					E_item = new Edge_Item;
					E_item->reverse_k = Cal_ReverseK(p.Point[j], p.Point[j1]);
					E_item->low_x = float(p.Point[j].x);
					E_item->y_max = p.Point[j1].y;
					E_item->next = ET[i].Item;//前插法
					ET[i].Item = E_item;
				}
				if (p.Point[j2].y > n_scanline)//如果J2的y值大于此条扫描线的行号证明 J J2 这条边Y值最低值在J 将J入边表
				{
					E_item = new Edge_Item;
					E_item->reverse_k = Cal_ReverseK(p.Point[j], p.Point[j2]);
					E_item->low_x = float(p.Point[j].x);
					E_item->y_max = p.Point[j2].y;
					E_item->next = ET[i].Item;//前插法
					ET[i].Item = E_item;
				}
			}
		}
		Sort_Edge_Link(ET[i]);
	}
	AET = new Edge_Link[Scanline_num];//申请AET表空间
}
void Delete_ET()
{
	if (AET)
	{
		delete AET;
	}
	int Scanline_num = p.y_Max - p.y_Min + 1;
	Edge_Item* e_item;
	Edge_Item* next;
	while (ET)
	{
		for (int i = 0; i < Scanline_num; i++)
		{
			if (ET[i].Item)
			{
				e_item = ET[i].Item;
				next = e_item->next;
				while (e_item)
				{
					next = e_item->next;
					delete e_item;
					e_item = next;
				}
			}

		}
	}
}
void AET_Paint_Polygon()
{
	int Scanline_num = p.y_Max - p.y_Min + 1;
	memset(AET, 0, sizeof(Edge_Link) * Scanline_num);//对AET空间进行初始化
	int no_scanline = p.y_Min;//起始扫描线行号
	int i = 0;
	for ( ;i  < Scanline_num; i++ ,no_scanline++)
	{
		if (ET[i].Item)
		{
			AET[i].Scanline_No = ET[i].Scanline_No;
			AET[i].Item = ET[i].Item;
			break;
		}
	}
	for (int j = i; j < Scanline_num; j++ , no_scanline++)
	{
		if (AET[j].Item)
		{
			Edge_Item * Pre = NULL;
			Edge_Item * Next = AET[j].Item;
			bool Even = true;//判断每一条扫描线交点的奇偶性
			while (Next)
			{
				if (Next->y_max == no_scanline)//当前边的y最大值等于扫描线行号
				{
					if (!Pre)//如果当前边是AET表第一条边 摘掉第一条边
					{
						AET[j].Item = Next->next;
						Next = Next->next;
					}
					else//如果当前边不是AET的第一条边 摘掉当前边
					{
						Pre->next = Next->next;
						Next = Next->next;
					}
				}
				else//如果没有沿着链继续进行
				{
					Even = !Even;
					Pre = Next;
					Next = Next->next;
				}
			}
			bool Fill = false;
			Next = AET[j].Item;
			while (Next && Even)
			{
				Fill = !Fill;//保证每次都是不重复的两个点取出来
				if (Fill)
				{
					int x1 = (int)(Next->low_x + 0.5);//取出两个点
					int x2 = (int)(Next->next->low_x + 0.5);
					for (int i = x1; i <= x2; i++)
					{
						Vertix v1(i, no_scanline);
						Print_Pixel(v1);
						Sleep(1);
					}
				}
				Next = Next->next;
			}
			Next = AET[j].Item;
			int kk = j + 1;//下一行元素
			if (kk < Scanline_num)
			{
				while (Next)//将在下一行仍然存在的边信息更新后放入下一行AET表
				{
					Edge_Item *	e_item = new Edge_Item;
					e_item->low_x = Next->low_x + Next->reverse_k;
					e_item->reverse_k = Next->reverse_k;
					e_item->y_max = Next->y_max;
					e_item->next = AET[kk].Item;
					AET[kk].Item = e_item;
					Next = Next->next;
				}
				Next = ET[kk].Item;
				Edge_Item * temp = NULL;
				while (Next)//将下一行ET表的内容放入AET表
				{
					temp = new Edge_Item;
					temp->reverse_k = Next->reverse_k;
					temp->low_x = Next->low_x;
					temp->y_max = Next->y_max;
					temp->next = AET[kk].Item;
					AET[kk].Item = temp;
					Next = Next->next;
				}
				Sort_Edge_Link(AET[kk]);//将下一行信息进行排序
			}
		}

	}

}
void DDA(Vertix start , Vertix end )
{
	int dx, dy, epsl ;
	float k, xIncrease, yIncrease ,x, y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	k = float(end.y - end.x) / float(end.x - start.x);
	x = start.x;
	y = start.y;
	if (abs(dx)>abs(dy))
	{
		epsl = abs(dx);
	}
	else
	{
		epsl = abs(dy);
	}
	xIncrease = float(dx) / float(epsl);
	yIncrease = float(dy) / float(epsl);
	for (int i = 0; i <= epsl; i++)
	{
		Vertix temp(x+0.5 ,y+0.5);
		Print_Pixel(temp);
		x += xIncrease;
		y += yIncrease;
	}
}
void BH(Vertix start, Vertix end)
{
	int dx, dy, d, UpIncrease, DownIncrease, x, y;
	bool signal = 0; // 如果k值为负时值为1；
	dx = end.x - start.x;
	dy = end.y - start.y;
	if (dx * dy < 0)
	{
		signal = 1;
	}
	if (abs(dy)>abs(dx))// |k| ＞ 1
	{
		if (start.y > end.y)
		{
			x = end.x;
			end.x = start.x;
			start.x = x;
			y = end.y;
			end.y = start.y;
			start.y = y;
		}
		if (signal == 1)
		{
			end.x = -end.x;
			start.x = -start.x;
		}
		y = start.y;
		x = start.x;
		dx = end.x - start.x;
		dy = end.y - start.y;
		d = dy - 2*dx;
		UpIncrease = 2 * dy - 2 * dx;
		DownIncrease = -2 * dx;
		while (y <= end.y)
		{
			if (signal == 1
)
			{
				Vertix temp(-x, y);
				Print_Pixel(temp);
			}
			else
			{
				Vertix temp(x, y);
				Print_Pixel(temp);
			}
			y++;
			if (d < 0)
			{
				x++;
				d += UpIncrease;
			}
			else
			{
				d += DownIncrease;
			}
		}
	}
	else // |k| ≤ 1
	{
		if (start.x > end.x)
		{
			x = end.x;
			end.x = start.x;
			start.x = x;
			y = end.y;
			end.y = start.y;
			start.y = y;
		}
		if (signal == 1)
		{
			end.y = -end.y;
			start.y = -start.y;
		}
			x = start.x;
			y = start.y;
			dx = end.x - start.x;
			dy = end.y - start.y;
			d = dx - 2 * dy;
			UpIncrease = 2 * dx - 2 * dy;
			DownIncrease = -2 * dy;
			while (x <= end.x)
			{
				if (signal == 1)
				{
					Vertix temp(x, -y);
					Print_Pixel(temp);
				}
				else
				{
					Vertix temp(x, y);
					Print_Pixel(temp);
				}
				x++;
				if (d < 0)
				{
					y++;
					d += UpIncrease;
				}
				else
				{
					d += DownIncrease;
				}
				
			}
	}
}
void BH_advanced(Vertix start, Vertix end)
{
	int x, y, dx, dy, e;
	bool signal = 0; // k 值为负时为1
	dx = end.x - start.x;
	dy = end.y - start.y;
	if (dx * dy < 0)
	{
		signal = 1;
	}
	if (abs(dx)> abs(dy))// |k|≤1 
	{
		if (start.x > end.x)
		{
			x = end.x;
			end.x = start.x;
			start.x = x;
			y = end.y;
			end.y = start.y;
			start.y = y;
		}
		if (signal == 1)
		{
			end.y = -end.y;
			start.y = -start.y;
		}
		x = start.x;
		y = start.y;
		dx = end.x - start.x;
		dy = end.y - start.y;
		e = -dx;
		while (x <= end.x)
		{
			if (signal == 1)
			{
				Vertix temp(x, -y);
				Print_Pixel(temp);
			}
			else
			{
				Vertix temp(x, y);
				Print_Pixel(temp);
			}
			x++;
			e = e + 2 * dy;
			if (e>0)
			{
				y++;
				e = e - 2 * dx;
			}
		}
	}
	else
	{
		if (start.y > end.y)
		{
			x = end.x;
			end.x = start.x;
			start.x = x;
			y = end.y;
			end.y = start.y;
			start.y = y;
		}
		if (signal == 1)
		{
			end.x = -end.x;
			start.x = -start.x;
		}
		x = start.x;
		y = start.y;
		dx = end.x - start.x;
		dy = end.y - start.y;
		e = -dy;
		while (y <= end.y)
		{
			if (signal == 1
				)
			{
				Vertix temp(-x, y);
				Print_Pixel(temp);
			}
			else
			{
				Vertix temp(x, y);
				Print_Pixel(temp);
			}
			y++;
			e = e + 2 * dx;
			if (e > 0)
			{
				x++;
				e = e - 2 * dy;
			}
		}
	}
}
void Circle_Point(int x0, int y0 , int x ,int y)
{
	Vertix temp1(x+x0 ,y+y0);
	Vertix temp2(y+x0,x+y0);
	Vertix temp3(-y+x0,x+y0);
	Vertix temp4(-x+x0,y+y0);
	Vertix temp5(-x+x0,-y+y0);
	Vertix temp6(-y+x0,-x+y0);
	Vertix temp7(y+x0,-x+y0);
	Vertix temp8(x+x0,-y+y0);
	Print_Pixel(temp1);
	Print_Pixel(temp2);
	Print_Pixel(temp3);
	Print_Pixel(temp4);
	Print_Pixel(temp5);
	Print_Pixel(temp6);
	Print_Pixel(temp7);
	Print_Pixel(temp8);
}
void BH_Circle(Vertix center, Vertix arc)
{
	int x, y, d;
	int r_2 = pow((arc.x - center.x), 2) + pow((arc.y - center.y), 2);
	y = sqrt(r_2);
	x = 0;
	d = 1 - y;
	while (x<y)
	{
		Circle_Point(center.x, center.y, x, y);
		if (d<0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
	if (x == y)
	{
		Circle_Point(center.x, center.y, x, y);
	}
}
void BH_Ellipse(int c_x,int c_y ,int a , int b)
{
	int x, y;
	float d1, d2;
	x = 0;
	y = b;
	d1 = b * b + a * a + (-b + 0.25);
	Vertix temp1(x+c_x, y+ c_y);
	Vertix temp2(-x + c_x, -y + c_y);
	Vertix temp3(-x + c_x, y + c_y);
	Vertix temp4(x + c_x, -y + c_y);
	Print_Pixel(temp1);
	Print_Pixel(temp2);
	Print_Pixel(temp3);
	Print_Pixel(temp4);
	while (b*b*(x+1)<a*a*(y-0.5))
	{
		if (d1 <= -0.000001)
		{
			d1 += (b*b*(2 * x + 3));
			x++;
		}
		else
		{
			d1 += (b*b*(2 * x + 3) + a * a*(-2 * y + 2));
			x++;
			y--;
		}
		Vertix temp1(x + c_x, y + c_y);
		Vertix temp2(-x + c_x, -y + c_y);
		Vertix temp3(-x + c_x, y + c_y);
		Vertix temp4(x + c_x, -y + c_y);
		Print_Pixel(temp1);
		Print_Pixel(temp2);
		Print_Pixel(temp3);
		Print_Pixel(temp4);
	}
	d2 = b * b*(x + 0.5)*(x + 0.5) + a * a*(y - 1)*(y - 1) - a * a * b * b;
	while (y>0)
	{
		if (d2<= -0.000001)
		{
			d2 += (b * b*(2 * x + 2) + a * a*(-2 * y + 3));
			x++;
			y--;
		}
		else
		{
			d2 += (a * a*(-2 * y + 3));
			y--;
		}
		Vertix temp1(x + c_x, y + c_y);
		Vertix temp2(-x + c_x, -y + c_y);
		Vertix temp3(-x + c_x, y + c_y);
		Vertix temp4(x + c_x, -y + c_y);
		Print_Pixel(temp1);
		Print_Pixel(temp2);
		Print_Pixel(temp3);
		Print_Pixel(temp4);
	}
}
void Paint_Polygon()
{
	Initial_Polygon();
	Construct_ET();
	Initial();
	AET_Paint_Polygon();
	//Delete_ET();
}
bool Check_for_inside(Vertix v)
{
	int count = 0;
	if (v.x < p_edge.x_min || v.x > p_edge.x_max || v.y < p_edge.y_min || v.y > p_edge.y_max)//若点超过了范围判定在界外
	{
		return false;
	}
	else
	{
		for (int i = v.x - p_edge.x_min; i < p_edge.x_max-p_edge.x_min ; i++)//固定一点沿着x增大的方向扫描
		{
			if (p_edge.Point_Matrix[i][v.y-p_edge.x_min] == -1)//遇到边界点
			{
				count++;
			}
		}
		if (count%2 == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
}
bool Check_for_isFufill(Vertix v)
{
	if (p_edge.Point_Matrix[v.x-p_edge.x_min][v.y-p_edge.y_min] == -2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Fulfill()
{
	Vertix seed;
	bool judge = true;
	while (judge)
	{
		cout << "请输入种子点：";
		cin >> seed.x >> seed.y;
		if (Check_for_inside(seed) == false)
		{
			cout << "种子点不在界内 请重新输入：";
			Sleep(3000);
			system("cls");
		}
		else
		{
			judge = false;
		}
	}
	Initial();
	fulfill_stack.push(seed);
	while (!fulfill_stack.empty())
	{
		Vertix p = fulfill_stack.top();
		Vertix p_up(p.x, p.y + 1);
		Vertix p_down(p.x , p.y - 1);
		Vertix p_left(p.x -1, p.y);
		Vertix p_right(p.x + 1, p.y);//四连通路
		Vertix p_up_left(p.x - 1, p.y + 1);
		Vertix p_up_right(p.x + 1, p.y + 1);
		Vertix p_down_left(p.x -1, p.y - 1);
		Vertix p_down_right(p.x + 1 , p.y - 1);//八联通
		fulfill_stack.pop();
		if (Check_for_inside(p_up) && Check_for_isFufill(p_up))
		{	
			Print_Pixel(p_up);
			fulfill_stack.push(p_up);
		}
		if (Check_for_inside(p_down) && Check_for_isFufill(p_down))
		{
			Print_Pixel(p_down);
			fulfill_stack.push(p_down);
		}
		if (Check_for_inside(p_left) && Check_for_isFufill(p_left))
		{
			Print_Pixel(p_left);
			fulfill_stack.push(p_left);
		}
		if (Check_for_inside(p_right) && Check_for_isFufill(p_right))
		{
			Print_Pixel(p_right);
			fulfill_stack.push(p_right);
		}
		if (Check_for_inside(p_up_left) && Check_for_isFufill(p_up_left))
		{
			Print_Pixel(p_up_left);
			fulfill_stack.push(p_up_left);
		}
		if (Check_for_inside(p_up_right) && Check_for_isFufill(p_up_right))
		{
			Print_Pixel(p_up_right);
			fulfill_stack.push(p_up_right);
		}
		if (Check_for_inside(p_down_left) && Check_for_isFufill(p_down_left))
		{
			Print_Pixel(p_down_left);
			fulfill_stack.push(p_down_left);
		}
		if (Check_for_inside(p_down_right) && Check_for_isFufill(p_down_right))
		{
			Print_Pixel(p_down_right);
			fulfill_stack.push(p_down_right);
		}
	}
}
int main()
{	
	
	Vertix s(0, 0), e(100, 100);
	//Initial();
	//DDA(s, e);
	//BH(s, e);
	//BH_advanced(s, e);
	//BH_Circle(s, e);
	//BH_Ellipse(0,0,100, 200);
	Paint_Polygon();
	Initial_edge_fulfill_Polygon();

	//Fulfill();
	system("pause");
	return 0;
}