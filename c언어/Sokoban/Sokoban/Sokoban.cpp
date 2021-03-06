#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "Sokoban.h"

#define ROW 8
#define COLUMN 8
	//0=빈공간, 1 = 벽, 4 = 사용자, 3= 물건, 2 = 컨테이너
int gametable[ROW][COLUMN] ={
{ 0, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 1, 2, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 1, 1, 1, 1 },
{ 1, 1, 1, 3, 0, 3, 2, 1 },
{ 1, 2, 3, 4, 3, 1, 1, 1 },
{ 1, 1, 1, 1, 0, 1, 0, 0 },
{ 0, 0, 0, 1, 2, 1, 0, 0 },
{ 0, 0, 0, 1, 1, 1, 0, 0 }
};

Sokoban::Sokoban(){
	memcpy(Table, gametable, sizeof(Table));
}


Sokoban::~Sokoban(){
}
void Sokoban::FindContainerPos() {
	int count = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (Table[i][j] == 2) {
				pos[count].x = i;
				pos[count].y = j;
				count++;
			}
		}
	}
}
void Sokoban::FindChar(){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (Table[i][j] == 4){
				cX = i;
				cY = j;
				return;
			}
		}
	}
}
bool Sokoban::IsEnd(){
	int count = 0;
	for (int i = 0; i< 4; ++i){
		int x = pos[i].x;
		int y = pos[i].y;

		if (Table[x][y] == 3){
			++count;
		}
	}
	if (count == 4)
		return true;

	return false;
}
void Sokoban::ShowTable(){
	printf("\n");
	for (int i = 0; i < 8; ++i){
		printf("  ");
		for (int j = 0; j < 8; ++j){
			switch (Table[i][j]){
			case 0:
				printf("  ");
				break;

			case 1:
				printf("▒");
				break;

			case 3:
				printf("●");
				break;

			case 4:
				printf("Θ");
				break;

			case 2:
				printf("○");
				break;
			}
		}

		printf("\n");
	}
}
void Sokoban::Swap(int x, int y, int nx, int ny){
	int value = Table[x][y];
	Table[x][y] = Table[nx][ny];
	Table[nx][ny] = value;
}

void Sokoban::Move(int x, int y){
	if (cX == 0)
		return;

	int nX = cX + x;
	int nY = cY + y;

	int nextTable = Table[nX][nY];

	if (nextTable == 0)
		Swap(cX, cY, nX, nY);

	else if (nextTable == 1)
		return;

	else if (nextTable == 2){
		Table[nX][nY] = Table[cX][cY];
		Table[cX][cY] = 0;
	}

	else if (nextTable == 3){
		int nnX = nX + x;
		int nnY = nY + y;

		if (Table[nnX][nnY] == 0){
			Swap(nX, nY, nnX, nnY);
			Swap(cX, cY, nX, nY);
		}

		else if (Table[nnX][nnY] == 1)
			return;

		else if (Table[nnX][nnY] == 2){
			Table[nnX][nnY] = Table[nX][nY];
			Table[nX][nY] = Table[cX][cY];
			Table[cX][cY] = 0;
		}
	}
}
void Sokoban::Input(){
	if (_kbhit()){
		int key = _getch();
		if (key == 224){
			// 
			key = _getch();

			switch (key){
				// 위
			case 72:{
				if (cX == 0)
					return;

				Move(-1, 0);
			}
			break;
			// 아래
			case 80:{
				Move(1, 0);
			}
			break;
			// 왼쪽
			case 75:{
				Move(0, -1);
			}
			break;
			// 오른쪽
			case 77:{
				Move(0, 1);
			}
			break;
			}
		}
	}
}
void Sokoban::Run(){
	FindContainerPos();
	//memcpy(Table, Table2, sizeof(Table));
	while (1){
		system("cls");
		ShowTable();
		FindChar();
		Input();
		if (IsEnd()){
			system("cls");
			ShowTable();
			printf("게임을 클리어 하였습니다. !\n");
			Sleep(1000);
			return;
		}

		Sleep(100);
	}
}



