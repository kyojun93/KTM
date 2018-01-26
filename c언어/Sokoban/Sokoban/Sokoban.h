#pragma once
#pragma once
class Sokoban
{
private:

	typedef struct ContainerPosition
	{
		int x;
		int y;
	}Pos;

private:
	int cX, cY;
	Pos pos[4];

	int Table[8][8];

public:
	Sokoban();
	~Sokoban();

public:
	void FindContainerPos();
	void FindChar();
	bool IsEnd();
	void ShowTable();
	void Swap(int x, int y, int nx, int ny);
	void Move(int x, int y);
	void Input();
	void Run();

};

