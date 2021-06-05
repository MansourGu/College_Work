#include "easyx.h"
#include "graphics.h"
#include <strstream>
#include <iostream>
#include <ctime>
#pragma comment(lib, "Winmm.lib")
#pragma warning(disable:4996)
#define OPP(c) ((c == 'B') ? 'W' : 'B')
using namespace std;

/*******************************����ȫ�ֱ���*****************************/
const int difficult = 6;		// �Ѷȣ��ݹ����
const int Move[8][2] = {{-1, 0}, {1, 0}, 
						{0, -1}, {0, 1},
						{-1, -1}, {1, -1}, 
						{1, 1}, {-1, 1}};
								// �˸�������չ
char map[8][8];					// ����
IMAGE img[5];					// ����pic
int black, white;				// ˫����������
int X, Y;						// ��������ӵ�
int Round = 1;					// ������
/**********************************��������*****************************/
void load(void);				// �����ز�
void draw(void);				// �����̣�ͬʱ��¼˫�����Ӹ���
void put_down(int, int, char);	// �µ�ǰ�ӣ�ͬʱ��ת
int judge(int, int, char);		// �жϵ�ǰ�Ƿ�������£����ؿɳ�����������ɳԲſ���
bool has_chance(char);			// �ж���������Ƿ��п���λ��
bool is_lose(char);				// �ж��Ƿ�������
bool ask(void);					// �����Ի���
int DP_with_minmax(char, int);	// ��̬�滮������minmax���ҵ��涨�����ڣ��ҷ��ܹ�����������һ��
void play_b(void);				// ��Ϊ��������
void play_w(void);				// ��Ϊ�������

/**********************************���庯��*****************************/
void load(void)		// �����ز�
{
	// ����pic
	loadimage(&img[0], "pic\\Blank.bmp");
	loadimage(&img[1], "pic\\Black.bmp");
	loadimage(&img[2], "pic\\White.bmp");
	loadimage(&img[3], "pic\\Black1.bmp");
	loadimage(&img[4], "pic\\White1.bmp");
	//��ʼ������
	initgraph(340, 340);
	IMAGE board;
	loadimage(&board, "pic\\Board.bmp");
	putimage(0, 0, &board);
	setorigin(26, 26);
	SetWindowText(GetHWnd(), "Reversi");
	int scrWidth, scrHeight;
	RECT rect;
	//�����Ļ�ߴ�
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);
	//ȡ�ô��ڳߴ�
	GetWindowRect(GetHWnd(), &rect);
	//��������rect���ֵ
	rect.left = (scrWidth - rect.right) / 2;
	rect.top = (scrHeight - rect.bottom) / 2;
	SetWindowPos(GetHWnd(), HWND_TOP, rect.left, rect.top, 356, 379, SWP_SHOWWINDOW);
}

void draw(void)	// ������,ͬʱ��¼˫�����Ӹ���
{
	int x, y;
	black = white = 0;
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
			switch(map[x][y]){
				case 0:
						putimage(37 * y, 37 * x, &img[0]);
					break;
				case 'B':
						putimage(37 * y, 37 * x, &img[1]);
					black++;
					break;
				case 'W':
						putimage(37 * y, 37 * x, &img[2]);
					white++;
					break;
			}
}

void put_down(int x, int y, char a)	// �µ�ǰ��
{
	char b = OPP(a);// �з���
	int i, x1, y1, x2, y2;
	bool sign;			
	for (i = 0; i < 8; i++){
		sign = false;
		x1 = x + Move[i][0];
		y1 = y + Move[i][1];
		while (0 <= x1 && x1 < 8 && 0 <= y1 && y1 < 8 && map[x1][y1]){//�������ڣ��Ҹ�λ������
			if(map[x1][y1] == b)
				sign = true;
			else{//�ҵ��˱������ӣ���ʼ��ת��Χ�ڵĵз�����
				if(sign){
					x1 -= Move[i][0];
					y1 -= Move[i][1];
					x2 = x + Move[i][0];
					y2 = y + Move[i][1];
					while (((x <= x2 && x2 <= x1) || (x1 <= x2 && x2 <= x)) && ((y <= y2 && y2 <= y1) || (y1 <= y2 && y2 <= y))){
						map[x2][y2] = a;
						x2 += Move[i][0];
						y2 += Move[i][1];
					}
				}
				break;
			}
			x1 += Move[i][0];
			y1 += Move[i][1];
		}
	}
	map[x][y] = a;
}

int judge(int x, int y, char a)	// �жϵ�ǰ�Ƿ�������£����ؿɳ�����������ɳԲſ���
{
	if(map[x][y])// �����ǰ���ǿյķ���0ֵ
		return 0;
	char b = OPP(a);//�з�����
	int i, x1, y1;
	int n = 0, sign;
	for (i = 0; i < 8; i++){//��˸�������չ����
		sign = 0;
		x1 = x + Move[i][0];
		y1 = y + Move[i][1];
		while (0 <= x1 && x1 < 8 && 0 <= y1 && y1 < 8 && map[x1][y1]){//һֱ����ĳһ��������չ
			if(map[x1][y1] == b)//�����з����ӣ�sign��һ
				sign++;
			else{//������������ҵ���һ����������(while�е�map[x1][y1]�жϱ�֤����һ��)��n��¼���ܹ������ĵз�������
				n += sign;
				break;
			}
			x1 += Move[i][0];
			y1 += Move[i][1];
		}
	}
	return n;// ���ؿɳ�����
}

bool has_chance(char c)	// �ж���������Ƿ��п���λ��
{
	int x, y;
	for(x = 0; x < 8; x++)//ֻҪ����һ�����µĵط��ͷ���true
		for(y = 0; y < 8; y++)
			if(judge(x, y, c))
				return true;
	return false;
}

bool is_lose(char c)// �ж��Ƿ�������
{
	//bool b = false, w = false;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++){
			if(map[i][j] == c)
				return false;
		}
	return true;
}

bool ask(void)	// �����Ի���
{
	HWND wnd = GetHWnd();
	int key;
	char str[50];
	ostrstream strout(str, 50);
	strout <<"�ڣ�" <<black <<"  �ף�" <<white <<endl;
	if (black == white)
		strout <<"ƽ��!";
	else if(black > white)
		strout <<"��Ӯ��!";
	else
		strout <<"������!";
	strout <<"\n����һ����" <<ends;
	if(black == white)
		key = MessageBox(wnd, str, "�;�", MB_YESNO | MB_ICONQUESTION);
	else if(black > white)
		key = MessageBox(wnd, str, "��ʤ", MB_YESNO | MB_ICONQUESTION);
	else
		key = MessageBox(wnd, str, "��ʤ", MB_YESNO | MB_ICONQUESTION);
	if (key == IDYES) {
		Round++;
		return true;
	}
	else return false;
}

int DP_with_minmax(char c, int step)//��һ���ܳԵ����ĵз�����Ϊ����
{
	// �ж��Ƿ�����ݹ�
	if (step > difficult)
		return 0;
	if (!has_chance(c)){
		if (has_chance(OPP(c)))
			return -DP_with_minmax(OPP(c), step);
		else
			return 0;
	}

	int i, j, max = 0, temp, x, y;
	bool ans = false;

	// ������ʱ����,������ǰ���
	char **t = new char *[8];
	for (i = 0; i < 8; i++)
		t[i] = new char [8];
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			t[i][j] = map[i][j];

	// �����ⷨ
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)//N^2
			if (temp = judge(i, j, c)){//N^2
				put_down(i, j, c);//N^3
				temp -= DP_with_minmax(OPP(c), step + 1);
				if (temp > max || !ans){
					max = temp;
					x = i;
					y = j;
					ans = true;
				}
				for (int k = 0; k < 8; k++)
					for (int l = 0; l < 8; l++)
						map[k][l] = t[k][l];
			}

	// �����ռ�
	for (i = 0; i < 8; i++)
		delete[] t[i];
	delete[] t;

	// ����ǵ�һ�����ʶ�������ӵ�
	if (step == 1){
		X = x;
		Y = y;
	}

	return max;// �������Ž�
}

void play_b(void)// ��Ϸ����
{
	// ��ʼ������
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			map[i][j] = 0;
	map[3][4] = map[4][3] = 'B';
	map[3][3] = map[4][4] = 'W';
	draw();
	MOUSEMSG m;
	int total_time = 0;//AI����ʱ
	// ��ʼ��Ϸ
	do
	{
		if (has_chance('B'))// ������������λ��							
		{
			int x, y;
			while (true) {
				while (true){
					m = GetMouseMsg();// ��ȡ�����Ϣ
					if (m.uMsg == WM_LBUTTONDOWN && m.x - 26 < 37 * 8 && m.y - 26 < 37 * 8)
						// ���������
						break;
				}
				x = (m.y - 26) / 37;
				y = (m.x - 26) / 37;
				if (judge(x, y, 'B')){// �����ǰλ����Ч
					put_down(x, y, 'B');//���ӣ�ͬʱ��ת
					draw();
					putimage(37 * y, 37 * x, &img[3]);// ��ʶ���ӵ�
					break;
				}
			}
			if (is_lose('W'))// ������Ƿ�ʧ��
				break;
		}

		if (has_chance('W')){// ��������������λ��
			clock_t start, end;
			start = clock();
			DP_with_minmax('W', 1);// �����ⷨ
			end = clock();
			std::cout << "AI: " << '(' << X + 1 << ',' << char(Y + 65) << ')'
				<< " with " << end - start << "ms" << endl;
			total_time += end - start;
			put_down(X, Y, 'W');
			draw();
			putimage(37 * Y, 37 * X, &img[4]);	// ��ʶ���ӵ�
			if (is_lose('B'))// ����Ƿ�ʧ��
				break;
		}
	}while (has_chance('B') || has_chance ('W'));
	std::cout << "Total time: " << 
		(double)total_time / CLOCKS_PER_SEC << "sec" << endl;
}

void play_w(void) {
	// ��ʼ������
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			map[i][j] = 0;
	map[3][4] = map[4][3] = 'B';
	map[3][3] = map[4][4] = 'W';
	draw();
	MOUSEMSG m;
	int total_time = 0;//AI����ʱ
					   // ��ʼ��Ϸ
	do
	{
		if (has_chance('B')) {// ��������������λ��
			clock_t start, end;
			start = clock();
			DP_with_minmax('B', 1);// �����ⷨ
			end = clock();
			std::cout << "AI: " << '(' << X + 1 << ',' << char(Y + 65) << ')'
				<< " with " << end - start << "ms" << endl;
			total_time += end - start;
			put_down(X, Y, 'B');
			draw();
			putimage(37 * Y, 37 * X, &img[3]);	// ��ʶ���ӵ�
			if (is_lose('W'))// ����Ƿ�ʧ��
				break;
		}

		if (has_chance('W'))// ������������λ��							
		{
			int x, y;
			while (true) {
				while (true) {
					m = GetMouseMsg();// ��ȡ�����Ϣ
					if (m.uMsg == WM_LBUTTONDOWN && m.x - 26 < 37 * 8 && m.y - 26 < 37 * 8)
						// ���������
						break;
				}
				x = (m.y - 26) / 37;
				y = (m.x - 26) / 37;
				if (judge(x, y, 'W')) {// �����ǰλ����Ч
					put_down(x, y, 'W');//���ӣ�ͬʱ��ת
					draw();
					putimage(37 * y, 37 * x, &img[4]);// ��ʶ���ӵ�
					break;
				}
			}
			if (is_lose('B'))// ������Ƿ�ʧ��
				break;
		}
	} while (has_chance('B') || has_chance('W'));
	std::cout << "Total time: " <<
		(double)total_time / CLOCKS_PER_SEC << "sec" << endl;
}
// ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	load();
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);
	do{
		std::cout << "**** " << "Round " << Round << " ****" << endl;
		HWND wnd = GetHWnd();
		int key;
		key = MessageBox(wnd, "�ҷ����֣�", "ѡ���Ⱥ���", MB_YESNO | MB_ICONQUESTION);
		if (key == IDYES)	play_b();
		else				play_w();
	} while(ask());
	closegraph();
	FreeConsole();
	return 0;
}