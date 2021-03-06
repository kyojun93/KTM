// Tetris.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define TetrisSize_H 21
#define TetrisSize_W 12
// 1) 프로젝트 이름에 마우스를 위치시켜 놓은 후 마우스 우측 버튼을 클릭하세요.
// 2) 메뉴에서 속성을 클릭하신 후  링커를 클릭하고, 추가 종속성에 winmm.lib 파일을 
//    추가하세요.
// 3) winmm.lib 파일을 추가시켜 놓는 이유는 timeGetTime() 함수의 본체가 winmm.lib 파일에
//    있기 때문입니다.

#include <windows.h>

typedef struct TetrisPosition
{
	int x, y;
}POS;

// 배열이라는 것은 순차적으로 나열된 공간이라고 말씀드렸습니다.
// 구조체 배열 또한 순차적으로 나열된 공간이기에 아래와 같이 사용 가능합니다.
//POS pos[4] = { 10, 10, 20, 20, 30, 30, 40, 40 };
//POS pos2[4] = { {10, 10},{20, 20},{30, 30},{40,40} };




// 커서의 포지션 값을 이동
void CursorPos(int x, int y)
{
	COORD pos = { x,y };

	// SetConsoleCursorPosition은 콘솔창에서의 커서 위치를 설정하는 함수입니다.
	// SetConsoleCursorPosition 함수는 매개변수가 두 개이며,
	// 첫 번째 매개변수는 콘솔창의 핸들 값을 받으며, 두 번째 매개 변수로는 위치값을 받게 됩니다.
	// GetStdHandle() 함수가 표준 핸들 파일을 넘겨주는 함수이며,
	// STD_OUTPUT_HANDLE가 의미하는 바는 출력 핸들이라는 뜻이기에,
	// GetStdHandle(STD_OUTPUT_HANDLE)는 출력 핸들을 받아 오겠다는
	// 의미가 되게 됩니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorVisible(bool blnCursorVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = blnCursorVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

POS polygon[6][4][4] =
{
	// ▨
	// ▨▨▨ 도형
	{
		{ 0, 0, -1,  0,  1,  0,  1, -1 },
		{ 0, 0,  0, -1, -1, -1,  0,  1 },
		{ 0, 0, -1,  0,  1,  0, -1,  1 },
		{ 0, 0,  0, -1,  0,  1,  1,  1 }
	},

	// ▨▨▨▨ 도형
	{
		{ 0,-1,  0,  0,  0,  1,  0,  2 },
		{ -1, 0,  0,  0,  1,  0,  2,  0 },
		{ 0,-1,  0,  0,  0,  1,  0,  2 },
		{ -1, 0,  0,  0,  1,  0,  2,  0 },
	},
	//      ▨
	//	▨▨▨ 도형
	{
		{ -1,  0,  0,  0,  1,  0,  1,  -1 },
		{ 0, -1,  0,  0,  0,  1,  1,   1 },
		{ -1,  0,  0,  0,  1,  0, -1,   1 },
		{ -1, -1,  0, -1,  0,  0,  0,   1 },
	},

	// ▨▨
	// ▨▨ 도형
	{
		{ -1, -1,  0, -1,  -1,  0,  0,  0 },
		{ -1, -1,  0, -1,  -1,  0,  0,  0 },
		{ -1, -1,  0, -1,  -1,  0,  0,  0 },
		{ -1, -1,  0, -1,  -1,  0,  0,  0 },
	},

	// ▨
	// ▨▨ 
	//   ▨ 도형
	{
		{ -1, -1,  -1, 0,  0,   0,  0,   1 },
		{ -1,  0,   0, 0,  0,  -1,  1,  -1 },
		{ -1, -1,  -1, 0,  0,   0,  0,   1 },
		{ -1,  0,   0, 0,  0,  -1,  1,  -1 }
	},
	//  ▨
	//▨▨▨  도형
	{
		{ -1,  0,  0,  0,  0, -1,  1,  0 },
		{ -1, -1, -1,  0, -1,  1,  0,  0 },
		{ -1, -1,  0, -1,  1, -1,  0,  0 },
		{ -1,  0,  0, -1,  0,  0,  0,  1 },
	}	
};

POS NextPolycurrPos{ 31, 10 };
POS gcurrPos = { 10, 3 };
int buffer[TetrisSize_H][TetrisSize_W];
int initBuffer[TetrisSize_H][TetrisSize_W];
int GameTable[TetrisSize_H][TetrisSize_W] = {
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,1,1,1,1,1,1,1,1,1,1,1 }
};
int gdir;
int gselPoly;
int nextPoly;
void DrawPolygon(int selpolygon, int dirIndex, POS pos) {
	for (int i = 0; i < 4; ++i) {
		int x = pos.x + polygon[selpolygon][dirIndex][i].x * 2;
		int y = pos.y + polygon[selpolygon][dirIndex][i].y;

		CursorPos(x, y);
		printf("■");
	}
}
void reset() {
	gcurrPos.x = 10;
	gcurrPos.y = 2;
	gdir = 0;
	gselPoly = nextPoly;
	nextPoly = rand() % 6;
}
void PrintTable() {
	for (int i = 0; i < TetrisSize_H; i++) {
		for (int j = 0; j < TetrisSize_W; j++) {
			switch (GameTable[i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("▩");
				break;
			case 2:
				printf("□");
				break;
			}
		}
		printf("\n");
	}
	CursorPos(27, 7);
	printf("Next Block");
	DrawPolygon(nextPoly, 0, NextPolycurrPos);
}

POS ScreenToTable(int selpolygon, int direction, int index) {
	int x = (gcurrPos.x + polygon[selpolygon][direction][index].x * 2) / 2;
	int y = gcurrPos.y + polygon[selpolygon][direction][index].y;
	return { y,x };
}
bool CheckMove(int selpolygon, int dirIndex, int dirx, int diry) {
	int count = 0;
	for (int i = 0; i < 4; ++i){
		int x = (gcurrPos.x + polygon[selpolygon][dirIndex][i].x * 2) / 2;
		int y = gcurrPos.y + polygon[selpolygon][dirIndex][i].y;

		if (GameTable[y + diry][x + dirx] == 0) {
			count++;
		}
		else
			return false;
	} 
	if (count == 4) {
		return true;
	}
	
	return false;
}

void Input(){
	if (_kbhit()){
		int key = _getch();

		if (key == 224){
			key = _getch();

			switch (key){
				// up 키를 클릭하였다면
			case 72:
				if (CheckMove(gselPoly, (gdir + 1) % 4, 0, 0)) {
					++gdir;
					gdir %= 4;
				}
				break;
				//left
			case 75:
				if (CheckMove(gselPoly, gdir, -1, 0)) {
					gcurrPos.x -= 2;
				}
				break;
				//right
			case 77:
				if (CheckMove(gselPoly, gdir, 1, 0)) {
					gcurrPos.x += 2;
				}
				break;
				//down
			case 80:
				if (CheckMove(gselPoly, gdir, 0, 1)) {
					gcurrPos.y += 1;
				}
				break;
			}
		}
		else if(key == 32){
			while (CheckMove(gselPoly, gdir, 0, 1)) {
				gcurrPos.y += 1;
			}
		}
	}
}
bool CheckLine(int index)
{
	int count = 0;
	for (int i = 0; i < TetrisSize_W; ++i)
	{
		if (GameTable[index][i] == 2)
		{
			++count;
		}
	}
	if (count == TetrisSize_W-2)
		return true;

	return false;
}
void breakblock() {
	// 버퍼 값을 0값으로 초기화 합니다.
	memcpy(buffer, initBuffer, sizeof(initBuffer));
	int count = TetrisSize_H-1;
	for (int i = TetrisSize_H - 1; i > 0; --i){
		if (CheckLine(i) == false){
			memcpy(&buffer[count], &GameTable[i][0], sizeof(int) * TetrisSize_W);
			--count;
		}
	}
	memcpy(GameTable, buffer, sizeof(buffer));
}

bool gameover() {
	for (int i = 1;i < TetrisSize_W - 2;i++) {
		if (GameTable[1][i] == 2) {
			system("cls");
			printf("\n\n\t▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n");
			printf("\t▤  +-----------------------+   ▤\n");
			printf("\t▤  |                       |   ▤\n");
			printf("\t▤  |   G A M E  O V E R..  |   ▤\n");
			printf("\t▤  | 1:다시시작 2: 끝내기  |   ▤\n");
			printf("\t▤  |                       |   ▤\n");
			printf("\t▤  +-----------------------+   ▤\n");
			printf("\t▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n");
			Sleep(1000);
			return true;
		}
	}
	return false;
}
int main(){
	reset();
	memcpy(initBuffer, GameTable, sizeof(GameTable));
	srand((unsigned int)time(NULL));
	CursorVisible(false);
	int prevTime = GetTickCount();
	while (1){
			system("cls");
			Input();
			breakblock();
			PrintTable();
			DrawPolygon(gselPoly, gdir, gcurrPos);
		if (CheckMove(gselPoly, gdir, 0, 1)) {
			if (GetTickCount() - prevTime >= 1000) {
				gcurrPos.y += 1;
				prevTime = GetTickCount();
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				POS pos = ScreenToTable(gselPoly, gdir, i);
				GameTable[pos.x][pos.y] = 2;
			}
			reset();
		}
		while (1) {
			char input;
			if (gameover()) {
				scanf_s("%c", &input);
				if (input == '1') {
					printf("\t게임을 다시시작합니다.\n");
					Sleep(1000);
					memcpy(GameTable, initBuffer, sizeof(initBuffer));
					continue;
				}
				else if (input == '2') {
					printf("\t게임을 끝냅니다.\n");
					Sleep(1000);
					return 0;
				}
				else {
					printf("\t잘못 입력 하였습니다.\n");
					Sleep(1000);
				}
			}
			else { break; }
		}
		Sleep(50);
	}
    return 0;
}

