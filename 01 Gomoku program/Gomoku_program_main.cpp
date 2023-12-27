#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 12	//棋盘大小
#define EMPTY 0			//该位置为空
#define BLACK 1			//该位置为黑子
#define WHITE 2			//该位置为白子
#define MAX_DEPTH 5		//搜索深度

typedef int BOOL;
#define TRUE 1
#define FALSE 0

/* AB初始值 */
const int maxLeaf = 100000000;
const int minLeaf = -100000000;
/* 记录给分情况 */
#define FIVE_IN_A_ROW 1000000
#define LIVE_FOUR 10000
#define SLEEP_FOUR 1000
#define LIVE_THREE 1000
#define SLEEP_THREE 100
#define LIVE_TWO 100
#define SLEEP_TWO 10
#define LIVE_ONE 10

#define START "START"	//开始对局
#define PLACE "PLACE"	//平台放置棋子
#define TURN "TURN"		//大脑程序计算走子
#define END "END"		//结束游戏
/* 记录控制台五子棋位置 */
struct Command {
	int x;
	int y;
};

int board[BOARD_SIZE][BOARD_SIZE] = { 0 };		//棋盘
int calScore[5] = { 0 };						//计分棋盘
int myFlag;										//存储我方棋子类型(B/W)
int enemyFlag;									//存储敌方棋子类型(B/W)
Command mycmd;									//存储我方行动位置
Command enemycmd;								//存储敌方行动位置
// 方向向量（上，下，左，右，左上，右上，左下，右下）
const int direction[8][2] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1},
	{-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};


/****************函数声明区域****************/
int evaluatePosition(int flag, int row, int col);
int AlphaBeta(int depth, int flag, int alpha, int beta);
int checkLine(int flag, int row, int col, int deltaRow, int deltaCol);
int evaluate();
void printBoard(void);
bool checkSurroundings(int row, int col);
/*********以下为五子棋程序基本实现逻辑*********/

/* 初始化AI，设置对手棋子类型 */
void initAI(int me) { enemyFlag = 3 - me; }

/* 检查棋子是否在棋盘内 */
BOOL isInBound(int x, int y) { return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE); }

/*
* 函数名称：start
* 函数功能：开始棋局并进行初始化，包括棋盘的清空和放置起始的四个棋子
* 函数输入：int flag
*/
void start(int flag)
{
	memset(board, 0, sizeof(board));
	int middlePlace = BOARD_SIZE / 2;
	board[middlePlace - 1][middlePlace - 1] = WHITE;
	board[middlePlace][middlePlace] = WHITE;
	board[middlePlace - 1][middlePlace] = BLACK;
	board[middlePlace][middlePlace - 1] = BLACK;
	initAI(flag);
}

/*
* 函数名称：place
* 函数功能：敌方放置棋子
* 函数输入：Command cmd	-	控制台位置
*/
void place(struct Command cmd) { board[cmd.y][cmd.x] = enemyFlag; }

/* 我方(大脑AI)放置棋子 */
void turn()
{
	if (board[4][4] == EMPTY && myFlag == BLACK) {
		mycmd.y = 4;
		mycmd.x = 4;
	}
	else {
		int value = AlphaBeta(MAX_DEPTH, myFlag, minLeaf, maxLeaf);
	}
	//如果无路可走选择自杀，应放置在棋盘内随机一个空位置
	if (mycmd.y == -1 || mycmd.x == -1) {
		while (1) {
			int x = rand() % 12;
			int y = rand() % 12;
			if (board[y][x] == EMPTY) {
				mycmd.y = y;
				mycmd.x = x;
				break;
			}
		}
	}
	printf("%d %d\n", mycmd.y, mycmd.x);
	fflush(stdout);
	board[mycmd.y][mycmd.x] = myFlag;
	//printBoard();
}

/* 结束程序，退出 */
void end(int x) { exit(0); }

/* 开始执行程序 */
void loop()
{
	int status;
	char tag[10] = { 0 };	//存储状态指令
	while (true) {
		memset(tag, 0, sizeof(tag));
		scanf("%s", tag);	//输入状态指令
		if (strcmp(tag, START) == 0) {
			scanf("%d", &myFlag);
			start(myFlag);
			printf("OK\n");
			fflush(stdout);
		}
		else if (strcmp(tag, PLACE) == 0)
		{
			scanf("%d %d", &enemycmd.y, &enemycmd.x);
			place(enemycmd);
		}
		else if (strcmp(tag, TURN) == 0)
		{
			turn();
		}
		else if (strcmp(tag, END) == 0)
		{
			scanf("%d", &status);
			end(status);
		}
	}
}
/*******以下为五子棋AI对战程序自我实现逻辑*******/

/* 估值函数
*  对水平、垂直、双对角线方向进行估值
*  将遍历结束后的分数相加
*  返回给评估函数(evaluate），
*/
// 评估函数
int evaluatePosition(int flag, int row, int col) {
	int score = 0;
	// 对四个方向进行评分
	for (int i = 0; i < 8; i += 2) {
		score += checkLine(flag, row, col, direction[i][0], direction[i][1]);
	}
	return score;
}

// 计算八个方向上连续的棋子数和封闭的端口数
int checkLine(int flag, int row, int col, int deltaRow, int deltaCol) {
	int r = row;
	int c = col;
	int count = 1; // 连续棋子数
	int block = 0; // 封闭的一端数
	int emptyCount = 0; // 空位计数

	// 正方向
	while (count < 5) {
		r += deltaRow;
		c += deltaCol;
		if (!isInBound(r, c)) {
			block++; // 边界算作封闭端
			break;
		}
		if (board[r][c] == flag) {
			count++;
			emptyCount = 0; // 重置空位计数
		}
		else {
			if (board[r][c] != EMPTY) {
				block++;
				break;
			}
			else {
				emptyCount++;
				if (emptyCount >= 2) break; // 连续两个空位时停止搜索
			}
		}
	}
	r = row;
	c = col;
	emptyCount = 0; // 重置空位计数

	// 反方向
	while (count < 5) {
		r -= deltaRow;
		c -= deltaCol;
		if (!isInBound(r, c)) {
			block++; // 边界算作封闭端
			break;
		}
		if (board[r][c] == flag) {
			count++;
			emptyCount = 0; // 重置空位计数
		}
		else {
			if (board[r][c] != EMPTY) {
				block++;
				break;
			}
			else {
				emptyCount++;
				if (emptyCount >= 2) break; // 连续两个空位时停止搜索
			}
		}
	}
	int ratio = 1;
	if (flag == enemyFlag)
		ratio = 2;

	// 根据count和block返回评分
	if (count >= 5) {
		return FIVE_IN_A_ROW * ratio;
	}
	else if (count == 4) {
		if (block == 0) return LIVE_FOUR * ratio;
		if (block == 1) return SLEEP_FOUR;
	}
	else if (count == 3) {
		if (block == 0) return LIVE_THREE * ratio;
		if (block == 1) return SLEEP_THREE;
	}
	else if (count == 2) {
		if (block == 0) return LIVE_TWO;
		if (block == 1) return SLEEP_TWO;
	}
	else if (count == 1)
	{
		if (block == 0) return LIVE_ONE;
	}
	return 0;
}

// 总评估函数
int evaluate()
{
	int myScore = 0;
	int enemyScore = 0;
	// 遍历整个棋盘，评估每个位置
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			if (board[row][col] == myFlag) {
				// 对玩家的估值
				myScore += evaluatePosition(myFlag, row, col);
			}
			else if (board[row][col] == enemyFlag) {
				// 对对手的估值
				enemyScore += evaluatePosition(enemyFlag, row, col);
			}
		}
	}
	return myScore - enemyScore;
}

/* Alpha-Beta剪枝算法
*  Alpha : 已知最大值，初始化为-100000000
*  Beta  : 已知最小值，初始化为100000000
*/
int AlphaBeta(int depth, int flag, int alpha, int beta) {
	if (depth == 0) {
		return evaluate();
	}
	int bestX = -1, bestY = -1;
	if (flag == myFlag) {//极大结点
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				// 寻找可以下棋的地方
				if (board[i][j] == EMPTY) {
					if (checkSurroundings(i, j)) {
						//试执行棋子
						board[i][j] = myFlag;
						int val = AlphaBeta(depth - 1, enemyFlag, alpha, beta);  // 注意切换标志和alpha、beta
						// 撤销棋子
						board[i][j] = EMPTY;
						if (val > alpha) {
							alpha = val;
							bestX = j;
							bestY = i;
						}
						if (beta <= alpha)
							break;  // beta剪枝
					}
				}
			}
		}
		mycmd.x = bestX;  // 更新最佳坐标
		mycmd.y = bestY;
		return alpha;
	}
	else if (flag == enemyFlag) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				// 寻找可以下棋的地方
				if (board[i][j] == EMPTY) {
					if (checkSurroundings(i, j)) {
						//试执行棋子
						board[i][j] = enemyFlag;
						int val = AlphaBeta(depth - 1, myFlag, alpha, beta);
						// 撤销棋子
						board[i][j] = EMPTY;
						if (val < beta) {
							beta = val;
							bestX = j;
							bestY = i;
						}
						if (beta <= alpha)
							break;  //alpha剪枝
					}
				}
			}
		}
		return beta;  // 返回beta值作为估值
	}
	return 0;
}


//画棋盘
void printBoard(void)
{
	printf("     0  1  2  3  4  5  6  7  8  9 10 11\n");
	fflush(stdout);
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("   -------------------------------------\n%2d ", i);
		fflush(stdout);
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == WHITE) {
				printf("|●");
				fflush(stdout);
			}
			else if (board[i][j] == BLACK) {
				printf("|○");
				fflush(stdout);
			}
			else {
				printf("|  ");
				fflush(stdout);
			}
		}
		printf("|\n");
		fflush(stdout);
	}
	printf("   -------------------------------------\n");
	fflush(stdout);
}

//判断周围九个点是否有棋子 是否需要搜索
bool checkSurroundings(int row, int col)
{
	for (int di = -1; di <= 1; di++) {
		for (int dj = -1; dj <= 1; dj++) {
			// 跳过(row, col)本身
			if (di == 0 && dj == 0) {
				continue;
			}
			int new_i = row + di;
			int new_j = col + dj;
			// 检查边界条件
			if (new_i >= 0 && new_i < BOARD_SIZE && new_j >= 0 && new_j < BOARD_SIZE) {
				// 如果周围位置有棋子，则返回true
				if (board[new_i][new_j] != EMPTY) {
					return true;
				}
			}
		}
	}
	// 如果所有周围位置都检查完毕且没有棋子，则返回false
	return false;
}

int main(int argc, char* argv[])
{
	loop();
	return 0;
}