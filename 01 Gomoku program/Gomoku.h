#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 12	//棋盘大小
#define EMPTY 0			//该位置为空
#define BLACK 1			//该位置为黑子
#define WHITE 2			//该位置为白子
#define MIN_DEPTH 2

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define START "START"	//开始对局
#define PLACE "PLACE"	//平台放置棋子
#define TURN "TURN"		//大脑程序计算走子
#define END "END"		//结束游戏
/* 记录控制台五子棋位置 */
struct Command {
	int x;
	int y;
};

void debug(const char* str);

/* 初始化AI，设置对手棋子类型 */
void initAI(int me);

/* 检查棋子是否在棋盘内 */
BOOL isInBound(int x, int y);

/*
* 函数名称：start
* 函数功能：开始棋局并进行初始化，包括棋盘的清空和放置起始的四个棋子
* 函数输入：int flag
*/
void start(int flag);

/*
* 函数名称：place
* 函数功能：敌方放置棋子
* 函数输入：Command cmd	-	控制台位置
*/
void place(struct Command cmd);

/* 我方放置棋子 */
void turn();

/* 结束程序，退出 */
void end(int x);
/* 开始执行程序 */
void loop();

int calculateScore(int consecutiveCount, int emptyCount, int blocked);

// 在水平方向上评估分数并返回
int evaluateHorizontal(int flag, int row, int col);

// 在垂直方向上评估分数并返回
int evaluateVertical(int flag, int row, int col);

// 在左下到右上对角线方向上评估分数并返回
int evaluateDiagonal1(int flag, int row, int col);

// 在左上到右下对角线方向上评估分数并返回
int evaluateDiagonal2(int flag, int row, int col);

/* 对位置估值 */
int evaluatePosition(int flag, int row, int col);

/* 总评估函数 */
int evaluate();

/* Min-Max算法与Alpha-Beta剪枝算法 */
int MinMax(int depth, int flag, struct Command* cmd);
