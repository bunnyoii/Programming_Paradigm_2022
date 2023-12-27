#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 12	//���̴�С
#define EMPTY 0			//��λ��Ϊ��
#define BLACK 1			//��λ��Ϊ����
#define WHITE 2			//��λ��Ϊ����
#define MAX_DEPTH 5		//�������

typedef int BOOL;
#define TRUE 1
#define FALSE 0

/* AB��ʼֵ */
const int maxLeaf = 100000000;
const int minLeaf = -100000000;
/* ��¼������� */
#define FIVE_IN_A_ROW 1000000
#define LIVE_FOUR 10000
#define SLEEP_FOUR 1000
#define LIVE_THREE 1000
#define SLEEP_THREE 100
#define LIVE_TWO 100
#define SLEEP_TWO 10
#define LIVE_ONE 10

#define START "START"	//��ʼ�Ծ�
#define PLACE "PLACE"	//ƽ̨��������
#define TURN "TURN"		//���Գ����������
#define END "END"		//������Ϸ
/* ��¼����̨������λ�� */
struct Command {
	int x;
	int y;
};

int board[BOARD_SIZE][BOARD_SIZE] = { 0 };		//����
int calScore[5] = { 0 };						//�Ʒ�����
int myFlag;										//�洢�ҷ���������(B/W)
int enemyFlag;									//�洢�з���������(B/W)
Command mycmd;									//�洢�ҷ��ж�λ��
Command enemycmd;								//�洢�з��ж�λ��
// �����������ϣ��£����ң����ϣ����ϣ����£����£�
const int direction[8][2] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1},
	{-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};


/****************������������****************/
int evaluatePosition(int flag, int row, int col);
int AlphaBeta(int depth, int flag, int alpha, int beta);
int checkLine(int flag, int row, int col, int deltaRow, int deltaCol);
int evaluate();
void printBoard(void);
bool checkSurroundings(int row, int col);
/*********����Ϊ������������ʵ���߼�*********/

/* ��ʼ��AI�����ö����������� */
void initAI(int me) { enemyFlag = 3 - me; }

/* ��������Ƿ��������� */
BOOL isInBound(int x, int y) { return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE); }

/*
* �������ƣ�start
* �������ܣ���ʼ��ֲ����г�ʼ�����������̵���պͷ�����ʼ���ĸ�����
* �������룺int flag
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
* �������ƣ�place
* �������ܣ��з���������
* �������룺Command cmd	-	����̨λ��
*/
void place(struct Command cmd) { board[cmd.y][cmd.x] = enemyFlag; }

/* �ҷ�(����AI)�������� */
void turn()
{
	if (board[4][4] == EMPTY && myFlag == BLACK) {
		mycmd.y = 4;
		mycmd.x = 4;
	}
	else {
		int value = AlphaBeta(MAX_DEPTH, myFlag, minLeaf, maxLeaf);
	}
	//�����·����ѡ����ɱ��Ӧ���������������һ����λ��
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

/* ���������˳� */
void end(int x) { exit(0); }

/* ��ʼִ�г��� */
void loop()
{
	int status;
	char tag[10] = { 0 };	//�洢״ָ̬��
	while (true) {
		memset(tag, 0, sizeof(tag));
		scanf("%s", tag);	//����״ָ̬��
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
/*******����Ϊ������AI��ս��������ʵ���߼�*******/

/* ��ֵ����
*  ��ˮƽ����ֱ��˫�Խ��߷�����й�ֵ
*  ������������ķ������
*  ���ظ���������(evaluate����
*/
// ��������
int evaluatePosition(int flag, int row, int col) {
	int score = 0;
	// ���ĸ������������
	for (int i = 0; i < 8; i += 2) {
		score += checkLine(flag, row, col, direction[i][0], direction[i][1]);
	}
	return score;
}

// ����˸��������������������ͷ�յĶ˿���
int checkLine(int flag, int row, int col, int deltaRow, int deltaCol) {
	int r = row;
	int c = col;
	int count = 1; // ����������
	int block = 0; // ��յ�һ����
	int emptyCount = 0; // ��λ����

	// ������
	while (count < 5) {
		r += deltaRow;
		c += deltaCol;
		if (!isInBound(r, c)) {
			block++; // �߽�������ն�
			break;
		}
		if (board[r][c] == flag) {
			count++;
			emptyCount = 0; // ���ÿ�λ����
		}
		else {
			if (board[r][c] != EMPTY) {
				block++;
				break;
			}
			else {
				emptyCount++;
				if (emptyCount >= 2) break; // ����������λʱֹͣ����
			}
		}
	}
	r = row;
	c = col;
	emptyCount = 0; // ���ÿ�λ����

	// ������
	while (count < 5) {
		r -= deltaRow;
		c -= deltaCol;
		if (!isInBound(r, c)) {
			block++; // �߽�������ն�
			break;
		}
		if (board[r][c] == flag) {
			count++;
			emptyCount = 0; // ���ÿ�λ����
		}
		else {
			if (board[r][c] != EMPTY) {
				block++;
				break;
			}
			else {
				emptyCount++;
				if (emptyCount >= 2) break; // ����������λʱֹͣ����
			}
		}
	}
	int ratio = 1;
	if (flag == enemyFlag)
		ratio = 2;

	// ����count��block��������
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

// ����������
int evaluate()
{
	int myScore = 0;
	int enemyScore = 0;
	// �����������̣�����ÿ��λ��
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			if (board[row][col] == myFlag) {
				// ����ҵĹ�ֵ
				myScore += evaluatePosition(myFlag, row, col);
			}
			else if (board[row][col] == enemyFlag) {
				// �Զ��ֵĹ�ֵ
				enemyScore += evaluatePosition(enemyFlag, row, col);
			}
		}
	}
	return myScore - enemyScore;
}

/* Alpha-Beta��֦�㷨
*  Alpha : ��֪���ֵ����ʼ��Ϊ-100000000
*  Beta  : ��֪��Сֵ����ʼ��Ϊ100000000
*/
int AlphaBeta(int depth, int flag, int alpha, int beta) {
	if (depth == 0) {
		return evaluate();
	}
	int bestX = -1, bestY = -1;
	if (flag == myFlag) {//������
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				// Ѱ�ҿ�������ĵط�
				if (board[i][j] == EMPTY) {
					if (checkSurroundings(i, j)) {
						//��ִ������
						board[i][j] = myFlag;
						int val = AlphaBeta(depth - 1, enemyFlag, alpha, beta);  // ע���л���־��alpha��beta
						// ��������
						board[i][j] = EMPTY;
						if (val > alpha) {
							alpha = val;
							bestX = j;
							bestY = i;
						}
						if (beta <= alpha)
							break;  // beta��֦
					}
				}
			}
		}
		mycmd.x = bestX;  // �����������
		mycmd.y = bestY;
		return alpha;
	}
	else if (flag == enemyFlag) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				// Ѱ�ҿ�������ĵط�
				if (board[i][j] == EMPTY) {
					if (checkSurroundings(i, j)) {
						//��ִ������
						board[i][j] = enemyFlag;
						int val = AlphaBeta(depth - 1, myFlag, alpha, beta);
						// ��������
						board[i][j] = EMPTY;
						if (val < beta) {
							beta = val;
							bestX = j;
							bestY = i;
						}
						if (beta <= alpha)
							break;  //alpha��֦
					}
				}
			}
		}
		return beta;  // ����betaֵ��Ϊ��ֵ
	}
	return 0;
}


//������
void printBoard(void)
{
	printf("     0  1  2  3  4  5  6  7  8  9 10 11\n");
	fflush(stdout);
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("   -------------------------------------\n%2d ", i);
		fflush(stdout);
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == WHITE) {
				printf("|��");
				fflush(stdout);
			}
			else if (board[i][j] == BLACK) {
				printf("|��");
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

//�ж���Χ�Ÿ����Ƿ������� �Ƿ���Ҫ����
bool checkSurroundings(int row, int col)
{
	for (int di = -1; di <= 1; di++) {
		for (int dj = -1; dj <= 1; dj++) {
			// ����(row, col)����
			if (di == 0 && dj == 0) {
				continue;
			}
			int new_i = row + di;
			int new_j = col + dj;
			// ���߽�����
			if (new_i >= 0 && new_i < BOARD_SIZE && new_j >= 0 && new_j < BOARD_SIZE) {
				// �����Χλ�������ӣ��򷵻�true
				if (board[new_i][new_j] != EMPTY) {
					return true;
				}
			}
		}
	}
	// ���������Χλ�ö���������û�����ӣ��򷵻�false
	return false;
}

int main(int argc, char* argv[])
{
	loop();
	return 0;
}