#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<easyx.h>
using namespace std;
int chess[3][3];//棋盘
int ai = 1;
int user = -1;
int current ;
string AI = " X ";
string User = " O ";
int first_or_last;//判断先后手
struct Vertix
{
	int x;
	int y;
	Vertix(int x_, int y_)
	{
		x = x_;
		y = y_;
	}
	Vertix() {};
};
void Print_X(int x, int y)
{
	line(x - 50, y - 50, x + 50, y + 50);
	line(x - 50, y + 50, x + 50, y - 50);
}
void Print_O(int x, int y)
{
	fillcircle(x, y, 60);
}
void Print_Current()
{
	settextcolor(BLACK);
	settextstyle(25, 0, _T("Consolas"));
	outtextxy(500, 100, _T("当前下棋方"));
	if (current == user)
	{
		outtextxy(530, 130, _T("用户"));
		Print_O(560, 240);
	}
	else if (current == ai)
	{
		outtextxy(530, 130, _T("AI"));
		Print_X(560, 240);
	}
}
void Fill_Chess()
{
	cleardevice();
	line(0, 160, 480, 160);
	line(0, 320, 480, 320);
	line(0, 0, 480, 0);
	line(0, 480, 480, 480);
	line(0, 480, 0, 0);
	line(160, 480, 160, 0);
	line(320, 480, 320, 0);
	line(480, 480, 480, 0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (chess[i][j] == ai)
			{
				Print_X(i * 160 + 80, j * 160 + 80);
			}
			else if (chess[i][j] == user)
			{
				Print_O(i * 160 + 80, j * 160 + 80);
			}
		}
	}
	Print_Current();
}
void Initial()
{
	initgraph(640, 480);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_JOIN_ROUND | PS_ENDCAP_ROUND, 10);
	setfillcolor(WHITE);
	setfillstyle(BS_NULL);
}
Vertix Mouse_Input()
{
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();

		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			int x = m.x / 160;
			int y = m.y / 160;
			Vertix v(x, y);
			return v;
		}
		default:
			break;
		}

}
}
bool Check_uesr_win(int user)
{
	for (int i = 0; i < 3; i++)
	{
		if (chess[i][0] == user && chess[i][1]==user && chess[i][2] == user)//判断一行
		{
			return true;
		}
		else if (chess[0][i] == user && chess[1][i] == user && chess[2][i] == user)//判断一列
		{
			return true;
		}
	}
	if (chess[0][0] == user && chess[1][1] == user && chess[2][2] == user)//主对角线
	{
		return true;
	}
	if (chess[0][2] == user && chess[1][1] == user && chess[2][0] == user)//斜对角线
	{
		return true;
	}
	return false;
}
bool Chess_is_Empty()//判断棋盘是否为空
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (chess[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
void User_Input()
{
	int row, col;
	Vertix v;
	while (true)
	{
		v = Mouse_Input();
		row = v.x;
		col = v.y;
		if (row<3 && row >=0 && col >=0 && col< 3 && chess[row][col] == 0 )//输入的棋子在界内并且未被占用
		{
			break;
		}
		else
		{
			cout << "输入有误！ 请重新输入！"<<endl;
			continue;
		}
	}
	chess[row][col] = user;
}
int AI_Best_Input(int state , int next_state,int alpha ,int beta)
{
	int now = state;
	if (Check_uesr_win(now))
	{
		if (now == ai)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else if (Chess_is_Empty())
	{
		return 0;//没有判断出胜负同时棋盘已经满了那么平局
	}
	else
	{
		int score;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (chess[i][j] == 0)
				{
					chess[i][j] = now;
					score = AI_Best_Input(next_state, state, alpha, beta);
					chess[i][j] = 0;
					if (state == ai)
					{
						if (score >= alpha)
						{
							alpha = score;
						}
						if (alpha > beta)
						{
							return beta;
						}
					}
					else
					{
						if (score <beta)
						{
							beta = score;
						}
						if (beta<=alpha)
						{
							return alpha;
						}
					}
				}

			}
		}
		if (state==ai)
		{
			return alpha;
		}
		else
		{
			return beta;
		}
	}

}
void AI_Input()
{
	int best_x = 0;
	int best_y = 0;
	int best_score = -1000;
	int score;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (chess[i][j] == 0)
			{
				chess[i][j] = ai;
				score = AI_Best_Input(user, ai, -1000, 1000);//初始上下界为无穷
				if (score > best_score)
				{
					best_score = score;
					best_x = i;
					best_y = j;
				}
				chess[i][j] = 0;
			}

		}

	}
	chess[best_x][best_y] = ai;
}
void Initial_Chess()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			chess[i][j] = 0;
		}
	}
	first_or_last = rand() % 2 + 1;
	Initial();
	if (first_or_last != 2)
	{
		first_or_last = 1;
	}
	if (first_or_last ==1)//玩家先手
	{
		current == user;
		Fill_Chess();
	}
	else//电脑先手随机选取一点开始下棋
	{
		int random_x = rand() % 2;
		int random_y = rand() % 2;
		if (random_x < 0)
		{
			random_x = -random_x;
		}
		if (random_y < 0)
		{
			random_y = -random_y;
		}
		current == ai;
		chess[random_x][random_y] = ai;
		Fill_Chess();
	}
}
void Play()
{
	
	Initial_Chess();
	current = user;
	while (!Check_uesr_win(user) && !Check_uesr_win(ai) &&!Chess_is_Empty())//没有输赢平局
	{
		switch (current)
		{
		case -1:User_Input(); current = ai; Fill_Chess(); break;
		case 1:AI_Input(); current = user; Fill_Chess(); break;
		default:
			break;
		}
	}
	if (Check_uesr_win(user))
	{
		settextcolor(RED);
		settextstyle(100, 0, _T("Consolas"));
		outtextxy(150, 200, _T(" 玩家获胜！"));
	}
	else if (Check_uesr_win(ai))
	{
		settextcolor(RED);
		settextstyle(100, 0, _T("Consolas"));
		outtextxy(150, 200, _T(" AI获胜！"));
	}
	else
	{
		settextcolor(RED);
		settextstyle(100, 0, _T("Consolas"));
		outtextxy(150, 200, _T(" 平局！"));
	}
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			Play();
		}
		default:
			break;
		}
	}
}
int main()
{
	srand((unsigned int)time);
	Play();
	system("pause");
	return 0;
}