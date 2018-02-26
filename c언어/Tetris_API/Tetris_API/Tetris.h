#pragma once
class Tetris
{
private:
	// ���� ��ġ
	const int m_startPos = 10;

	// ������ ����
	const int m_PolygonCount = 7;

	int m_tableSize;
	bool m_isEnd;

	// ��Ҹ� �����ϱ� ���� �������� �����͸� ���մϴ�.
	int m_GameTable[20][12];
	int **m_pCheckTable;

	// �� �������� ��½�Ű�� ���� ��������Դϴ�.
	Block* m_pBlock;

	// ����� ���� ��ġ
	POS m_Pos;
	//���� ����
	int m_Nextpolygon;
	// ���õ� ����
	int m_selpolygon;
	// ���� ����
	int m_GameLevel;
	// ������ ȸ����
	int m_dirIndex;

	// Ű �� ó��
	int m_Key;

	// ���� �ð�
	DWORD m_prevTime;

	// ���� ���ǵ�
	DWORD m_gameSpeed;

	// ���� ���ӽ��ǵ�
	DWORD m_prevGameSpeed;

	// ����� ���� ���� �ð�
	DWORD m_prevDownTime;

	// Ű�� ���� �̵� ���ǵ� ��
	DWORD m_KeySpeed;

	DWORD m_GameSpeed;

	int m_GameScore;
	// Ű�� �Է��� �� �ִ°��� ���� ���°�
	bool m_KeyState;

public:
	Tetris();
	~Tetris();

public:

	void InitData();
	void LoadData(TCHAR* path);
	void DrawTable(HDC hdc);
	void DrawPolygon(HDC hdc);
	void DrawPolygon(HDC hdc, int x, int y);
	bool CalculatePositionFall(int x, int y);


	void Reset();
	void Input();
	void Update();

	void KeyUpdate();
	void MoveDown();

	void AddKey(int key);
	void RemoveKey(int key);

	void FixBlock();

	bool CheckMoving(float x, float y, int currRot);
	void EraseLine();
	void endGame(HWND hwnd);
	void DrawNextPolygon(HDC hdc);
	void CheckLevel();
};

