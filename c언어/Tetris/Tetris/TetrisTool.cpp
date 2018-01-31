#include "stdafx.h"

#include "TetrisTool.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define TetrisSize_H 23
#define TetrisSize_W 12
#define cursorx 2
#define cursory 2
int score = 0;
int level = 1;
int speed = 60;
int TetrisTable[TetrisSize_H][TetrisSize_W];
int CapyTable[TetrisSize_H][TetrisSize_W];
bool IsNewBlock = false;

int block[7][4][4][4] = { { {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },			//���
{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },			//���
{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 }},
{{ 0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0 },		//��
{ 1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },		//��
{ 0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0 },		//��
{ 1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0 }},		//��
{{ 0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0 },
{ 0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0},			//��
{ 0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0},			//����
{ 0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0 } },
{ { 0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0},
{ 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 },			//    ��
{ 0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0 },			//����
{ 0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,1 } },
{ { 0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0},
{ 0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0 },			//���
{ 0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0 },			//  ���
{ 0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0 } },
{ { 0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1 },			//   ���
{ 0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0 },			// ��� 
{ 0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1 } },
{ { 0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,1,1,0,0,1,0 },			//  ��
{ 0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0 },			//����
{ 0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0 } } };

int x;
int y;
int count;
int b_type;
int b_rotation;
int nextblock;
namespace TetrisTool {

	void CursorVisible(bool blnCursorVisible)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
		cursorInfo.bVisible = blnCursorVisible;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

	void SetCursorPosition(int posX, int posY)
	{
		COORD pos = {posX, posY};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void print() {		
		for (int i = 1; i < TetrisSize_W - 1; i++) {
			if(TetrisTable[2][i] ==0)
				TetrisTable[2][i] = 4;
		}
		for (int i = 0; i < TetrisSize_H; i++) {
			for (int j = 0; j < TetrisSize_W; j++) {
				if (CapyTable[i][j] != TetrisTable[i][j]) {
					SetCursorPosition((cursorx+j)*2, cursory+i);
					switch (TetrisTable[i][j]){
					case 0:
						printf("  ");
						break;
					case 1:
						printf("��");
						break;
					case 2:
						printf("��");
						break;
					case 3:
						printf("��");
						break;
					case 4:
						printf("-");
						break;
					}
				}
			}
		}
		for (int i = 0;i<TetrisSize_H;i++) { //�������� �׸� �� main_cpy�� ����  
			for (int j = 0;j<TetrisSize_W;j++) {
				CapyTable[i][j] = TetrisTable[i][j];
			}
		}
		
		SetCursorPosition(cursorx + 20 * 2, cursory + 9 + 2);printf("         Level: %d       ", level);
		SetCursorPosition(cursorx + 20 * 2, cursory + 12 + 2);printf("         Score: %-5d  ", score);
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				SetCursorPosition((cursorx +16*2)+j * 2, cursory + i+18);
				switch (block[nextblock][0][i][j])
				{
				case 0:
					printf("  ");
					break;
				case 1:
					printf("��");
					break;
				}
			}
		}
	}

	void init() {
		b_type = rand() % 7;
		level = 1;
		score = 0;
		speed = 60;
		x = (TetrisSize_W) / 2-2;
		y = 0;
		CursorVisible(false);
		initdraw();
		srand((unsigned)time(NULL));
		for (int i = 0; i < TetrisSize_H; i++) {
			for (int j = 0; j < TetrisSize_W; j++) {
				if ((i == TetrisSize_H - 1) || (j == 0)  || (j == TetrisSize_W-1)) {
					TetrisTable[i][j] = 3;
				}
				else {
					TetrisTable[i][j] = 0;
				}
			}
		}
		for (int i = 1; i < TetrisSize_W-1; i++) {
			TetrisTable[2][i] = 4;
		}
		for (int i = 0; i < TetrisSize_H; i++) {
			for (int j = 0; j < TetrisSize_W; j++) {
				CapyTable[i][j] = 100;
			}
		}
	}

	void newblock() {
		x = (TetrisSize_W) / 2 - 2;
		y = 0;
		b_type = nextblock;
		nextblock = rand() % 7;
		b_rotation = 0;
		for (int i = 0;i<4;i++) { //������ x, y��ġ�� ������  
			for (int j = 0;j<4;j++) {
				if (block[b_type][b_rotation][i][j] == 1) 
					TetrisTable[y + i][x + j] = 1;
			}
		}
	}

	void breakblock() {
		int count = 0;
		int countLevel = 1;
		int breakx;
		for (int i = 0; i < TetrisSize_H; i++) {
			count = 0;
			for (int j = 0; j < TetrisSize_W; j++) {
				if (TetrisTable[i][j] == 2)
					count++;
			}
			if (count == TetrisSize_W - 2) {
				countLevel++;
				breakx = i;
				for (int j = 0; j < TetrisSize_W; j++) {
					if (TetrisTable[i][j] == 2) {
						TetrisTable[i][j] = 0;
					}
				}
				for (int i = breakx; i > 0; i--) {
					for (int j = 1; j < TetrisSize_W - 1; j++) {
						if (TetrisTable[i][j] == 2) {
							TetrisTable[i][j] = 0;
							TetrisTable[i+1][j] = 2;
						}
					}
				}
			}
		}
		for (int i = 0;i < countLevel; i++) {
			score += 10 * i * level;
		}
	}
	void initdraw() {
		count = 1;
		int Titlex = cursorx + 16 * 2;
		int NBx = cursorx + 15 * 2;
		SetCursorPosition(Titlex, cursory + count++);
		printf("�����  �����  �����  �����  ��  ����");
		SetCursorPosition(Titlex, cursory + count++);
		printf("   ��     ��           ��     ��    ��  ��  ��    ");
		SetCursorPosition(Titlex, cursory + count++);
		printf("   ��     �����     ��     �����  ��  ����");
		SetCursorPosition(Titlex, cursory + count++);
		printf("   ��     ��           ��     ��  ��    ��      ��");
		SetCursorPosition(Titlex, cursory + count++);
		printf("   ��     �����     ��     ��    ��  ��  ����");
		SetCursorPosition(NBx+2, cursory + 15);
		printf("Next block");
		SetCursorPosition(NBx, cursory + 17);
		printf("�̢̢̢̢̢̢�");
		SetCursorPosition(NBx, cursory + 18);
		printf("��          ��");
		SetCursorPosition(NBx, cursory + 19);
		printf("��          ��");
		SetCursorPosition(NBx, cursory + 20);
		printf("��          ��");
		SetCursorPosition(NBx, cursory + 21);
		printf("��          ��");
		SetCursorPosition(NBx, cursory + 22);
		printf("�̢̢̢̢̢̢�");
		SetCursorPosition(0, cursory + 24);
		printf("\t�� = ROTATE \t P = PASUE \n\t�� = move left \t R = Reset\n\t�� = move right  Space Bar = dorp\n\t�� = move down");
		for (int i = 1; i < TetrisSize_W - 1; i++) {
			if (TetrisTable[2][i] == 0)
				TetrisTable[2][i] = 4;
		}
		for (int i = 0; i < TetrisSize_H; i++) {
			for (int j = 0; j < TetrisSize_W; j++) {
					SetCursorPosition((cursorx + j) * 2, cursory + i);
					switch (TetrisTable[i][j]) {
					case 0:
						printf("  ");
						break;
					case 1:
						printf("��");
						break;
					case 2:
						printf("��");
						break;
					case 3:
						printf("��");
						break;
					case 4:
						printf("-");
						break;
					}
				}
			}
	}
	void InputDir() {
		int key = 0;
		int c = 0;

		if (_kbhit()) {
				key = _getch();
				switch (key) {
				case 'p':
					system("cls");
					printf("\n\n\t�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n");
					printf("\t��  +-----------------------+   ��\n");
					printf("\t��  |                       |   ��\n");
					printf("\t��  |       P A U S E       |   ��\n");
					printf("\t��  |                       |   ��\n");
					printf("\t��  +-----------------------+   ��\n");
					printf("\t�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n");
					system("PAUSE");
					system("cls");
					initdraw();
					break;
				case 'r':
					Sleep(100);
					init();
					break;
				case UP:
					if (check(x, y, b_rotation+1) == true)
						move(UP);
					break;
				case DOWN:
					if (check(x, y+1, b_rotation) == true)
						move(DOWN);
					break;
				case LEFT:
					if (check(x - 1, y, b_rotation) == true) 
						move(LEFT);
					break;

				case RIGHT:
					if (check(x+1, y, b_rotation) == true) 
						move(RIGHT);
					break;
				case SPACE:
					while (1) {
						if (check(x, y+1, b_rotation) == true)
							dropblock();
						else break;
					
					}
					break;
			}
		}
	}

	void move(int dir) {
		int i, j;
		switch (dir) {
		case LEFT: //���ʹ��� 
			for (i = 0;i<4;i++) { //������ǥ�� ���� ���� 
				for (j = 0;j<4;j++) {
					if (block[b_type][b_rotation][i][j] == 1) 
						TetrisTable[y + i][x + j] = 0;
				}
			}
			for (i = 0;i<4;i++) { //�������� ��ĭ���� active block�� ���� 
				for (j = 0;j<4;j++) {
					if (block[b_type][b_rotation][i][j] == 1) 
						TetrisTable[y + i][x + j - 1] = 1;
				}
			}
			x --;//��ǥ�� �̵� 
			break;

		case RIGHT:    //������ ����. ���ʹ����̶� ���� ������ ���� 
			for (i = 0;i<4;i++) {
				for (j = 0;j<4;j++) {
					if (block[b_type][b_rotation][i][j] == 1) 
						TetrisTable[y + i][x + j] = 0;
				}
			}
			for (i = 0;i<4;i++) {
				for (j = 0;j<4;j++) {
					if (block[b_type][b_rotation][i][j] == 1) 
						TetrisTable[y + i][x + j + 1] = 1;
				}
			}
			x++;
			break;

		case DOWN:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
			for (i = 0;i<4;i++) {
				for (j = 0;j<4;j++) {
					if (block[b_type][b_rotation][i][j] == 1) 
						TetrisTable[y + i][x + j] = 0;
				}
			}
			for (i = 0;i<4;i++) {
				for (j = 0;j<4;j++) {
					if (block[b_type][b_rotation][i][j] == 1) 
						TetrisTable[y + i + 1][x + j] = 1;
				}
			}
			y++;
			break;

		case UP: //Ű���� ���� �������� ȸ����Ŵ. 
			for (i = 0;i<4;i++) { //������ǥ�� ���� ����  
				for (j = 0;j<4;j++) {
					if (block[b_type][b_rotation][i][j] == 1) 
						TetrisTable[y + i][x + j] = 0;
				}
			}
			b_rotation = (b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
			for (i = 0;i<4;i++) { //ȸ���� ����� ���� 
				for (j = 0;j<4;j++) {
					if (block[b_type][b_rotation][i][j] == 1) 
						TetrisTable[y + i][x + j] = 1;
				}
			}
			break;
		}
	}

	bool check(int bx, int by, int rotation) {
		int i, j;
		for (i = 0;i<4;i++) {
			for (j = 0;j<4;j++) { 
				if (block[b_type][(rotation%4)][i][j] == 1 && (TetrisTable[by + i][bx + j] == 3
					|| TetrisTable[by + i][bx + j] == 2))
					return false;
			}
		}
		return true; //�ϳ��� �Ȱ�ġ�� true���� 
	}

	void dropblock() {
		int i, j;
		for (i = 0;i<4;i++) { //������ǥ�� ���� ����  
			for (j = 0;j<4;j++) {
				if (block[b_type][b_rotation][i][j] == 1)
					TetrisTable[y + i][x + j] = 0;
			}
		}
		for (i = 0;i<4;i++) { //������ ��ĭ ������ ��
			for (j = 0;j<4;j++) {
				if (block[b_type][b_rotation][i][j] == 1)
					TetrisTable[y + i+1][x + j] = 1;
			}
		}
		y++;
	}

	void changebolck() {
		int i,j;
		for (i = 0;i<4;i++) {
			for (j = 0;j<4;j++) {
				if (block[b_type][b_rotation][i][j] == 1)
					TetrisTable[y + i][x + j] = 2;
			}
		}
	}

	void gameover() {
		for (int i = 1;i < TetrisSize_W - 2;i++) {
			if (TetrisTable[2][i] == 2) {
				system("cls");
				printf("\n\n\t�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n");
				printf("\t��  +-----------------------+   ��\n");
				printf("\t��  |   G A M E  O V E R..  |   ��\n");
				printf("\t��  |                       |   ��\n");
				printf("\t��  |     your score = %-5d|   ��\n", score);
				printf("\t��  +-----------------------+   ��\n");
				printf("\t�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�\n");
				Sleep(1000);
				system("cls");
				init();
			}
		}
	}
	
	void levelup() {
		if (score > 100 && score <= 300) {
			level = 2;
			speed = 50;
			return;
		}
		else if (score > 300 && score <= 600) {
			level = 3;
			speed = 40;
			return;
		}
		else if (score > 600 && score <= 1200) {
			level = 4;
			speed = 30;
			return;
		}
		else if (score > 1500) {
			level = 5;
			speed = 20;
			return;
		}
	}
	void run() {
		init();
		while (1) {
			if (IsNewBlock == false) {
				newblock();
				IsNewBlock = true;
			}
			for (int i = 0; i < 5; i++) {
				InputDir();
				print();
				Sleep(speed);
			}
			if (check(x, y+1, b_rotation)) {
				dropblock();
			}
			else {
				changebolck();
				IsNewBlock = false;
			}
			breakblock();
			levelup();
			gameover();
		}
	}
}