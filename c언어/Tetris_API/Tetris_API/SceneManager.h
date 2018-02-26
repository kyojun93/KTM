#pragma once
class SceneManager : public TSingleton<SceneManager>
{
	friend TSingleton<SceneManager>;

public:
	typedef enum SceneType
	{
		LOGO,
		TITLE,
		GAME

	}SCENE;

private:

	// 윈도우 핸들
	HWND m_hWnd;

	// 후면 dc
	HDC		m_BackDC;

	// 후면 dc에 연결될 비트맵
	HBITMAP m_backBitmap;

	HBRUSH m_brush;

	// 윈도우 영역을 갖고 있기 위한 변수
	RECT m_rect;

	std::map< int, BaseScene *> m_SceneMap;

	int m_currScene;



private:
	SceneManager();
public:
	~SceneManager();

public:
	// 초기화 함수
	void Init();

	// 렌더링 함수.
	void Render();

	void Input();

	void Update();

	void SetHwnd(HWND hWnd);

	void Add(SCENE scene, BaseScene * pScene);

	void ChangeScene(SCENE nextScene);

	void SetScene(SCENE scene);

	void GameReset();

	bool IsGameScene(SCENE scene);
};

