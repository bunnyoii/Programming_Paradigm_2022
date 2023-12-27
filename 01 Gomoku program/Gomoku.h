#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 12	//���̴�С
#define EMPTY 0			//��λ��Ϊ��
#define BLACK 1			//��λ��Ϊ����
#define WHITE 2			//��λ��Ϊ����
#define MIN_DEPTH 2

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define START "START"	//��ʼ�Ծ�
#define PLACE "PLACE"	//ƽ̨��������
#define TURN "TURN"		//���Գ����������
#define END "END"		//������Ϸ
/* ��¼����̨������λ�� */
struct Command {
	int x;
	int y;
};

void debug(const char* str);

/* ��ʼ��AI�����ö����������� */
void initAI(int me);

/* ��������Ƿ��������� */
BOOL isInBound(int x, int y);

/*
* �������ƣ�start
* �������ܣ���ʼ��ֲ����г�ʼ�����������̵���պͷ�����ʼ���ĸ�����
* �������룺int flag
*/
void start(int flag);

/*
* �������ƣ�place
* �������ܣ��з���������
* �������룺Command cmd	-	����̨λ��
*/
void place(struct Command cmd);

/* �ҷ��������� */
void turn();

/* ���������˳� */
void end(int x);
/* ��ʼִ�г��� */
void loop();

int calculateScore(int consecutiveCount, int emptyCount, int blocked);

// ��ˮƽ��������������������
int evaluateHorizontal(int flag, int row, int col);

// �ڴ�ֱ��������������������
int evaluateVertical(int flag, int row, int col);

// �����µ����϶Խ��߷�������������������
int evaluateDiagonal1(int flag, int row, int col);

// �����ϵ����¶Խ��߷�������������������
int evaluateDiagonal2(int flag, int row, int col);

/* ��λ�ù�ֵ */
int evaluatePosition(int flag, int row, int col);

/* ���������� */
int evaluate();

/* Min-Max�㷨��Alpha-Beta��֦�㷨 */
int MinMax(int depth, int flag, struct Command* cmd);
