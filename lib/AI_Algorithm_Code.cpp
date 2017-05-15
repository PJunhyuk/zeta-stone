// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI �ڵ� �ۼ� ���]

1. char info[]�� �迭 �ȿ�					"TeamName:�ڽ��� ����,Department:�ڽ��� �Ҽ�"					������ �ۼ��մϴ�.
( ���� ) Teamname:�� Department:�� �� ���� �մϴ�.
"�ڽ��� ����", "�ڽ��� �Ҽ�"�� �����ؾ� �մϴ�.

2. �Ʒ��� myturn() �Լ� �ȿ� �ڽŸ��� AI �ڵ带 �ۼ��մϴ�.

3. AI ������ �׽�Ʈ �Ͻ� ���� "���� �˰����ȸ ��"�� ����մϴ�.

4. ���� �˰��� ��ȸ ���� �����ϱ⿡�� �ٵϵ��� ���� ��, �ڽ��� "����" �� �� �˰����� �߰��Ͽ� �׽�Ʈ �մϴ�.



[���� �� �Լ�]
myturn(int cnt) : �ڽ��� AI �ڵ带 �ۼ��ϴ� ���� �Լ� �Դϴ�.
int cnt (myturn()�Լ��� �Ķ����) : ���� �� �� �־��ϴ��� ���ϴ� ����, cnt�� 1�̸� ���� ���� ��  �� ����  �δ� ��Ȳ(�� ��), cnt�� 2�̸� �� ���� ���� �δ� ��Ȳ(�� ��)
int  x[0], y[0] : �ڽ��� �� ù �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
int  x[1], y[1] : �ڽ��� �� �� �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
void domymove(int x[], int y[], cnt) : �� ������ ��ǥ�� �����ؼ� ���


//int board[BOARD_SIZE][BOARD_SIZE]; �ٵ��� �����Ȳ ��� �־� �ٷλ�� ������. ��, ���������ͷ� ���� �������
// ������ ���� ��ġ�� �ٵϵ��� ������ �ǰ��� ó��.

boolean ifFree(int x, int y) : ���� [x,y]��ǥ�� �ٵϵ��� �ִ��� Ȯ���ϴ� �Լ� (������ true, ������ false)
int showBoard(int x, int y) : [x, y] ��ǥ�� ���� ���� �����ϴ��� �����ִ� �Լ� (1 = �ڽ��� ��, 2 = ����� ��, 3 = ��ŷ)


<-------AI�� �ۼ��Ͻ� ��, ���� �̸��� �Լ� �� ���� ����� �������� �ʽ��ϴ�----->
*/

#define BOARD_SIZE 20
const int myColor = 1, opColor = 2, bloColor = 3;

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

void getBoard();
bool check(int x, int y, int color);//(x,y) �����ϸ� 6�� �� �� �ֳ� üũ
bool checkV(int x, int y, int color);
bool checkH(int x, int y, int color);
bool checkD(int x, int y, int color);
bool checkD2(int x, int y, int color);

bool canWin(int color);
bool myisFree(int x, int y);

// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:����Ÿ,Department:�������б�" };

int myBoard[BOARD_SIZE][BOARD_SIZE];
int winx[2] = { 0 }, winy[2] = { 0 };

void myturn(int cnt) {
	getBoard();

	int x[2], y[2];

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	if (canWin(myColor)) {//�̹� �Ͽ� �̱� �� �ִٸ�
//		printf("win!!! (%d,%d), (%d,%d)", winx[0], winy[0], winx[1], winy[1]);//
		domymove(winx, winy, cnt);
		return;
	} else if (canWin(opColor)) {
		domymove(winx, winy, cnt);
		return;
	} else {
//		printf("�̹� �Ͽ� �̱� ����� ������");//
		for (int i = 0; i < cnt; i++) {
			do {
				x[i] = rand() % width;
				y[i] = rand() % height;
				if (terminateAI) return;
			} while (!isFree(x[i], y[i]));

			if (x[1] == x[0] && y[1] == y[0]) i--;
		}
	}

	/*
	for (int i = 0; i < cnt; i++) {
		do {
			x[i] = rand() % width;
			y[i] = rand() % height;
			if (terminateAI) return;
		} while (!isFree(x[i], y[i]));

		if (x[1] == x[0] && y[1] == y[0]) i--;
	}
	*/

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);
}

void getBoard() {
	for (int i = 0; i<width; ++i) {
		for (int j = 0; j<height; ++j) {
			myBoard[i][j] = showBoard(i, j);
		} // printf("\n");
	}
}

bool canWin(int color) {
	int x1, y1, x2, y2;
	for (int i = 0; i<width*height; ++i) {//�� �ϳ��� �̱� �� �ֳ� �˻�. �̱� �� ������ �װͰ� 0,0�� winx, winy�� ��. �̰� ������ �ɼ���..
		x1 = i / width; y1 = i%width;
		if (!myisFree(x1, y1)) continue;

		myBoard[x1][y1] = color;
		if (check(x1, y1, color)) {
			winx[0] = x1; winy[0] = y1;
			return true;
		}
		myBoard[x1][y1] = 0;
	}

	for (int i = 0; i<width*height; ++i) {//�� �ѷ� �̱� �� �ֳ� �˻�. ù°�� �ֺ� +-5���� ��° ���� ��.
		x1 = i / width; y1 = i%width;
		if (!myisFree(x1, y1)) continue;
		myBoard[x1][y1] = color;

		for (x2 = x1 - 5; x2 <= x1 + 5; ++x2) {//���� +-5 �α�
			y2 = y1;
			if (!myisFree(x2, y2)) continue;
			myBoard[x2][y2] = color;

			if (check(x2, y2, color)) {
				winx[0] = x1; winy[0] = y1; winx[1] = x2; winy[1] = y2;
				return true;
			}
			myBoard[x2][y2] = 0;
		}
		for (y2 = y1 - 5; y2 <= y1 + 5; ++y2) {//����
			x2 = x1;
			if (!myisFree(x2, y2)) continue;
			myBoard[x2][y2] = color;

			if (check(x2, y2, color)) {
				winx[0] = x1; winy[0] = y1; winx[1] = x2; winy[1] = y2;
				return true;
			}
			myBoard[x2][y2] = 0;
		}
		for (x2 = x1 - 5, y2 = y1 - 5; x2 <= x1 + 5; ++x2, ++y2) {//�ִ밢
			if (!myisFree(x2, y2)) continue;
			myBoard[x2][y2] = color;

			if (check(x2, y2, color)) {
				winx[0] = x1; winy[0] = y1; winx[1] = x2; winy[1] = y2;
				return true;
			}
			myBoard[x2][y2] = 0;
		}
		for (x2 = x1 - 5, y2 = y1 + 5; x2 <= x1 + 5; ++x2, --y2) {//�δ밢
			if (!myisFree(x2, y2)) continue;
			myBoard[x2][y2] = color;

			if (check(x2, y2, color)) {
				winx[0] = x1; winy[0] = y1; winx[1] = x2; winy[1] = y2;
				return true;
			}
			myBoard[x2][y2] = 0;
		}


		myBoard[x1][y1] = 0;
	}

	return false;
}

bool check(int x, int y, int color) {
	if (checkV(x, y, color)) return true;
	if (checkH(x, y, color)) return true;
	if (checkD(x, y, color)) return true;
	if (checkD2(x, y, color)) return true;

	return false;
}

bool checkV(int x, int y, int color) {
	int i = 0;
	int j = 0;

	int cnt = 0;//���ΰ˻�
	for (i = x; i >= 0; --i) {
		if (myBoard[i][y] == color)
			cnt++;
		else break;
	}
	for (i = x + 1; i<height; ++i) {
		if (myBoard[i][y] == color)
			cnt++;
		else break;
	}
	if (cnt == 6)
		return true;
	else
		return false;
}

bool checkH(int x, int y, int color) {
	int i = 0;
	int j = 0;

	int cnt = 0;//���ΰ˻�
	for (j = y; j >= 0; --j) {
		if (myBoard[x][j] == color)
			cnt++;
		else break;
	}
	for (j = y + 1; j<width; ++j) {
		if (myBoard[x][j] == color)
			cnt++;
		else break;
	}
	if (cnt == 6)
		return true;
	else
		return false;
}
bool checkD(int x, int y, int color) {
	int i, j;
	int cnt = 0;//�ִ밢�˻�
	for (i = x, j = y; i >= 0 && j >= 0; --i, --j) {
		if (myBoard[i][j] == color)
			cnt++;
		else break;
	}
	for (i = x + 1, j = y + 1; i<height&&j<width; ++i, ++j) {
		if (myBoard[i][j] == color)
			cnt++;
		else break;
	}
	if (cnt == 6)
		return true;
	else
		return false;
}
bool checkD2(int x, int y, int color) {
	int i, j;
	int cnt = 0;//�δ밢�˻�
	for (i = x, j = y; i >= 0 && j<width; --i, ++j) {
		if (myBoard[i][j] == color)
			cnt++;
		else break;
	}
	for (i = x + 1, j = y - 1; i<height&&j >= 0; ++i, --j) {
		if (myBoard[i][j] == color)
			cnt++;
		else break;
	}
	if (cnt == 6)
		return true;
	else
		return false;
}


bool myisFree(int x, int y) {//�� �Լ��� ���� ���� �ؾ���. myBoard�� �˻��ؼ� free���� ���� �Լ�.
	return x >= 0 && y >= 0 && x < width && y < height && myBoard[x][y] == 0;
}