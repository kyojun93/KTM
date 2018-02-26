#pragma once
class Tetris
{
private:
	// 시작 위치
	const int m_startPos = 10;

	// 도형의 개수
	const int m_PolygonCount = 7;

	int m_tableSize;
	bool m_isEnd;

	// 요소를 구분하기 위한 실질적인 데이터를 뜻합니다.
	int m_GameTable[20][12];
	int **m_pCheckTable;

	// 각 도형들을 출력시키기 위한 구성요소입니다.
	Block* m_pBlock;

	// 블록의 현재 위치
	POS m_Pos;
	//다음 도형
	int m_Nextpolygon;
	// 선택된 도형
	int m_selpolygon;
	// 게임 레벨
	int m_GameLevel;
	// 도형의 회전값
	int m_dirIndex;

	// 키 값 처리
	int m_Key;

	// 이전 시간
	DWORD m_prevTime;

	// 게임 스피드
	DWORD m_gameSpeed;

	// 이전 게임스피드
	DWORD m_prevGameSpeed;

	// 블록을 내린 이전 시간
	DWORD m_prevDownTime;

	// 키를 통한 이동 스피드 값
	DWORD m_KeySpeed;

	DWORD m_GameSpeed;

	int m_GameScore;
	// 키를 입력할 수 있는가에 대한 상태값
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

