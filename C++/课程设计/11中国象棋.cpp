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
	virtual bool judge_move(chessbord&cb, int startx, int starty, int endx, int endy)=0// �ж������ƶ��ĺ�����
	{
	}
	virtual ~chess()
	{
	}
};
class chessbord
{
private:chess*c[10][11];//����
		char chessword[15][4] = { "��","��","��","��","��","��","˧"," ","��","ʿ","��","�R","܇","�h","��" };//���� һ�������ĸ��ֽ�
public:
	static int player;//˧Ϊ-1 ��Ϊ1
	static bool end;
	chessbord();
	~chessbord();
	chess *get(int x, int y);//����ָ�����ָ��
	int getid(int x, int y);//����ָ�����ӵ�ID
	bool Move(int startx, int starty, int endx, int endy);//�ƶ�
	void init();//��ʼ��
	void show();//չʾ
	void play();
};
class General :public chess//���� ˧�� ID Ϊ -1 �� 1
{
public :
	General(int i) :chess((i == 0 ? -1 : 1)) {};//�ж�Ϊ��һ��������
	bool judge_move(chessbord&ch, int startx, int starty, int endx, int endy)
	{
		int tempx = startx - endx;//�������λ����
		int tempy = starty - endy;//��������λ����
		int s_id = ch.getid(startx, starty);//��������ӵ�id
		int e_id = ch.getid(endx, endy);//��㴦���ӵ�id
		if ((s_id*e_id<=0)&&(tempx*tempx+tempy*tempy==1)&&(endx >= 4 && endx <= 6) && (endy >= 1 && endy <= 3 || endy >= 8 && endy <= 10))
		{//���õ���������㴦��IDӦ��С�ڵ���0��Ҫô��㴦idΪ�գ�Ҫô��㴦��id������������ӵķ����෴ �����ͬΪͬһ���Ĳ����£�
		 //˧������һ��ֻ����һ�����Ժ��������ƽ����Ϊ1 �Ҳ��ܳ��������������ָ�
			return true;
		}
		return false;
	}
};
class Guardian :public chess//ʿ���� ID Ϊ -2 �� 2
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
		{//ʿֻ��б���� ��ζ�ź�����������Ϊһ ���������������ƽ���͵���2 �Ҳ��ܳ��������ָ�
			return true;
		}
		return false;
	}
};
class Xiang :public chess//���� IDΪ -3 �� 3
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
		{//������ ��������Ϊ2 ����ƽ����Ϊ8 ���� ������ֻ��Ϊ���� �Ҳ��ܹ��� (starty - 1) / 5 == (endy - 1) / 5 �ж��Ƿ���� ����������㴦������λ�ò�������
			return true;
		}
		return false;
	}
};
class Horse :public chess//�R���� ID Ϊ -4��4
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
		{//������ ���������ƽ����Ϊ5 ������ǰ�����������ڽ�λ���ϲ��������� !ch.get(startx + (tempx/ 2), starty + (tempy / 2) �ж�
			return true;
		}
		return false;
	}
};
class Car :public chess//܇�ͳ� IDΪ-5��5
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
		{						//��ֻ����һ������ǰ����������һ��
			if (tempx!=0)//����Ƿ񳵵�ǰ���������б�������
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
class Pao : public chess//�h���� ID -6 �� 6
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
			int tmp = 0;//��¼��ǰ�������ϰ��ĸ���
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
			if (e_id)//���Ӵ�������
			{
				if (tmp == 1)//���м�ֻ����һ�����ӳ���
				{
					return true;
				}
			}
			else//��㴦������
			{
				if (tmp == 0)//�м䲻��������
				{
					return true;
				}
			}
		}
		return false;
	}
};
class Soldier :public chess//��ͱ� ID Ϊ-7��7
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
			// (e_id*tempy <= 0)) �ж����Ӻ��ܻ�ͷ
			if (fabs(tempy)==1 && tempx == 0)
			{	//ֻ�������ƶ�����
				return true;
			}
			if (fabs(tempx)==1 && tempy==0)
			{
				if (((starty - 1) / 5 == 0 && s_id < 0) || ((starty - 1) / 5 == 1 && s_id > 0))
				{//���ӿ��Ժ�����
					return true;
				}
			}
		}
		return false;
	}
};
int chessbord::player = -1;//ȫ�ֱ��� ����ִ�巽
bool chessbord::end = true;//��֤��Ϸ�Ƿ����
chessbord::chessbord()
{
	memset(c, NULL, sizeof(c));//������ȫ����Ϊ��ָ��
}
chess* chessbord::get(int x, int y)
{
	return c[x][y];//��������Ŀ��λ���ϵĵ�ַ
}
int chessbord::getid(int x, int y)
{
	if (c[x][y]!=NULL)
	{
		return c[x][y]->get();//��������Ŀ��λ����ָ����������͵�id
	}
	return NULL;
}
bool chessbord::Move(int startx, int starty, int endx, int endy)//�ƶ�����
{
	if (startx>=1 && startx<=9 &&starty>=1 &&starty<=10 && endx >= 1 && endx <= 9 && endy >= 1 && endy <= 10 && getid(startx, starty) && getid(startx, starty)*player > 0 && c[startx][starty]->judge_move(*this, startx, starty, endx, endy))
	{
		if (c[endx][endy]!=NULL)//Ŀ��λ���ϲ�Ϊ��
		{
			delete c[endx][endy];//����
		}
		c[endx][endy] = c[startx][starty];//�����õ���������Ŀ�괦
		c[startx][starty] = NULL;//�����õ�����ԭλ�ô��ÿ�
		player *= -1;//����
		return true;
	}
	else
	{
		cout << "�߷��������������룺" << endl;
		return false;
	}
}
void chessbord::init()//�����ӷ��������� ��ʼ��
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
void chessbord::show()//��ӡ����
{
	cout << endl;
	cout << "     P2  һ �� �� �� �� �� �� �� ��" << endl << endl;
	char num[11][4] = { "��","һ","��","��","��","��","��","��","��","��" ,"ʮ" };
	for (int i = 1; i < 11; i++)
	{
		if (i == 6)
		{
			cout << "          ������������ ���硪������" << endl << endl;
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
				cout << "��" << " ";
			}
			else
			{
				cout << "ʮ" << " ";
			}
		}
		cout << endl << endl;
	}
	cout << "     P1  һ �� �� �� �� �� �� �� ��" << endl << endl;
}
void chessbord::play()//��ʼ��Ϸ
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
			cout << "��P" << (chessbord::player == 1 ? 2 : 1) << "������ʼ����λ����Ŀ��λ�õ����꣺" << endl;//�ж�ִ�巽
			cin >> starty >> startx >> aimy >> aimx;
		} while (!this->Move(startx, starty, aimx, aimy));
		system("cls");
		this->show();
		for (int i = 4; i < 7; i++)//�ж�˧�뽫�Ƿ�����
		{
			this->show();          //����˧�����ڵ�4��5��6 �����н���˧�Ƿ���ͬһ�������߼��ָ��ΪȫΪ��ָ�룻
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
			chessbord::end = false;//�и�
		}
	} while (chessbord::end);//ֱ��end Ϊ false ����
	cout << "������Ӯ����Player" << (chessbord::player == 1 ? 1 : 2) << endl;
}
chessbord::~chessbord()//�������� ������ȫ����Ϊ��ָ��
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