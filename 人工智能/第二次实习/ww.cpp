#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <map>

using namespace std;

#define ROW_NUM			4		// ����
#define COL_NUM			4		// ����
#define GOLD_NUM		1		// ������
#define CAVE_NUM		2		// ������
#define WUMPUS_NUM		1		// ������
#define FLAG_NUM		12		// ��������ı���λ����

#define CURRENT			2		// ��ǰ��
#define SAFE			4		// ��ȫ
#define VISITED			8		// �ѷ���
#define GLITTER			16		// ����
#define STENCH			32		// ����
#define BREEZE			64		// ΢��
#define GOLD_SUSPECT	128		// �����н���
#define CAVE_SUSPECT	256		// ����������
#define WUMPUS_SUSPECT	512		// �����й���
#define GOLD			1024		// ����
#define CAVE			2048	// ����
#define WUMPUS			4096	// ����

#define GOLD_VALUE		1000	// ���Ӽ�ֵ
#define WUMPUS_COST		10		// ��������
#define DEATH_COST		1000	// ��������
#define STEP_COST		1		// �ж�����

#define Point pair<int, int>	// pair�洢������
#define xx first				// x����
#define yy second				// y����

int real_world[ROW_NUM][COL_NUM];	// ��ʵ����
int agent_world[ROW_NUM][COL_NUM];	// ��������

Point cave_position[CAVE_NUM];		// ��������
Point wumpus_position[WUMPUS_NUM];	// ��������
Point gold_position[GOLD_NUM];		// ��������

Point path_record[100];			// ·����¼
Point start;	// ��ʼ������

bool find_gold;	// �Ƿ��ҵ�����
bool game_over;	// �Ƿ���Ϸ����
int score = 1000;		// ��ǰ����
int step_cnt;   // ����
int RandInt(int l, int r, vector<int> except)
{
	int result = 0;
	do {
		result = rand() % (r - l + 1) + l;	// ���������
	} while (std::find(except.begin(), except.end(), result) != except.end());

	return result;
}
Point RandPoint(Point l, Point r, vector<Point> except)
{
	Point result;
	do {
		result.xx = RandInt(l.xx, r.xx, vector<int>{});	// x����
		result.yy = RandInt(l.yy, r.yy, vector<int>{});	// y����
	} while (std::find(except.begin(), except.end(), result) != except.end());
	return result;
}
void PutFlag(int world[ROW_NUM][COL_NUM], Point pos, int flag)
{
	// ����ѷ����������Ĵ�������־����
	if (pos.xx < 0 || pos.xx >= ROW_NUM || pos.yy < 0 || pos.yy >= COL_NUM) {
		return;
	}
	if (flag == VISITED) {
		world[pos.xx][pos.yy] &= ~SAFE;
		world[pos.xx][pos.yy] &= ~CAVE_SUSPECT;
		world[pos.xx][pos.yy] &= ~GOLD_SUSPECT;
		world[pos.xx][pos.yy] &= ~WUMPUS_SUSPECT;
	}
	world[pos.xx][pos.yy] |= flag;	// �ű��
}
void GetNeighborPosition(Point pos, vector<Point> &neighbor)
{
	int Next[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };// �ϣ��£�����
	for (int i = 0; i < 4; ++i) {
		int next_x = pos.xx + Next[i][0];	// �ھӵ�x����
		int next_y = pos.yy + Next[i][1];	// �ھӵ�y����
		if (next_x >= 0 && next_x < ROW_NUM && next_y >= 0 && next_y < COL_NUM) {// �߽���
			neighbor.push_back({ next_x, next_y });
		}
	}
}
void UpdateNeighborsInformation(Point current)
{
	vector<Point> neighbors;
	GetNeighborPosition(current, neighbors);
	int curx = current.xx, cury = current.yy;
	for (int i = 0; i < neighbors.size(); ++i) {
		int nx = neighbors[i].xx;
		int ny = neighbors[i].yy;
		if ((agent_world[nx][ny] & SAFE) == 0 && (agent_world[nx][ny] & VISITED) == 0) {	   // ����ȫ��δ������
			if ((agent_world[curx][cury] & BREEZE) == BREEZE) {	// ��΢��
				if ((agent_world[nx][ny] & CAVE_SUSPECT) == CAVE_SUSPECT) {
					PutFlag(agent_world, neighbors[i], CAVE);
				}
				else {
					PutFlag(agent_world, neighbors[i], CAVE_SUSPECT);
				}
			}

			if ((agent_world[curx][cury] & STENCH) == STENCH) {	// �г���
				if ((agent_world[nx][ny] & WUMPUS_SUSPECT) == WUMPUS_SUSPECT) {
					PutFlag(agent_world, neighbors[i], WUMPUS);
				}
				else {
					PutFlag(agent_world, neighbors[i], WUMPUS_SUSPECT);
				}
			}

			if ((agent_world[curx][cury] & GLITTER) == GLITTER) {	//������
				if ((agent_world[nx][ny] & GOLD_SUSPECT) == GOLD_SUSPECT) {
					PutFlag(agent_world, neighbors[i], GOLD);
				}
				else {
					PutFlag(agent_world, neighbors[i], GOLD_SUSPECT);
				}
			}

			if (((agent_world[curx][cury] & BREEZE) == 0) && ((agent_world[curx][cury] & STENCH) == 0)) {	 // û��΢��ͳ�����ȫ
				PutFlag(agent_world, neighbors[i], SAFE);
				// ɾ�������Ǳ�Ҫ���
				agent_world[nx][ny] &= ~CAVE_SUSPECT;
				agent_world[nx][ny] &= ~WUMPUS_SUSPECT;
				agent_world[nx][ny] &= ~CAVE;
				agent_world[nx][ny] &= ~WUMPUS;
			}
		}
	}
}
void GetBfsPath(Point cur, Point begPos, Point tar, map<Point, Point> bfs_path)
{
	if (cur == begPos) {
		return;
	}
	GetBfsPath(bfs_path[cur], begPos, tar, bfs_path);
	if (cur != tar) path_record[step_cnt++] = cur;
}
int Bfs(Point src, Point tar, bool record)
{
	// ���������ĸ�����
	int Next[4][2] = { {0, 1}, {0, -1}, {-1, 0},{1, 0} };
	int steps = 0;
	map<Point, Point> bfs_path;
	bool flag = false;
	if ((agent_world[tar.xx][tar.yy] & VISITED) == 0) {
		agent_world[tar.xx][tar.yy] |= VISITED;
		flag = true;
	}

	queue<Point> Q;
	Q.push(src);
	bool vis[ROW_NUM][COL_NUM];	// �������
	memset(vis, false, sizeof(vis));
	vis[src.xx][src.yy] = true;
	while (!Q.empty()) {
		Point cur = Q.front();
		Q.pop();
		++steps;
		if (cur == tar) {
			break;
		}
		for (int i = 0; i < 4; ++i) {
			int dx = cur.xx + Next[i][0];   // ��һ���������
			int dy = cur.yy + Next[i][1];
			if (dx >= 0 && dx < ROW_NUM && dy >= 0 && dy < COL_NUM && ((agent_world[dx][dy] & VISITED) == VISITED) && vis[dx][dy] == false) {
				if (record == true)	// ��Ҫ��¼·��
					bfs_path[Point{ dx,dy }] = cur;
				vis[dx][dy] = true;
				Q.push({ dx, dy });
			}
		}
	}
	if (record == true) {   // ��Ҫ��¼���������·���ҵ��������
		GetBfsPath(tar, src, tar, bfs_path);
	}
	if (flag) agent_world[tar.xx][tar.yy] &= ~VISITED;// ȡ�����ʱ��
	return steps;   // �������·������
}
void Dfs(Point current)
{
	vector<Point> neighbors;
	path_record[step_cnt++] = current;
	agent_world[current.xx][current.yy] |= real_world[current.xx][current.yy];	// ��ȡ��ǰ����Ϣ
	if ((agent_world[current.xx][current.yy] & GOLD) == GOLD) {	//��������˽���
		find_gold = true;
		return;
	}
	if ((agent_world[current.xx][current.yy] & CAVE) == CAVE) {	// �����˶�Ѩ
		game_over = true;
		return;
	}
	PutFlag(agent_world, current, VISITED);	// ��ǰ���ѷ���
	UpdateNeighborsInformation(current);	// ������Χ�����Ϣ
	agent_world[current.xx][current.yy] &= ~CURRENT;	// ���ڵ�ǰ��

	int Next[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };// �ϣ��£�����
	for (int i = 0; i < 4; ++i) {
		int next_x = current.xx + Next[i][0];	// �ھӵ�x����
		int next_y = current.yy + Next[i][1];	// �ھӵ�y����
		if (next_x >= 0 && next_x < ROW_NUM && next_y >= 0 && next_y < COL_NUM) {// �߽���
			neighbors.push_back({ next_x, next_y });
		}
	}
	for (int i = 0; i < neighbors.size(); ++i) {	// ��Χ�����н���
		if ((agent_world[neighbors[i].xx][neighbors[i].yy] & GOLD) == GOLD) {
			PutFlag(agent_world, neighbors[i], CURRENT);
			Dfs(neighbors[i]);	// ��һ��
			if (find_gold || game_over) return;
		}
	}
	// ��Χû�н���
	if (find_gold == false) {
		vector<Point> safe_place;
		for (int i = 0; i < neighbors.size(); ++i) {
			if (((agent_world[neighbors[i].xx][neighbors[i].yy] & SAFE) == SAFE)		// ��ȫ
				&& ((agent_world[neighbors[i].xx][neighbors[i].yy] & VISITED) == 0)) { // δ����
				safe_place.push_back(neighbors[i]);
			}
		}
		if (safe_place.size() > 0) {	// ���ڰ�ȫ����
			int rand_next_pos = rand() % safe_place.size();	// ���ѡ��һ����ȫ����
			PutFlag(agent_world, safe_place[rand_next_pos], CURRENT);
			Dfs(safe_place[rand_next_pos]);	// ��һ��
			if (find_gold || game_over) return;
		}
		else {		// û�а�ȫ����Ѱ������İ�ȫ�ش�
			Point nearest_safe_pos = { -1, -1 };	// ����İ�ȫ���ʼ��
			for (int i = 0; i < ROW_NUM; ++i) {
				for (int j = 0; j < COL_NUM; ++j) {
					if ((agent_world[i][j] & SAFE) == SAFE) {
						if (nearest_safe_pos == Point{ -1, -1 })	// ��һ����ȫ�ĵ�
							nearest_safe_pos = { i, j };
						else {
							int dismin = Bfs(current, nearest_safe_pos, false); // �����ȫ�����
							int discur = Bfs(current, Point{ i, j }, false);	// ��ǰ��ȫ�����
							if (discur < dismin) {	// ��ǰ��ȫ�����
								nearest_safe_pos = { i, j };	// ���������ȫ��
							}
						}
					}
				}
			}
			// �����˵�ͼ���а�ȫ��
			if (nearest_safe_pos != Point{ -1, -1 }) {
				PutFlag(agent_world, nearest_safe_pos, CURRENT);
				Bfs(current, nearest_safe_pos, true);	// ��¼�ж�·��
				Dfs(nearest_safe_pos);	// ��һ��
				if (find_gold || game_over) return;
			}
			else {	// û�а�ȫ�㣬ѡ��һ����԰�ȫ�ĵص�
				vector<Point> good_neighbor;
				for (int i = 0; i < neighbors.size(); ++i) {
					if (((agent_world[neighbors[i].xx][neighbors[i].yy] & VISITED) == 0)	// δ������
						&& ((agent_world[neighbors[i].xx][neighbors[i].yy] & CAVE) == 0)	// û������
						&& ((agent_world[neighbors[i].xx][neighbors[i].yy] & WUMPUS) == 0)) // û�й���
						good_neighbor.push_back(neighbors[i]);
				}

				if (good_neighbor.size() > 0) {	// ����԰�ȫ�ĵ�
					int rand_next_goodpos = rand() % (good_neighbor.size());	// ���ѡȡһ����԰�ȫ�ĵ�
					Dfs(good_neighbor[rand_next_goodpos]);	// ��һ��
					if (find_gold || game_over) return;
				}
				else {	// û����԰�ȫ�ĵ㣬ѡ��ɱ������
					vector<Point> kill_pos, cave_pos;
					for (int i = 0; i < neighbors.size(); ++i) {
						if ((agent_world[neighbors[i].xx][neighbors[i].yy] & VISITED) == 0) // δ�����ʹ�
							if ((agent_world[neighbors[i].xx][neighbors[i].yy] & WUMPUS) == WUMPUS) {	// �ǹ���
								kill_pos.push_back(neighbors[i]);
							}
							else {
								cave_pos.push_back(neighbors[i]);
							}
					}
					if (kill_pos.size() > 0) {	// ���ڹ�����ɱ������
						int kill_wumpus = rand() % kill_pos.size();
						vector<Point> wumpus_neighbors;
						GetNeighborPosition(kill_pos[kill_wumpus], wumpus_neighbors);
						agent_world[kill_pos[kill_wumpus].xx][kill_pos[kill_wumpus].yy] &= ~WUMPUS;// ȡ�����ޱ��
						// ��ɱ���Ĺ�����Χ�ĳ������ȡ��
						for (int i = 0; i < wumpus_neighbors.size(); ++i) {
							agent_world[wumpus_neighbors[i].xx][wumpus_neighbors[i].yy] &= ~STENCH;
						}
						PutFlag(agent_world, kill_pos[kill_wumpus], CURRENT);
						Dfs(kill_pos[kill_wumpus]);	// ��һ��
						if (find_gold || game_over) return;
					}
					else if (cave_pos.size()) {	// û�й���ֻ������
						int jump_cave = rand() % cave_pos.size();
						PutFlag(agent_world, cave_pos[jump_cave], CURRENT);
						Dfs(cave_pos[jump_cave]);
					}
				}
			}
		}
	}
}
void CreatWorld()
{
	/* ==================== WumpusWorld��ʼ�� ================== */
	start.xx = 0, start.yy = 0;	// ��ʼ��(0, 0)
	vector<Point> except;		// �Ƿ����ʵ�
	except.push_back(start);	// ����ʼ�㲻���ٷ���
	Point l{ 1, 1 }, r{ ROW_NUM - 1, COL_NUM - 1 };	// �߽��
	find_gold = false;
	game_over = false;
	step_cnt = 0;

	for (int i = 0; i < ROW_NUM; ++i) {
		for (int j = 0; j < COL_NUM; ++j) {
			real_world[i][j] = 0;
			agent_world[i][j] = 0;
		}
	}

	// ��������λ��
	for (int i = 0; i < CAVE_NUM; ++i) {
		cave_position[i] = RandPoint(l, r, except);
		except.push_back(cave_position[i]);
	}

	// ���ɹ���λ��
	for (int i = 0; i < WUMPUS_NUM; ++i) {
		wumpus_position[i] = RandPoint(l, r, except);
		except.push_back(wumpus_position[i]);
	}

	// ���ɽ���λ��
	for (int i = 0; i < CAVE_NUM; ++i) {
		gold_position[i] = RandPoint(l, r, except);
		except.push_back(gold_position[i]);
	}

	vector<Point> neighbor;	// ��ǰ����ھ�����
	// ��������
	for (int i = 0; i < ROW_NUM; ++i) {
		for (int j = 0; j < COL_NUM; ++j) {
			// ������
			for (int k = 0; k < CAVE_NUM; ++k) {
				if (i == cave_position[k].xx && cave_position[k].yy == j) {
					PutFlag(real_world, cave_position[k], CAVE);	// ������
					GetNeighborPosition(cave_position[k], neighbor);// ��ȡ�ھ�����
					while (!neighbor.empty()) {	// ������ھӵ㶼����΢����
						PutFlag(real_world, neighbor[neighbor.size() - 1], BREEZE);
						neighbor.pop_back();
					}
				}
			}

			// ���޼��
			for (int k = 0; k < WUMPUS_NUM; ++k) {
				if (i == wumpus_position[k].xx && j == wumpus_position[k].yy) {
					PutFlag(real_world, wumpus_position[k], WUMPUS);  // �Ź���
					GetNeighborPosition(wumpus_position[k], neighbor);// ��ȡ�ھ�����
					while (!neighbor.empty()) {	// ���޵��ھӵ㶼���ϳ������
						PutFlag(real_world, neighbor[neighbor.size() - 1], STENCH);
						neighbor.pop_back();
					}
				}
			}

			// ���Ӽ��
			for (int k = 0; k < GOLD_NUM; ++k) {
				if (i == gold_position[k].xx && j == gold_position[k].yy) {
					PutFlag(real_world, gold_position[k], GOLD);	// �Ž���
					GetNeighborPosition(gold_position[k], neighbor);// ��ȡ�ھ�����
					while (!neighbor.empty()) {
						PutFlag(real_world, neighbor[neighbor.size() - 1], GLITTER);
						neighbor.pop_back();
					}
				}
			}
		}
	}
	/* =============== �������������ʾ���ɵ����� ================= */

	for (int i = 0; i < CAVE_NUM; ++i) cout << i + 1 <<" cave corrd: ( " << cave_position[i].xx + 1<<" , "<< cave_position[i].yy + 1<<" )" <<endl;
	for (int i = 0; i < WUMPUS_NUM; ++i) cout << i + 1 <<" wumpus corrd: ( "<< wumpus_position[i].xx+1<< " , " << wumpus_position[i].yy+1 << " )" <<endl;
	for (int i = 0; i < GOLD_NUM; ++i) cout << i + 1 <<" gold corrd: ( "<< gold_position[i].xx+1 << " , " << gold_position[i].yy+1 << " )" <<endl;

	// ��ʾ����
	for (int i = 0; i < ROW_NUM; ++i) {
		for (int j = 0; j < COL_NUM; ++j) {
			if ((real_world[i][j] & CAVE) == CAVE) printf("C ");
			else if ((real_world[i][j] & WUMPUS) == WUMPUS) printf("W ");
			else if ((real_world[i][j] & GOLD) == GOLD) printf("G ");
			else printf("O ");
		}
		printf("\n");
	}
}
void ShowPath()
{
	Dfs(start);
	int count =0;
	if (find_gold) {
		Bfs(gold_position[0], start, true);
		path_record[step_cnt++] = start;
	}
	for (int i = 0; i < step_cnt; ++i) 
	{
		if (i != step_cnt ) {
			
			score -= STEP_COST;
			if ((real_world[path_record[i].xx][path_record[i].yy] & WUMPUS) == WUMPUS) {  // 
				score -= WUMPUS_COST;
				cout << "kill wumpus"<<endl;
			}
			else if ((real_world[path_record[i].xx][path_record[i].yy] & GOLD) == GOLD) { // 
				score += GOLD_VALUE;
				cout << " ( " << path_record[i].xx + 1 << " , " << path_record[i].yy + 1 << " ) ";
				cout << "  find gold  score: " << score << endl;
				break;
			}
			if ((real_world[path_record[i].xx][path_record[i].yy] & CAVE) == CAVE) 
			{ // 
				score -= DEATH_COST;
				cout << " ( " << path_record[i].xx + 1 << " , " << path_record[i].yy + 1 << " ) "; cout << "  dead  ";
				cout << "  scores" << score << endl;
				break;
			}
		}
			cout << " ( " << path_record[i].xx + 1 << " , " << path_record[i].yy + 1 << " ) ";
			cout << "  scores"<<score << endl;
	}

	
}
int main()
{
	srand((unsigned int)time(0));
	CreatWorld();
	ShowPath();
	system("pause");
	return 0;
}