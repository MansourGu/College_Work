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

#define ROW_NUM			4		// 行数
#define COL_NUM			4		// 列数
#define GOLD_NUM		1		// 金子数
#define CAVE_NUM		2		// 陷阱数
#define WUMPUS_NUM		1		// 怪兽数
#define FLAG_NUM		12		// 标记向量的比特位数量

#define CURRENT			2		// 当前点
#define SAFE			4		// 安全
#define VISITED			8		// 已访问
#define GLITTER			16		// 发光
#define STENCH			32		// 臭气
#define BREEZE			64		// 微风
#define GOLD_SUSPECT	128		// 怀疑有金子
#define CAVE_SUSPECT	256		// 怀疑有陷阱
#define WUMPUS_SUSPECT	512		// 怀疑有怪兽
#define GOLD			1024		// 金子
#define CAVE			2048	// 陷阱
#define WUMPUS			4096	// 怪兽

#define GOLD_VALUE		1000	// 金子价值
#define WUMPUS_COST		10		// 怪兽消耗
#define DEATH_COST		1000	// 死亡消耗
#define STEP_COST		1		// 行动消耗

#define Point pair<int, int>	// pair存储点坐标
#define xx first				// x坐标
#define yy second				// y坐标

int real_world[ROW_NUM][COL_NUM];	// 真实世界
int agent_world[ROW_NUM][COL_NUM];	// 代理世界

Point cave_position[CAVE_NUM];		// 陷阱坐标
Point wumpus_position[WUMPUS_NUM];	// 怪兽坐标
Point gold_position[GOLD_NUM];		// 金子坐标

Point path_record[100];			// 路径记录
Point start;	// 起始点坐标

bool find_gold;	// 是否找到金子
bool game_over;	// 是否游戏结束
int score = 1000;		// 当前分数
int step_cnt;   // 步数
int RandInt(int l, int r, vector<int> except)
{
	int result = 0;
	do {
		result = rand() % (r - l + 1) + l;	// 随机数生成
	} while (std::find(except.begin(), except.end(), result) != except.end());

	return result;
}
Point RandPoint(Point l, Point r, vector<Point> except)
{
	Point result;
	do {
		result.xx = RandInt(l.xx, r.xx, vector<int>{});	// x坐标
		result.yy = RandInt(l.yy, r.yy, vector<int>{});	// y坐标
	} while (std::find(except.begin(), except.end(), result) != except.end());
	return result;
}
void PutFlag(int world[ROW_NUM][COL_NUM], Point pos, int flag)
{
	// 如果已访问则其他的传感器标志置零
	if (pos.xx < 0 || pos.xx >= ROW_NUM || pos.yy < 0 || pos.yy >= COL_NUM) {
		return;
	}
	if (flag == VISITED) {
		world[pos.xx][pos.yy] &= ~SAFE;
		world[pos.xx][pos.yy] &= ~CAVE_SUSPECT;
		world[pos.xx][pos.yy] &= ~GOLD_SUSPECT;
		world[pos.xx][pos.yy] &= ~WUMPUS_SUSPECT;
	}
	world[pos.xx][pos.yy] |= flag;	// 放标记
}
void GetNeighborPosition(Point pos, vector<Point> &neighbor)
{
	int Next[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };// 上，下，左，右
	for (int i = 0; i < 4; ++i) {
		int next_x = pos.xx + Next[i][0];	// 邻居点x坐标
		int next_y = pos.yy + Next[i][1];	// 邻居点y坐标
		if (next_x >= 0 && next_x < ROW_NUM && next_y >= 0 && next_y < COL_NUM) {// 边界检查
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
		if ((agent_world[nx][ny] & SAFE) == 0 && (agent_world[nx][ny] & VISITED) == 0) {	   // 不安全且未被访问
			if ((agent_world[curx][cury] & BREEZE) == BREEZE) {	// 有微风
				if ((agent_world[nx][ny] & CAVE_SUSPECT) == CAVE_SUSPECT) {
					PutFlag(agent_world, neighbors[i], CAVE);
				}
				else {
					PutFlag(agent_world, neighbors[i], CAVE_SUSPECT);
				}
			}

			if ((agent_world[curx][cury] & STENCH) == STENCH) {	// 有臭气
				if ((agent_world[nx][ny] & WUMPUS_SUSPECT) == WUMPUS_SUSPECT) {
					PutFlag(agent_world, neighbors[i], WUMPUS);
				}
				else {
					PutFlag(agent_world, neighbors[i], WUMPUS_SUSPECT);
				}
			}

			if ((agent_world[curx][cury] & GLITTER) == GLITTER) {	//有闪光
				if ((agent_world[nx][ny] & GOLD_SUSPECT) == GOLD_SUSPECT) {
					PutFlag(agent_world, neighbors[i], GOLD);
				}
				else {
					PutFlag(agent_world, neighbors[i], GOLD_SUSPECT);
				}
			}

			if (((agent_world[curx][cury] & BREEZE) == 0) && ((agent_world[curx][cury] & STENCH) == 0)) {	 // 没有微风和臭气则安全
				PutFlag(agent_world, neighbors[i], SAFE);
				// 删除其他非必要标记
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
	// 上下左右四个方向
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
	bool vis[ROW_NUM][COL_NUM];	// 遍历标记
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
			int dx = cur.xx + Next[i][0];   // 下一个点的坐标
			int dy = cur.yy + Next[i][1];
			if (dx >= 0 && dx < ROW_NUM && dy >= 0 && dy < COL_NUM && ((agent_world[dx][dy] & VISITED) == VISITED) && vis[dx][dy] == false) {
				if (record == true)	// 需要记录路径
					bfs_path[Point{ dx,dy }] = cur;
				vis[dx][dy] = true;
				Q.push({ dx, dy });
			}
		}
	}
	if (record == true) {   // 需要记录则根据搜索路径找到搜索结果
		GetBfsPath(tar, src, tar, bfs_path);
	}
	if (flag) agent_world[tar.xx][tar.yy] &= ~VISITED;// 取消访问标记
	return steps;   // 返回最短路径长度
}
void Dfs(Point current)
{
	vector<Point> neighbors;
	path_record[step_cnt++] = current;
	agent_world[current.xx][current.yy] |= real_world[current.xx][current.yy];	// 获取当前点信息
	if ((agent_world[current.xx][current.yy] & GOLD) == GOLD) {	//如果遇到了金子
		find_gold = true;
		return;
	}
	if ((agent_world[current.xx][current.yy] & CAVE) == CAVE) {	// 掉进了洞穴
		game_over = true;
		return;
	}
	PutFlag(agent_world, current, VISITED);	// 当前点已访问
	UpdateNeighborsInformation(current);	// 更新周围点的信息
	agent_world[current.xx][current.yy] &= ~CURRENT;	// 不在当前点

	int Next[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };// 上，下，左，右
	for (int i = 0; i < 4; ++i) {
		int next_x = current.xx + Next[i][0];	// 邻居点x坐标
		int next_y = current.yy + Next[i][1];	// 邻居点y坐标
		if (next_x >= 0 && next_x < ROW_NUM && next_y >= 0 && next_y < COL_NUM) {// 边界检查
			neighbors.push_back({ next_x, next_y });
		}
	}
	for (int i = 0; i < neighbors.size(); ++i) {	// 周围可能有金子
		if ((agent_world[neighbors[i].xx][neighbors[i].yy] & GOLD) == GOLD) {
			PutFlag(agent_world, neighbors[i], CURRENT);
			Dfs(neighbors[i]);	// 下一步
			if (find_gold || game_over) return;
		}
	}
	// 周围没有金子
	if (find_gold == false) {
		vector<Point> safe_place;
		for (int i = 0; i < neighbors.size(); ++i) {
			if (((agent_world[neighbors[i].xx][neighbors[i].yy] & SAFE) == SAFE)		// 安全
				&& ((agent_world[neighbors[i].xx][neighbors[i].yy] & VISITED) == 0)) { // 未访问
				safe_place.push_back(neighbors[i]);
			}
		}
		if (safe_place.size() > 0) {	// 存在安全区域
			int rand_next_pos = rand() % safe_place.size();	// 随机选择一个安全区域
			PutFlag(agent_world, safe_place[rand_next_pos], CURRENT);
			Dfs(safe_place[rand_next_pos]);	// 下一步
			if (find_gold || game_over) return;
		}
		else {		// 没有安全区域，寻找最近的安全地带
			Point nearest_safe_pos = { -1, -1 };	// 最近的安全点初始化
			for (int i = 0; i < ROW_NUM; ++i) {
				for (int j = 0; j < COL_NUM; ++j) {
					if ((agent_world[i][j] & SAFE) == SAFE) {
						if (nearest_safe_pos == Point{ -1, -1 })	// 第一个安全的点
							nearest_safe_pos = { i, j };
						else {
							int dismin = Bfs(current, nearest_safe_pos, false); // 最近安全点距离
							int discur = Bfs(current, Point{ i, j }, false);	// 当前安全点距离
							if (discur < dismin) {	// 当前安全点更近
								nearest_safe_pos = { i, j };	// 更新最近安全点
							}
						}
					}
				}
			}
			// 机器人地图上有安全点
			if (nearest_safe_pos != Point{ -1, -1 }) {
				PutFlag(agent_world, nearest_safe_pos, CURRENT);
				Bfs(current, nearest_safe_pos, true);	// 记录行动路线
				Dfs(nearest_safe_pos);	// 下一步
				if (find_gold || game_over) return;
			}
			else {	// 没有安全点，选择一个相对安全的地点
				vector<Point> good_neighbor;
				for (int i = 0; i < neighbors.size(); ++i) {
					if (((agent_world[neighbors[i].xx][neighbors[i].yy] & VISITED) == 0)	// 未被访问
						&& ((agent_world[neighbors[i].xx][neighbors[i].yy] & CAVE) == 0)	// 没有陷阱
						&& ((agent_world[neighbors[i].xx][neighbors[i].yy] & WUMPUS) == 0)) // 没有怪兽
						good_neighbor.push_back(neighbors[i]);
				}

				if (good_neighbor.size() > 0) {	// 有相对安全的点
					int rand_next_goodpos = rand() % (good_neighbor.size());	// 随机选取一个相对安全的点
					Dfs(good_neighbor[rand_next_goodpos]);	// 下一步
					if (find_gold || game_over) return;
				}
				else {	// 没有相对安全的点，选择杀死怪兽
					vector<Point> kill_pos, cave_pos;
					for (int i = 0; i < neighbors.size(); ++i) {
						if ((agent_world[neighbors[i].xx][neighbors[i].yy] & VISITED) == 0) // 未被访问过
							if ((agent_world[neighbors[i].xx][neighbors[i].yy] & WUMPUS) == WUMPUS) {	// 是怪兽
								kill_pos.push_back(neighbors[i]);
							}
							else {
								cave_pos.push_back(neighbors[i]);
							}
					}
					if (kill_pos.size() > 0) {	// 存在怪兽则杀死怪兽
						int kill_wumpus = rand() % kill_pos.size();
						vector<Point> wumpus_neighbors;
						GetNeighborPosition(kill_pos[kill_wumpus], wumpus_neighbors);
						agent_world[kill_pos[kill_wumpus].xx][kill_pos[kill_wumpus].yy] &= ~WUMPUS;// 取消怪兽标记
						// 将杀死的怪兽周围的臭气标记取消
						for (int i = 0; i < wumpus_neighbors.size(); ++i) {
							agent_world[wumpus_neighbors[i].xx][wumpus_neighbors[i].yy] &= ~STENCH;
						}
						PutFlag(agent_world, kill_pos[kill_wumpus], CURRENT);
						Dfs(kill_pos[kill_wumpus]);	// 下一步
						if (find_gold || game_over) return;
					}
					else if (cave_pos.size()) {	// 没有怪兽只有陷阱
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
	/* ==================== WumpusWorld初始化 ================== */
	start.xx = 0, start.yy = 0;	// 起始点(0, 0)
	vector<Point> except;		// 非法访问点
	except.push_back(start);	// 将起始点不可再访问
	Point l{ 1, 1 }, r{ ROW_NUM - 1, COL_NUM - 1 };	// 边界点
	find_gold = false;
	game_over = false;
	step_cnt = 0;

	for (int i = 0; i < ROW_NUM; ++i) {
		for (int j = 0; j < COL_NUM; ++j) {
			real_world[i][j] = 0;
			agent_world[i][j] = 0;
		}
	}

	// 生成陷阱位置
	for (int i = 0; i < CAVE_NUM; ++i) {
		cave_position[i] = RandPoint(l, r, except);
		except.push_back(cave_position[i]);
	}

	// 生成怪兽位置
	for (int i = 0; i < WUMPUS_NUM; ++i) {
		wumpus_position[i] = RandPoint(l, r, except);
		except.push_back(wumpus_position[i]);
	}

	// 生成金子位置
	for (int i = 0; i < CAVE_NUM; ++i) {
		gold_position[i] = RandPoint(l, r, except);
		except.push_back(gold_position[i]);
	}

	vector<Point> neighbor;	// 当前点的邻居坐标
	// 生成世界
	for (int i = 0; i < ROW_NUM; ++i) {
		for (int j = 0; j < COL_NUM; ++j) {
			// 陷阱检查
			for (int k = 0; k < CAVE_NUM; ++k) {
				if (i == cave_position[k].xx && cave_position[k].yy == j) {
					PutFlag(real_world, cave_position[k], CAVE);	// 放陷阱
					GetNeighborPosition(cave_position[k], neighbor);// 获取邻居坐标
					while (!neighbor.empty()) {	// 陷阱的邻居点都打上微风标记
						PutFlag(real_world, neighbor[neighbor.size() - 1], BREEZE);
						neighbor.pop_back();
					}
				}
			}

			// 怪兽检查
			for (int k = 0; k < WUMPUS_NUM; ++k) {
				if (i == wumpus_position[k].xx && j == wumpus_position[k].yy) {
					PutFlag(real_world, wumpus_position[k], WUMPUS);  // 放怪兽
					GetNeighborPosition(wumpus_position[k], neighbor);// 获取邻居坐标
					while (!neighbor.empty()) {	// 怪兽的邻居点都打上臭气标记
						PutFlag(real_world, neighbor[neighbor.size() - 1], STENCH);
						neighbor.pop_back();
					}
				}
			}

			// 金子检查
			for (int k = 0; k < GOLD_NUM; ++k) {
				if (i == gold_position[k].xx && j == gold_position[k].yy) {
					PutFlag(real_world, gold_position[k], GOLD);	// 放金子
					GetNeighborPosition(gold_position[k], neighbor);// 获取邻居坐标
					while (!neighbor.empty()) {
						PutFlag(real_world, neighbor[neighbor.size() - 1], GLITTER);
						neighbor.pop_back();
					}
				}
			}
		}
	}
	/* =============== 程序输出界面显示生成的世界 ================= */

	for (int i = 0; i < CAVE_NUM; ++i) cout << i + 1 <<" cave corrd: ( " << cave_position[i].xx + 1<<" , "<< cave_position[i].yy + 1<<" )" <<endl;
	for (int i = 0; i < WUMPUS_NUM; ++i) cout << i + 1 <<" wumpus corrd: ( "<< wumpus_position[i].xx+1<< " , " << wumpus_position[i].yy+1 << " )" <<endl;
	for (int i = 0; i < GOLD_NUM; ++i) cout << i + 1 <<" gold corrd: ( "<< gold_position[i].xx+1 << " , " << gold_position[i].yy+1 << " )" <<endl;

	// 显示世界
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