// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI 코드 작성 방법]

1. char info[]의 배열 안에					"TeamName:자신의 팀명,Department:자신의 소속"					순서로 작성합니다.
( 주의 ) Teamname:과 Department:는 꼭 들어가야 합니다.
"자신의 팀명", "자신의 소속"을 수정해야 합니다.

2. 아래의 myturn() 함수 안에 자신만의 AI 코드를 작성합니다.

3. AI 파일을 테스트 하실 때는 "육목 알고리즘대회 툴"을 사용합니다.

4. 육목 알고리즘 대회 툴의 연습하기에서 바둑돌을 누른 후, 자신의 "팀명" 이 들어간 알고리즘을 추가하여 테스트 합니다.



[변수 및 함수]
myturn(int cnt) : 자신의 AI 코드를 작성하는 메인 함수 입니다.
int cnt (myturn()함수의 파라미터) : 돌을 몇 수 둬야하는지 정하는 변수, cnt가 1이면 육목 시작 시  한 번만  두는 상황(한 번), cnt가 2이면 그 이후 돌을 두는 상황(두 번)
int  x[0], y[0] : 자신이 둘 첫 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
int  x[1], y[1] : 자신이 둘 두 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
void domymove(int x[], int y[], cnt) : 둘 돌들의 좌표를 저장해서 출력


//int board[BOARD_SIZE][BOARD_SIZE]; 바둑판 현재상황 담고 있어 바로사용 가능함. 단, 원본데이터로 수정 절대금지
// 놓을수 없는 위치에 바둑돌을 놓으면 실격패 처리.

boolean ifFree(int x, int y) : 현재 [x,y]좌표에 바둑돌이 있는지 확인하는 함수 (없으면 true, 있으면 false)
int showBoard(int x, int y) : [x, y] 좌표에 무슨 돌이 존재하는지 보여주는 함수 (1 = 자신의 돌, 2 = 상대의 돌, 3 = 블럭킹)


<-------AI를 작성하실 때, 같은 이름의 함수 및 변수 사용을 권장하지 않습니다----->
*/

#define BOARD_SIZE 20
const int myColor = 1, opColor = 2, bloColor = 3;

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

void getBoard();
bool check(int x, int y, int color);//(x,y) 포함하며 6줄 된 거 있나 체크
bool checkV(int x, int y, int color);
bool checkH(int x, int y, int color);
bool checkD(int x, int y, int color);
bool checkD2(int x, int y, int color);

bool canWin(int color);
bool myisFree(int x, int y);

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:팀제타,Department:연세대학교" };

int myBoard[BOARD_SIZE][BOARD_SIZE];
int winx[2] = { 0 }, winy[2] = { 0 };

void myturn(int cnt) {
	getBoard();

	int x[2], y[2];

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	if (canWin(myColor)) {//이번 턴에 이길 수 있다면
//		printf("win!!! (%d,%d), (%d,%d)", winx[0], winy[0], winx[1], winy[1]);//
		domymove(winx, winy, cnt);
		return;
	} else if (canWin(opColor)) {
		domymove(winx, winy, cnt);
		return;
	} else {
//		printf("이번 턴에 이길 방법은 없군요");//
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

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
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
	for (int i = 0; i<width*height; ++i) {//돌 하나로 이길 수 있나 검사. 이길 수 있으면 그것과 0,0이 winx, winy가 됨. 이게 문제가 될수도..
		x1 = i / width; y1 = i%width;
		if (!myisFree(x1, y1)) continue;

		myBoard[x1][y1] = color;
		if (check(x1, y1, color)) {
			winx[0] = x1; winy[0] = y1;
			return true;
		}
		myBoard[x1][y1] = 0;
	}

	for (int i = 0; i<width*height; ++i) {//돌 둘로 이길 수 있나 검사. 첫째돌 주변 +-5에만 둘째 돌을 둠.
		x1 = i / width; y1 = i%width;
		if (!myisFree(x1, y1)) continue;
		myBoard[x1][y1] = color;

		for (x2 = x1 - 5; x2 <= x1 + 5; ++x2) {//세로 +-5 두기
			y2 = y1;
			if (!myisFree(x2, y2)) continue;
			myBoard[x2][y2] = color;

			if (check(x2, y2, color)) {
				winx[0] = x1; winy[0] = y1; winx[1] = x2; winy[1] = y2;
				return true;
			}
			myBoard[x2][y2] = 0;
		}
		for (y2 = y1 - 5; y2 <= y1 + 5; ++y2) {//가로
			x2 = x1;
			if (!myisFree(x2, y2)) continue;
			myBoard[x2][y2] = color;

			if (check(x2, y2, color)) {
				winx[0] = x1; winy[0] = y1; winx[1] = x2; winy[1] = y2;
				return true;
			}
			myBoard[x2][y2] = 0;
		}
		for (x2 = x1 - 5, y2 = y1 - 5; x2 <= x1 + 5; ++x2, ++y2) {//주대각
			if (!myisFree(x2, y2)) continue;
			myBoard[x2][y2] = color;

			if (check(x2, y2, color)) {
				winx[0] = x1; winy[0] = y1; winx[1] = x2; winy[1] = y2;
				return true;
			}
			myBoard[x2][y2] = 0;
		}
		for (x2 = x1 - 5, y2 = y1 + 5; x2 <= x1 + 5; ++x2, --y2) {//부대각
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

	int cnt = 0;//세로검사
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

	int cnt = 0;//가로검사
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
	int cnt = 0;//주대각검사
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
	int cnt = 0;//부대각검사
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


bool myisFree(int x, int y) {//이 함수로 새로 만들어서 해야함. myBoard를 검사해서 free한지 보는 함수.
	return x >= 0 && y >= 0 && x < width && y < height && myBoard[x][y] == 0;
}