#include "stdafx.h"
#include "PuzzleHelper.h"

#include <stdlib.h> 
#include <time.h>   
#include <conio.h>  
#include <windows.h> 

#define PUZZLE_SIZE 3
#define CHIP_COUNT PUZZLE_SIZE*PUZZLE_SIZE-1

int gametable[PUZZLE_SIZE][PUZZLE_SIZE];

int row = 0;
int column = 0;

bool isEnd = false;

namespace PuzzleHelper
{
	//�ʱ�ȭ �Լ�
	void Initialize() {
		for (int i = 0; i < PUZZLE_SIZE; ++i){
			for (int j = 0; j< PUZZLE_SIZE; ++j){
				gametable[i][j] = i * PUZZLE_SIZE + j + 1;
			}
		}
		gametable[PUZZLE_SIZE - 1][PUZZLE_SIZE - 1] = 0;
	}

	//���̺��� ���¸� �����ִ� �Լ�
	void ShowTable() {
		for (int i = 0; i < PUZZLE_SIZE; ++i){
			for (int j = 0; j< PUZZLE_SIZE; ++j){
				printf("[ %2d ] ", gametable[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	//��ȯ����
	void Run() {
		srand((unsigned)time(NULL));

		int a = 0;
		// �⺻ �ʱ�ȭ
		Initialize();

		// ī�带 ������ �մϴ�.
		ShuffleCards();

		while (!isEnd){
			system("cls");

			ShowTable();

			InputDir();

			if (IsClear()){
				system("cls");
				ShowTable();

				printf("������ Ŭ���� �Ͽ����ϴ�.!");
				Sleep(2000);
				isEnd = true;
			}
			Sleep(100);
		}
	}

	void ShuffleCards() {
		int randomCount = 80 + rand() % 30;

		// ��� �����ٸ� ������ �� �ֵ��� �Ѵ�.
		while (randomCount > 0){
			int dir = rand() % 4;
			switch (dir){
				// �������� �̵�
			case 0:
				if ((column - 1) >= 0){
					swap(row, column, row, column - 1);
				}
				break;

			case 1:
				if ((column + 1) <= PUZZLE_SIZE - 1){
					swap(row, column, row, column+1);
				}
				break;

			case 2:
				if ((row - 1) >= 0){
					swap(row, column, row - 1, column);
				}
				break;

			case 3:
				if ((row + 1) <= (PUZZLE_SIZE - 1)){
					swap(row, column, row + 1, column);
				}
				break;
			}

			--randomCount;
		}
		FindZero();
	}

	void swap(int x, int y, int mx, int my) {
		int temp = gametable[x][y];
		gametable[x][y] = gametable[mx][my];
		gametable[mx][my] = temp;
	}

	void FindZero() {
		for (int i = 0; i < PUZZLE_SIZE; ++i){
			for (int j = 0; j< PUZZLE_SIZE; ++j){
				if (gametable[i][j] == 0){
					row = i;
					column = j;
					return;
				}
			}
		}
	}

	void InputDir() {
		printf("�̵��� ������ �Է��ϼ���.!\n");

		int key = 0;
		int c = 0;

		if (_kbhit()){
			int key = _getch();
			if (key == 27){
				printf("����Ű�� ���� ������ �����մϴ�.! \n");
				isEnd = true;
				Sleep(1000);
			}

			else if (key == 224){
				key = _getch();

				FindZero();

				switch (key){
				case 72:
					if ((row - 1) < 0){
						printf("�̵��� �� �����ϴ�. !");
						Sleep(1000);
					}
					else{
						swap(row, column, row - 1, column);
					}
					break;
				case 80:
					if ((row + 1) >= PUZZLE_SIZE){
						printf("�̵��� �� �����ϴ�. !");
						Sleep(1000);
					}
					else{
						swap(row, column, row + 1, column);
					}
					break;

				case 75:
					if ((column - 1) < 0){
						printf("�̵��� �� �����ϴ�. !");
						Sleep(1000);
					}
					else{
						swap(row, column, row, column-1);
					}
					break;

				case 77:
					if ((column + 1) >= PUZZLE_SIZE){
						printf("�̵��� �� �����ϴ�. !");
						Sleep(1000);
					}
					else{
						swap(row, column, row, column + 1);
					}
					break;
				}
			}
			else{
				printf("�߸� �Է��ϼ̽��ϴ�.\n����Ű�� �Է��ϼ���.! \n");
				Sleep(1000);
			}
		}
	}

	bool IsClear() {
		int count = 1;

		for (int i = 0; i < PUZZLE_SIZE; ++i){
			for (int j = 0; j < PUZZLE_SIZE; ++j){
				if (count == gametable[i][j]) {
					count++;
				}
				else
					break;
			}
		}
		if (count == PUZZLE_SIZE * PUZZLE_SIZE)
			return true;
		else
			return false;
	}
}