#pragma once
class GameTool
{
	typedef struct ContainerPosition
	{
		int x;
		int y;
	}UserPos;
private:
	int m_UserHP;
	int m_Score;
	int m_isClear;
	int m_AttakDamage;
	int m_Armor;
	int GameMap[10][10];
	UserPos user;
public:
	GameTool();
	~GameTool();

public:
	void init();
	void input();
	void DrawTable();
	void run();
	void UserMove(int x, int y);
	bool CheckMove(int x, int y);
	void UserState();
	void ShowMonster();
	bool MonsterCheck();
	void FightBoos();
	void FightMonster();
	int RPS(int user, int monster);
	bool ItemCheck();
	void Itemget();
	void GameOver();
	void Clear();
};

