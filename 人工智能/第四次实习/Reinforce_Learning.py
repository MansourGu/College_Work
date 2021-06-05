import pandas as pd   #pandas数据库，主要用于分析结构化数据
import numpy as np    #numpy数据库，主要用于矩阵运算
import random         #random模块，主要用于随机数的生成
import time           #时间模块，用于时间的设置设置初始化环境

epsilon = 0.8  # 贪婪度 greedy，此实验算法中以epsilon概率进行贪婪决策，以(1-epsilon)进行随即决策。
alpha = 0.2    # 学习率：在强化学习中，学习率α越大,表示采用新的尝试得到的结果比例越大,保持旧的结果的比例越小。
gamma = 0.8  # 奖励递减值(折现率)：强化学习中，期望奖励会以奖励乘以奖励递减值的形式体现。
row = 4      #迷宫的行
column = 5   #迷宫的列
states = ['{}_{}'.format(i,j) for i in range(row) for j in range(column)]
# 状态集，分别对应4行5列的位置状态
actions = ['up','down','left','right']       # 动作集，分别对应上下左右四个动作

# 奖励集。智能体到达宝藏所在位置奖励+1，智能体到达陷阱所在位置奖励-1，其他位置奖励皆为0
rewards = np.array([[0,  0,  0, 0,  0],
                    [0, -1,  0, 0, -1],
                    [0,  0, -1, 0,  0],
                    [0,  0,  0, 0,  1]])

# 创建Q-table，初始Q-value皆为0
q_table = pd.DataFrame(data=[[0 for _ in actions] for _ in states],
                       index=states, columns=actions)
q_table


def replace_char(string, char, index):
    '''状态更新，替换指定迷宫字符显示智能体位置'''

    string = list(string)
    string[index] = char
    return ''.join(string)


def update_maze(state_x, state_y):
    '''更新迷宫，并打印'''

    env = ['------', '-P---P', '--P---', '-----T']  # 环境
    env[state_x] = replace_char(env[state_x], 'o', state_y)
    # 将智能体显示，用"o"表示智能体所在的位置
    envs = ''
    for i in range(len(env)):
        envs = envs + env[i] + '\n'
    print('\r{}'.format(''.join(envs)))
    time.sleep(0.1)

def get_next_state(state_x, state_y, action):
    '''执行动作后，转移到下一状态'''

    if action == 'right' and state_y != column - 1: # 除非最后一个状态（位置），向右就+1
        next_state_x = state_x
        next_state_y = state_y + 1
    elif action == 'left' and state_y != 0:         # 除非最前一个状态（位置），向左就-1
        next_state_x = state_x
        next_state_y = state_y - 1
    elif action == 'up' and state_x != 0:          # 除非最上一个状态（位置），向上就-1
        next_state_x = state_x - 1
        next_state_y = state_y
    elif action == 'down' and state_x != row - 1: # 除非最下一个状态（位置），向下就+1
        next_state_x = state_x + 1
        next_state_y = state_y
    else:
        next_state_x = state_x
        next_state_y = state_y
    return next_state_x, next_state_y


def get_valid_actions(state_x, state_y):
    '''取当前状态下的合法动作集合，与reward无关！'''

    global actions  # ['up','down','left','right']

    valid_actions = set(actions)
    if state_y == column - 1:  # 最后一个状态（位置），则不能向右
        valid_actions -= set(['right'])
    if state_y == 0:  # 最前一个状态（位置），则不能向左
        valid_actions -= set(['left'])
    if state_x == row - 1:  # 最下一个状态（位置），则不能向下
        valid_actions -= set(['down'])
    if state_x == 0:  # 最上一个状态（位置），则不能向上
        valid_actions -= set(['up'])

    return list(valid_actions)


def q_learning(num):
    for i in range(num):
        current_state_x = 0
        current_state_y = 0

        # 绘制初始状态
        update_maze(current_state_x, current_state_y)
        total_steps = 0

        # 我们限制了智能体不能闯出迷宫，所以可以视为这是一个True循环,只要不到终点，就继续探索
        while (current_state_x != row - 1) or (current_state_y != column - 1):
            # 0.2的概率随机选择策略或是q_table中所有迭代值(reward)都为0，随机选择action
            if (random.uniform(0, 1) > epsilon) or (
            (q_table.loc['{}_{}'.format(current_state_x, current_state_y)] == 0).all()):  # 探索
                current_action = random.choice(get_valid_actions(current_state_x, current_state_y))
            else:
                current_action = q_table.loc['{}_{}'.format(current_state_x, current_state_y)].idxmax()  # bellman方程
                print(q_table.loc[
                          '{}_{}'.format(current_state_x, current_state_y)].idxmax())  # 利用贪婪，选择q_table里面值最大的action
            next_state_x, next_state_y = get_next_state(current_state_x, current_state_y, current_action)
            next_state_q_values = q_table.loc[
                '{}_{}'.format(next_state_x, next_state_y), get_valid_actions(next_state_x, next_state_y)]
            # 使用时序差分法(TD法)计算两者误差，然后更新，类似于监督学习中的梯度下降
            q_table.loc['{}_{}'.format(current_state_x, current_state_y), current_action] += alpha * (
                    rewards[next_state_x, next_state_y] + gamma * next_state_q_values.max() - q_table.loc[
                '{}_{}'.format(current_state_x, current_state_y), current_action])

            # 更新最新坐标
            current_state_x = next_state_x
            current_state_y = next_state_y

            print(next_state_x, next_state_y)
            print(get_valid_actions(next_state_x, next_state_y))

            # 状态转移，
            update_maze(current_state_x, current_state_y)
            total_steps += 1

        print('\rEpisode {}: total_steps = {}'.format(i, total_steps))
        time.sleep(2)
        print('\r                                ')

    print('\nq_table:')
    print(q_table)
random.seed(456)
q_learning(10)
