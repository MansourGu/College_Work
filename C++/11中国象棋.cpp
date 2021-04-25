#include<iostream>
#include<cmath>
#include<memory>
#include<cstring>
#include<cstdlib>
#include<windows.h>
using namespace std;
class chessbord;
class chess
{
private:
	int id;
public:
	chess(int i)
	{
		id = i;
	}
	int get() { return id; }
	virtual bool judge_move(chessbord&cb, int startx, int starty, int endx, int endy)=0// 判断棋子移动的合理性
	{
	}
	virtual ~chess()
	{
	}
};
class chessbord
{
private:chess*c[10][11];//棋盘
		char chessword[15][4] = { "兵","炮","车","马","相","仕","帅"," ","将","士","象","馬","車","砲","卒" };//棋子 一个汉字四个字节
public:
	static int player;//帅为-1 将为1
	static bool end;
	chessbord();
	~chessbord();
	chess *get(int x, int y);//返回指定点的指针
	int getid(int x, int y);//返回指定棋子的ID
	bool Move(int startx, int starty, int endx, int endy);//移动
	void init();//初始化
	void show();//展示
	void play();
};
class General :public chess//将类 帅类 ID 为 -1 和 1
{
public :
	General(int i) :chess((i == 0 ? -1 : 1)) {};//判断为哪一方的棋子
	bool judge_move(chessbord&ch, int startx, int starty, int endx, int endy)
	{
		int tempx = startx - endx;//算横坐标位移量
		int tempy = starty - endy;//算纵坐标位移量
		int s_id = ch.getid(startx, starty);//需调用棋子的id
		int e_id = ch.getid(endx, endy);//落点处棋子的id
		if ((s_id*e_id<=0)&&(tempx*tempx+tempy*tempy==1)&&(endx >= 4 && endx <= 6) && (endy >= 1 && endy <= 3 || endy >= 8 && endy <= 10))
		{//调用的棋子与落点处的ID应该小于等于0（要么落点处id为空，要么落点处的id符号与调用棋子的符号相反 如果相同为同一方的不能下）
		 //帅（将）一次只能走一格所以横纵坐标差平方和为1 且不能出各方的中心米字格
			return true;
		}
		return false;
	}
};
class Guardian :public chess//士，仕 ID 为 -2 和 2
{
public:
	Guardian(int i) :chess((i == 0 ? -2 : 2)){};
	bool judge_move(chessbord&ch, int startx, int starty, int endx, int endy)
	{
		int tempx = startx - endx;
		int tempy = starty - endy;
		int s_id = ch.getid(startx, starty);
		int e_id = ch.getid(endx, endy);
		if ((s_id*e_id<=0)&&(tempx*tempx+tempy*tempy==2)&& (endx >= 4 && endx <= 6) && (endy >= 1 && endy <= 3 || endy >= 8 && endy <= 10))
		{//士只能斜着走 意味着横纵坐标差都必须为一 所以其横纵坐标差的平方和等于2 且不能出中心米字格
			return true;
		}
		return false;
	}
};
class Xiang :public chess//象，相 ID为 -3 和 3
{
public :
	Xiang(int i) :chess((i == 0 ? -3 : 3)){};
	bool judge_move(chessbord&ch, int startx, int starty, int endx, int endy)
	{
		int tempx = startx - endx;
		int tempy = starty - endy;
		int s_id = ch.getid(startx, starty);
		int e_id = ch.getid(endx, endy);
		if ((s_id*e_id<=0)&&(tempx*tempx+tempy*tempy==8)&& (endx % 2 != 0 && endx >= 1 && endy <= 9) && ((starty - 1) / 5 == (endy - 1) / 5) && !ch.get(startx + (tempx / 2), starty + (tempy / 2)))
		{//象走田 横纵坐标差都为2 所以平方和为8 并且 横坐标只能为奇数 且不能过河 (starty - 1) / 5 == (endy - 1) / 5 判断是否过河 并且在与落点处的中心位置不能有棋
			return true;
		}
		return false;
	}
};
class Horse :public chess//馬和马 ID 为 -4和4
{
public:
	Horse(int i) :chess((i == 0 ? -4 : 4)) {};
	bool judge_move(chessbord&ch, int startx, int starty, int endx, int endy)
	{
		int tempx = startx - endx;
		int tempy = starty - endy;
		int s_id = ch.getid(startx, starty);
		int e_id = ch.getid(endx, endy);
		if ((s_id*e_id <= 0) && (tempx*tempx + tempy * tempy == 5)&& !ch.get(startx + (tempx/ 2), starty + (tempy / 2)))
		{//马走日 横纵坐标差平方和为5 且在其前进方向最大的邻近位置上不能有棋子 !ch.get(startx + (tempx/ 2), starty + (tempy / 2) 判断
			return true;
		}
		return false;
	}
};
class Car :public chess//車和车 ID为-5和5
{
public:
	Car(int i) :chess((i == 0 ? -5 : 5)) {};
	bool judge_move(chessbord&ch, int startx, int starty, int endx, int endy)
	{
		int tempx = startx - endx;
		int tempy = starty - endy;
		int s_id = ch.getid(startx, starty);
		int e_id = ch.getid(endx, endy);
		if ((s_id*e_id <= 0) && ((tempx==0||tempy==0)&&(tempx+tempy!=0)))
		{						//车只能向一个方向前进，最少走一格
			if (tempx!=0)//检测是否车的前进方向上有本方棋子
			{
				int sign = (tempx > 0 ? -1 : 1);
				for (int i = 1; i < fabs(tempx); i++)
				{
					if (ch.get(startx + sign * i, starty))
					{
						return false;
					}
				}
			}
			else
			{
				int sign = (tempy > 0 ? -1 : 1);
				for (int i = 1; i < fabs(tempy); i++)
				{
					if (ch.get(startx , starty + sign * i))
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}
};
class Pao : public chess//砲和炮 ID -6 和 6
{
public:
	Pao(int i) :chess((i == 0 ? -6 : 6)) {};
	bool judge_move(chessbord&ch, int startx, int starty, int endx, int endy)
	{
		int tempx = startx - endx;
		int tempy = starty - endy;
		int s_id = ch.getid(startx, starty);
		int e_id = ch.getid(endx, endy);
		if ((s_id*e_id <= 0)&& ((tempx == 0 || tempy == 0) && (tempx + tempy != 0)))
		{
			int tmp = 0;//记录炮前进方向障碍的个数
			if (tempx!=0)
			{
				int sign = (tempx > 0 ? -1 : 1);
				for (int i = 1; i < fabs(tempx); i++)
				{
					if (ch.get(startx + sign * i, starty))
					{
						tmp++;
					}
				}
			}
			else
			{
				int sign = (tempy > 0 ? -1 : 1);
				for (int i = 1; i < fabs(tempy); i++)
				{
					if (ch.get(startx , starty + sign * i))
					{
						tmp++;
					}
				}
			}
			if (e_id)//落子处有棋子
			{
				if (tmp == 1)//当中间只隔着一个棋子成立
				{
					return true;
				}
			}
			else//落点处无棋子
			{
				if (tmp == 0)//中间不能有棋子
				{
					return true;
				}
			}
		}
		return false;
	}
};
class Soldier :public chess//卒和兵 ID 为-7和7
{
public:
	Soldier(int i) :chess((i == 0 ? -7 : 7)) {};
	bool judge_move(chessbord&ch, int startx, int starty, int endx, int endy)
	{
		int tempx = startx - endx;
		int tempy = starty - endy;
		int s_id = ch.getid(startx, starty);
		int e_id = ch.getid(endx, endy);
		if ((s_id*e_id <= 0) && (e_id*tempy<=0))
		{
			// (e_id*tempy <= 0)) 判定过河后不能回头
			if (fabs(tempy)==1 && tempx == 0)
			{	//只有纵向移动成立
				return true;
			}
			if (fabs(tempx)==1 && tempy==0)
			{
				if (((starty - 1) / 5 == 0 && s_id < 0) || ((starty - 1) / 5 == 1 && s_id > 0))
				{//过河课以横着走
					return true;
				}
			}
		}
		return false;
	}
};
int chessbord::player = -1;//全局变量 代表执棋方
bool chessbord::end = true;//验证游戏是否结束
chessbord::chessbord()
{
	memset(c, NULL, sizeof(c));//将棋盘全部置为空指针
}
chess* chessbord::get(int x, int y)
{
	return c[x][y];//返回棋盘目标位置上的地址
}
int chessbord::getid(int x, int y)
{
	if (c[x][y]!=NULL)
	{
		return c[x][y]->get();//返回棋盘目标位置上指向的棋子类型的id
	}
	return NULL;
}
bool chessbord::Move(int startx, int starty, int endx, int endy)//移动棋子
{
	if (startx>=1 && startx<=9 &&starty>=1 &&starty<=10 && endx >= 1 && endx <= 9 && endy >= 1 && endy <= 10 && getid(startx, starty) && getid(startx, starty)*player > 0 && c[startx][starty]->judge_move(*this, startx, starty, endx, endy))
	{
		if (c[endx][endy]!=NULL)//目标位置上不为空
		{
			delete c[endx][endy];//吃子
		}
		c[endx][endy] = c[startx][starty];//将调用的棋子置于目标处
		c[startx][starty] = NULL;//将调用的棋子原位置处置空
		player *= -1;//换方
		return true;
	}
	else
	{
		cout << "走法错误，请重新输入：" << endl;
		return false;
	}
}
void chessbord::init()//将棋子放入棋盘中 初始化
{
	c[1][1] = new Car(1);
	c[9][1] = new Car(1);
	c[2][1] = new Horse(1);
	c[8][1] = new Horse(1);
	c[3][1] = new Xiang(1);
	c[7][1] = new Xiang(1);
	c[4][1] = new Guardian(1);
	c[6][1] = new Guardian(1);
	c[5][1] = new General(1);
	c[2][3] = new Pao(1);
	c[8][3] = new Pao(1);
	c[1][4] = new Soldier(1);
	c[3][4] = new Soldier(1);
	c[5][4] = new Soldier(1);
	c[7][4] = new Soldier(1);
	c[9][4] = new Soldier(1);
	c[1][10] = new Car(0);
	c[9][10] = new Car(0);
	c[2][10] = new Horse(0);
	c[8][10] = new Horse(0);
	c[3][10] = new Xiang(0);
	c[7][10] = new Xiang(0);
	c[4][10] = new Guardian(0);
	c[6][10] = new Guardian(0);
	c[5][10] = new General(0);
	c[2][8] = new  Pao(0);
	c[8][8] = new  Pao(0);
	c[1][7] = new Soldier(0);
	c[3][7] = new Soldier(0);
	c[5][7] = new Soldier(0);
	c[7][7] = new Soldier(0);
	c[9][7] = new Soldier(0);
}
void chessbord::show()//打印棋盘
{
	cout << endl;
	cout << "     P2  一 二 三 四 五 六 七 八 九" << endl << endl;
	char num[11][4] = { "零","一","二","三","四","五","六","七","八","九" ,"十" };
	for (int i = 1; i < 11; i++)
	{
		if (i == 6)
		{
			cout << "          ————楚河 汉界————" << endl << endl;
		}
		cout << "     " << num[i] << "  ";
		for (int j = 1; j < 10; j++)
		{
			if (c[j][i] != NULL)
			{
				if (c[j][i]->get() > 0)
				{
					cout << chessword[c[j][i]->get() + 7] << " ";
				}
				else
				{
					cout << chessword[c[j][i]->get() + 7] << " ";
				}
			}
			else if ((i == 2 && j == 5) || (i == 9 && j == 5))
			{
				cout << "米" << " ";
			}
			else
			{
				cout << "十" << " ";
			}
		}
		cout << endl << endl;
	}
	cout << "     P1  一 二 三 四 五 六 七 八 九" << endl << endl;
}
void chessbord::play()//开始游戏
{
	system("cls");
	this->init();
	this->show();
	do
	{
		int startx, starty, aimx, aimy, iflag;
		int sid, aid;
		iflag = 0;
		do
		{
			sid = aid = 0;
			cout << "请P" << (chessbord::player == 1 ? 2 : 1) << "输入起始棋子位置与目标位置的坐标：" << endl;//判断执棋方
			cin >> starty >> startx >> aimy >> aimx;
		} while (!this->Move(startx, starty, aimx, aimy));
		system("cls");
		this->show();
		for (int i = 4; i < 7; i++)//判断帅与将是否碰面
		{
			this->show();          //将（帅）所在的4、5、6 三列中将和帅是否在同一列且两者间的指针为全为空指针；
			for (int j = 1; j < 11; j++)
			{
				if (c[i][j] != NULL)
				{
					if ((int)fabs(c[i][j]->get()) == 1)
					{
						iflag++;
					}
					else if (iflag != 0 && iflag != 2)
					{
						if ((int)fabs(c[i][j]->get()) != 1)
						{
							iflag--;
						}
					}
				}
			}
		}
		if (iflag == 2)
		{
			player *= -1;
			chessbord::end = false;//判负
		}
	} while (chessbord::end);//直到end 为 false 结束
	cout << "结束，赢家是Player" << (chessbord::player == 1 ? 1 : 2) << endl;
}
chessbord::~chessbord()//析构函数 将棋盘全部置为空指针
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (c[i][j] != NULL)
			{
				delete c[i][j];
				c[i][j] = NULL;
			}
		}
	}
}
int main()
{
	chessbord C;
	C.play();
	system("pause");
	return 0;
}