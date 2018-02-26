#include "stdafx.h"
#include "Block.h"
#include "Tetris.h"
#include <time.h>

typedef enum TABLESIZE { WIDTH = 12, HEIGHT = 20, LINECOUNT = WIDTH - 2 } TSIZE;
typedef enum SPACETYPE { EMPTY = 0, BLOCK = 1, WALL = 2, ENTRY = 3 } STYPE;

typedef struct GameColor
{
	COLORREF penColor;
	COLORREF brushColor;
}GColor;

GColor color[8] =
{
	{ RGB(0,0,0), RGB(128,128,128) }, // 벽
	{ RGB(0,0,0), RGB(255,  0,  0) }, // 0 번 블록색
	{ RGB(0,0,0), RGB(244,164,196) }, // 1 번 블록색
	{ RGB(0,0,0), RGB(255,255,  0) }, // 2 번 블록색
	{ RGB(0,0,0), RGB(0,255,  0) }, // 3 번 블록색
	{ RGB(0,0,0), RGB(128,128,  0) }, // 4 번 블록색
	{ RGB(0,0,0), RGB(255,182,193) }, // 5 번 블록색
	{ RGB(0,0,0), RGB(0,191,255) }  // 6 번 블록색
};

int gCheckTable[HEIGHT][WIDTH];

int gGameTable[HEIGHT][WIDTH] =
{
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
	{ 1,1,1,1,1,1,1,1,1,1,1,1 },
};

POS polygon[7][4][4] =
{
	// ▨
	// ▨▨▨ 도형
	{
		{ 0, 0, -1,  0,  1,  0,  -1, -1 },
		{ 0, 0,  0, 1, 0, -1,  1,  -1 },
		{ 0, 0, -1,  0,  1,  0, 1,  1 },
		{ 0, 0,  0, -1,  0,  1,  -1,  1 }
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
		{ -1, -1,  0, -1,  0,  0,  0,   1 },
		{ -1,  0,  0,  0,  1,  0, -1,   1 },
		{ 0, -1,  0,  0,  0,  1,  1,   1 },
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
	//▨▨ 
	//▨ 도형
	{
		{ -1,  0,  0,  0,  0, -1, -1, 1 },
		{ -1, -1,  0, -1,  0,  0,  1, 0 },
		{ -1,  0,  0,  0,  0, -1, -1, 1 },
		{ -1, -1,  0, -1,  0,  0,  1, 0 },
	},

	//  ▨
	//▨▨▨
	{
		{ -1,  0,   0, 0,  1,  0,  0, -1 },
		{ 0,  1,   0, 0,  0, -1,  1,  0 },
		{ -1,  0,   0, 0,  1,  0,  0,  1 },
		{ 0,  1,   0, 0,  0, -1,  -1,  0 },

	}
};

#define KEY_LEFT	1
#define KEY_RIGHT	2
#define KEY_SPACE	4
#define KEY_UP      8
#define KEY_DOWN    16

Tetris::Tetris()
{
	InitData();
}


Tetris::~Tetris()
{
	if (m_pBlock != NULL)
		delete[] m_pBlock;

	if (m_pCheckTable != NULL)
	{
		for (int i = 0; i < HEIGHT; ++i)
		{
			delete[] m_pCheckTable[i];
		}

		delete[] m_pCheckTable;
	}
}

void Tetris::InitData()
{
	m_pBlock = NULL;
	m_pCheckTable = NULL;
	m_KeyState = true;
	m_Nextpolygon = rand() % m_PolygonCount;
	m_tableSize = sizeof(int) * WIDTH * HEIGHT;

	srand((unsigned int)time(NULL));
	memcpy(m_GameTable, gGameTable, m_tableSize);

	m_pBlock = new Block[8];

	m_pCheckTable = new int*[HEIGHT];

	for (int i = 0; i < HEIGHT; ++i)
		m_pCheckTable[i] = new int[WIDTH];

	for (int i = 0; i < 8; ++i)
	{
		m_pBlock[i].CreateBlockBrush(color[i].brushColor);
		m_pBlock[i].CreateBlockPen(PS_SOLID, 2, color[i].penColor);
		m_pBlock[i].SetSize(20, 20);
		m_pBlock[i].SetPos(0, 0);
	}

	m_prevTime = 0;
	m_GameScore = 0;
	m_KeySpeed = 150;
	m_GameLevel = 1;
	m_GameSpeed = 500;

	Reset();

}

void Tetris::LoadData(TCHAR* path)
{

}

void Tetris::DrawTable(HDC hdc)
{
	TCHAR str[128];
	SetBkColor(hdc, RGB(37, 235, 210));
	wsprintf(str, TEXT("Score  %d 점"), m_GameScore);
	TextOut(hdc, 300, 240, str, lstrlen(str));
	wsprintf(str, TEXT("Level  %d"), m_GameLevel);
	TextOut(hdc, 310, 210, str, lstrlen(str));
	for (int i = 0; i < 20; ++i)
	{
		int posY = i * 20 + m_startPos;

		for (int j = 0; j < 12; ++j)
		{
			int posX = j * 20 + m_startPos;

			int blockType = m_GameTable[i][j] - 1;

			if (blockType < 0)
				continue;

			m_pBlock[blockType].SetPos(posX, posY);
			m_pBlock[blockType].Render(hdc);
		}
	}
}
void Tetris::DrawNextPolygon(HDC hdc) {
	TCHAR str[100] = TEXT("Next Block");
	TextOut(hdc, 300, 40, str, lstrlen(str));
	for (int i = 0; i < 4; ++i)
	{
		int posx = 330 + polygon[m_Nextpolygon][0][i].x * 20 + m_startPos;
		int posy = 5 * 20 + polygon[m_Nextpolygon][0][i].y * 20 + m_startPos;

		m_pBlock[m_Nextpolygon + 1].SetPos(posx, posy);
		m_pBlock[m_Nextpolygon + 1].Render(hdc);
	}
}

void Tetris::DrawPolygon(HDC hdc, int x, int y)
{
	for (int i = 0; i < 4; ++i)
	{
		int posx = x * 20 + polygon[m_selpolygon][m_dirIndex][i].x * 20 + m_startPos;
		int posy = y * 20 + polygon[m_selpolygon][m_dirIndex][i].y * 20 + m_startPos;

		m_pBlock[m_selpolygon + 1].SetPos(posx, posy);
		m_pBlock[m_selpolygon + 1].Render(hdc);
	}
}

void Tetris::DrawPolygon(HDC hdc)
{
	DrawPolygon(hdc, m_Pos.x, m_Pos.y);

	int x = m_Pos.x;
	int y = m_Pos.y;


	for (int i = m_Pos.y; i < HEIGHT - 1; ++i)
	{

		if (CalculatePositionFall(x, i))
		{
			x = x;
			y = i;
		}
	}

	DrawPolygon(hdc, x, y);
}

void Tetris::Reset()
{
	m_Pos.x = 5;
	m_Pos.y = 1;

	m_dirIndex = 0;
	m_selpolygon = m_Nextpolygon;
	m_Nextpolygon = rand() % m_PolygonCount;
}

void Tetris::Input()
{
	if (!m_KeyState)
		return;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_Key & KEY_LEFT)
			return;
		else
			AddKey(KEY_LEFT);
	}
	else
	{
		if (m_Key & KEY_LEFT)
			RemoveKey(KEY_LEFT);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_Key & KEY_RIGHT)
			return;

		else
			AddKey(KEY_RIGHT);
	}
	else
	{
		if (m_Key & KEY_RIGHT)
			RemoveKey(KEY_RIGHT);
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (m_Key & KEY_UP)
			return;

		else
			AddKey(KEY_UP);
	}
	else
	{
		if (m_Key & KEY_UP)
		{
			if (CheckMoving(m_Pos.x, m_Pos.y, m_dirIndex + 1))
			{
				++m_dirIndex;
				m_dirIndex %= 4;
			}

			RemoveKey(KEY_UP);
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (m_Key & KEY_DOWN)
			return;

		else
			AddKey(KEY_DOWN);
	}
	else
	{
		if (m_Key & KEY_DOWN)
		{
			RemoveKey(KEY_DOWN);
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_Key & KEY_SPACE)
			return;

		else
			AddKey(KEY_SPACE);
	}
	else
	{
		if (m_Key & KEY_SPACE)
		{
			m_KeyState = false;
			m_prevGameSpeed = m_GameSpeed;
			m_GameSpeed = 20;
			RemoveKey(KEY_SPACE);
		}
	}
}

void Tetris::AddKey(int key)
{
	m_Key |= key;
}

void Tetris::RemoveKey(int key)
{
	int reverse = ~key;
	reverse = reverse | m_Key;
	m_Key = ~reverse;
}

void Tetris::KeyUpdate()
{
	if ((m_Key & KEY_LEFT) || (m_Key & KEY_RIGHT) || (m_Key & KEY_DOWN))
	{
		DWORD elapsedTime = timeGetTime() - m_prevTime;

		if (elapsedTime > m_KeySpeed)
		{
			if (m_Key & KEY_LEFT)
			{
				if (CheckMoving(m_Pos.x - 1, m_Pos.y, m_dirIndex))
					m_Pos.x -= 1;
			}

			if (m_Key & KEY_RIGHT)
			{
				if (CheckMoving(m_Pos.x + 1, m_Pos.y, m_dirIndex))
					m_Pos.x += 1;
			}

			if (m_Key & KEY_DOWN)
			{
				if (CheckMoving(m_Pos.x, m_Pos.y + 1, m_dirIndex))
					m_Pos.y += 1;

			}

			m_prevTime = timeGetTime();
		}
	}
}

void Tetris::Update()
{
	MoveDown();
	KeyUpdate();
	EraseLine();

}

void Tetris::MoveDown()
{
	DWORD elapsedTime = timeGetTime() - m_prevDownTime;

	if (elapsedTime > m_GameSpeed)
	{
		if (CheckMoving(m_Pos.x, m_Pos.y + 1, m_dirIndex))
			m_Pos.y += 1;

		else
		{
			m_KeyState = true;
			m_GameSpeed = m_prevGameSpeed;
			FixBlock();
			Reset();
		}

		m_prevDownTime = timeGetTime();
	}
}

void Tetris::FixBlock()
{
	for (int i = 0; i < 4; ++i)
	{
		int row = polygon[m_selpolygon][m_dirIndex][i].y + m_Pos.y;
		int column = polygon[m_selpolygon][m_dirIndex][i].x + m_Pos.x;

		if (row < 0)
		{
			m_isEnd = true;
			continue;
		}
		m_GameTable[row][column] = m_selpolygon + 2;
	}
	m_dirIndex = 0;
}

bool Tetris::CheckMoving(float x, float y, int currRot)
{
	int posX = x;
	int posY = y;

	if (currRot > 3)
		currRot = 0;

	for (int i = 0; i < 4; ++i)
	{
		int blockPosX = polygon[m_selpolygon][currRot][i].x + posX;
		int blockPosY = polygon[m_selpolygon][currRot][i].y + posY;

		if (blockPosX == 0)
			return false;

		if (blockPosX >= (TSIZE::WIDTH - 1))
			return false;

		if (blockPosY >= (TSIZE::HEIGHT - 1))
			return false;

		if (m_GameTable[blockPosY][blockPosX] != 0)
			return false;
	}
	return true;
}
void Tetris::EraseLine()
{
	int ScoreCnt = 1;
	int currRow = TSIZE::HEIGHT - 2;

	int clearRow = 0;

	for (int i = 0; i < HEIGHT; ++i)
		memcpy(m_pCheckTable[i], gGameTable[i], sizeof(int) * WIDTH);


	for (int row = TSIZE::HEIGHT - 2; row > 1; --row)
	{
		int count = 0;
		for (int column = 1; column <= TSIZE::LINECOUNT; ++column)
		{
			if (m_GameTable[row][column] != 0)
				++count;
		}

		if (count < TSIZE::LINECOUNT)
		{
			memcpy(m_pCheckTable[currRow], m_GameTable[row], sizeof(int) * WIDTH);
			--currRow;
		}
		
		else
		{
			m_GameScore += (10 * ScoreCnt++);
			++clearRow;
		}
	}

	for (int i = 0; i < HEIGHT; ++i)
	{
		memcpy(m_GameTable[i], m_pCheckTable[i], sizeof(int) * WIDTH);
	}
}

bool Tetris::CalculatePositionFall(int x, int y)
{
	POS pos = { 0, 0 };

	int count = 0;

	for (int i = 0; i < 4; ++i)
	{

		int posX = x + polygon[m_selpolygon][m_dirIndex][i].x;
		int posY = y + polygon[m_selpolygon][m_dirIndex][i].y;

		if (posX >= HEIGHT || posX >= WIDTH || posY <= 0 || posY <= 0)
			return false;

		if (m_GameTable[posY][posX] == 0)
			++count;
	}
	if (count == 4)
		return true;

	return false;

}
void Tetris::endGame(HWND hwnd) {
	TCHAR text[100];
	wsprintf(text, L"Game Over\nYour Score = %d점\n다시하시겠습니까?", m_GameScore);
	for (int i = 1;i < WIDTH - 2;i++) {
		if (m_GameTable[2][i] != 0) {
			if (MessageBox(hwnd, text, L"Game Over", MB_YESNO | MB_ICONQUESTION) == IDYES){
				InitData();
				RemoveKey(KEY_SPACE);
			}
			else
				DestroyWindow(hwnd);
		}
	}
}
void Tetris::CheckLevel() {
	if (m_GameScore > 100 && m_GameScore <= 300) {
		m_GameLevel = 2;
		m_gameSpeed = 400;
		m_prevGameSpeed = 400;
		return;
	}
	else if (m_GameScore > 300 && m_GameScore <= 600) {
		m_GameLevel = 3;
		m_gameSpeed = 300;
		m_prevGameSpeed = 300;
		return;
	}
	else if (m_GameScore > 600 && m_GameScore <= 1200) {
		m_GameLevel = 4;
		m_gameSpeed = 200;
		m_prevGameSpeed = 200;
		return;
	}
	else if (m_GameScore > 1500) {
		m_GameLevel = 5;
		m_gameSpeed = 100;
		m_prevGameSpeed = 100;
		return;
	}
}