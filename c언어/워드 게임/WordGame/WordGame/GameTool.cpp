#include "stdafx.h"
#include "GameTool.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define TableSize 10

void CursorVisible(bool blnCursorVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = blnCursorVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void CursorPos(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int CapyMap[TableSize][TableSize] = {
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,1,0,0,0,1,1,0,1 },
	{ 1,0,1,0,1,0,1,1,0,1 },
	{ 1,0,0,0,1,0,0,0,0,1 },
	{ 1,1,0,1,1,0,1,1,0,1 },
	{ 1,0,0,0,0,0,1,0,0,1 },
	{ 1,0,1,1,1,0,1,1,0,1 },
	{ 1,0,1,1,0,0,0,0,0,1 },
	{ 1,0,0,0,0,1,1,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1 }};

GameTool::GameTool()
{
	srand((unsigned int)time(NULL));
	init();
}

GameTool::~GameTool()
{
}
void GameTool::init() {
	m_AttakDamage = 0;
	m_Armor = 0;
	m_Score = 0;
	m_isClear = true;
	user = { 1,1 };
	memcpy(GameMap, CapyMap, sizeof(GameMap));
	CursorVisible(false);
	m_UserHP = rand() % 81 + 20;
}
void GameTool::input() {
	if (_kbhit()) {
		int key = _getch();

		if (key == 224) {
			key = _getch();

			switch (key) {
				// up 키를 클릭하였다면
			case 72:
				if (CheckMove(user.x, user.y - 1)) {
					UserMove(user.x, user.y - 1);
				}
				break;
				//left
			case 75:
				if (CheckMove(user.x - 1, user.y)) {
					UserMove(user.x - 1, user.y);
				}

				break;
				//right
			case 77:
				if (CheckMove(user.x + 1, user.y)){
					UserMove(user.x + 1, user.y);
			}
				break;
				//down
			case 80:
				if (CheckMove(user.x, user.y + 1)){
					UserMove(user.x, user.y + 1);
			}
				break;
			}
		}
	}
}
void GameTool::DrawTable() {
	for (int i = 0; i < TableSize; i++) {
		for (int j = 0; j < TableSize; j++) {
			CursorPos(10 + j * 2, 5 + i);
			switch (GameMap[i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("▩");
				break;
			case 2:
				printf("★");
				break;
			}
		}
	}
	UserState();
}
void GameTool::run() {
	while (m_isClear) {
		Sleep(100);
		input();
		system("cls");
		DrawTable();
		GameOver();
	}
	Clear();
}
void GameTool::UserMove(int x, int y) {
	GameMap[user.y][user.x] = 0;
	GameMap[y][x] = 2;
	user.y = y;
	user.x = x;
	if (MonsterCheck()) {
		ShowMonster();
	}
	else if (ItemCheck()) {
		Itemget();
	}
}
bool GameTool::CheckMove(int x, int y) {
	if (GameMap[y][x] == 1) {
		CursorPos(13, 16);
		printf("이동 불가능!!!!\n");
		Sleep(200);
		return false;
	}
	else 
		return true;
}
void GameTool::UserState() {
	CursorPos(8, 2);
	printf("UserHP = %d   UserAttack = %d", m_UserHP, m_AttakDamage);
	CursorPos(8, 3);
	printf("Score = %d     UserAmor = %d", m_Score, m_Armor);
}
void GameTool::ShowMonster() {
	int isBoss = rand() % 2;
		CursorPos(10, 4);
	if (isBoss) {
		printf("보스 몬스터 만남");
		Sleep(1000);
		FightBoos();
	}
	else {
		printf("일반 몬스터 만남");
		Sleep(1000);
		FightMonster();
	}
}
bool GameTool::MonsterCheck() {
	int random = rand() % 10;//10개중 1개 10%
	if (random == 1) {
		return true;
	}
	return false;
}
void GameTool::FightBoos() {
	int BossHP = 100;
	int Userslect, Monster;
	while (BossHP > 0) {
		GameOver();
		system("cls");
		fflush(stdin);
		Monster = rand() % 3 + 1;
		CursorPos(10, 3);
		printf("Monster HP = %d", BossHP);
		CursorPos(10, 4);
		printf("User HP = %d", m_UserHP);
		CursorPos(10, 5);
		printf("1:가위,2:바위, 3:보, -1:도망치기\n");
		scanf_s(" %d", &Userslect, sizeof(int));
		if (Userslect == -1) {
			break;
		}
		else {
			int result = RPS(Userslect, Monster);
			if (result == 1) {
				switch (Userslect)
				{
				case 1:
					BossHP -= (2 + m_AttakDamage);
					break;
				case 2:
					BossHP -= (10 + m_AttakDamage);
					break;
				case 3:
					BossHP -= (5 + m_AttakDamage);
					break;
				}
			}
			else if (result == 0) {
				switch (Monster)
				{
				case 1:
					if((2 - m_Armor) > 0 )
						m_UserHP -= (2-m_Armor);
					break;
				case 2:
					if ((10 - m_Armor) > 0)
						m_UserHP -= (10 - m_Armor);
					break;
				case 3:
					if ((5 - m_Armor) > 0)
						m_UserHP -= (5 - m_Armor);
					break;
				}
			}
		}
	}
	if (BossHP <= 0) {
		m_Score += 1000;
		m_isClear = false;
		printf("보스 몬스터 처치");
	}
}
void GameTool::FightMonster() {
	int MonsterHP = 10;
	int Userslect, Monster;
	while (MonsterHP > 0) {
		GameOver();
		fflush(stdin);
		system("cls");
		Monster = rand() % 3+1;
		CursorPos(10, 3);
		printf("Monster HP = %d", MonsterHP);
		CursorPos(10, 4);
		printf("User HP = %d", m_UserHP);
		CursorPos(10, 5);
		printf("1:가위,2:바위, 3:보, -1:도망치기\n");
		scanf_s(" %d", &Userslect, sizeof(int));
		if (Userslect == -1) {
			break;
		}
		else {
			int result = RPS(Userslect, Monster);
			if (result == 1) {
				switch (Userslect)
				{
				case 1:
					MonsterHP -= (2 + m_AttakDamage);
					break;
				case 2:
					MonsterHP -= (10 + m_AttakDamage);
					break;
				case 3:
					MonsterHP -= (5 + m_AttakDamage);
					break;
				}
			}
			else if (result == 0) {
				switch (Monster)
				{
				case 1:
					if ((2 - m_Armor) > 0)
						m_UserHP -= (2 - m_Armor);
					break;
				case 2:
					if ((10 - m_Armor) > 0)
						m_UserHP -= (10 - m_Armor);
					break;
				case 3:
					if ((5 - m_Armor) > 0)
						m_UserHP -= (5 - m_Armor);
					break;
				}
			}
		}
	}
	if (MonsterHP <= 0) {
		m_Score += 100;
		printf("일반 몬스터 처치");
		Sleep(300);
	}
}
int GameTool::RPS(int user, int monster) {
	int result;
	if (user == monster) {
		printf("비겼습니다.");
		Sleep(500);
		return 2;
	}
	if ((user == 1 && monster == 3) ||
		(user == 2 && monster == 1) ||
		(user == 3 && monster == 1)) {
		printf("이겼습니다.");
		Sleep(500);
		return 1;
	}
	else if ((monster == 1 && user == 3) ||
		(monster == 2 && user == 1) ||
		(monster == 3 && user == 1)) {
		printf("졌습니다.");
		Sleep(500);
		return 0;
	}
}
void GameTool::Itemget() {
	int random = rand() % 3;
	CursorPos(10, 4);
	switch (random)
	{
	case 0:
		printf("체력 10회복 아이템을 사용");
		Sleep(1000);
		m_UserHP += 10;
		break;
	case 1:
		printf("공격력 1강화");
		Sleep(1000);
		m_AttakDamage += 1;
		break;
	case 2:
		printf("방어력 1강화");
		Sleep(1000);
		m_Armor += 1;
	default:
		break;
	} 
}
bool GameTool::ItemCheck() {
	int random = rand() % 20;//20개중 1개 5%
	if (random == 1) {
		CursorPos(10, 4);
		printf("아이템 발견");
		Sleep(500);
		return true;
	}
	return false;
}
void GameTool::GameOver() {
	char a;
	if (m_UserHP < 0) {
		system("cls");
		printf("\n\n\t▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n");
		printf("\t▤  +-----------------------+   ▤\n");
		printf("\t▤  |                       |   ▤\n");
		printf("\t▤  |       GameOver        |   ▤\n");
		printf("\t▤  |                       |   ▤\n");
		printf("\t▤  +-----------------------+   ▤\n");
		printf("\t▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n");
		printf("다시하시겠습니까?(Y/N)");
		scanf_s("%c", &a);
		if (a == 'n' || a == 'N') {
			m_isClear == false;
			return;
		}
		init();
	}
	return;
}
void GameTool::Clear() {
	system("cls");
	printf("\n\n\t▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n");
	printf("\t▤  +-----------------------+   ▤\n");
	printf("\t▤  |                       |   ▤\n");
	printf("\t▤  |   게임을 끝냅니다.    |   ▤\n");
	printf("\t▤  |      Score = %d       |   ▤\n", m_Score);
	printf("\t▤  +-----------------------+   ▤\n");
	printf("\t▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤\n");
}