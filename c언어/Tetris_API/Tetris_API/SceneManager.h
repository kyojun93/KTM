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

	// ������ �ڵ�
	HWND m_hWnd;

	// �ĸ� dc
	HDC		m_BackDC;

	// �ĸ� dc�� ����� ��Ʈ��
	HBITMAP m_backBitmap;

	HBRUSH m_brush;

	// ������ ������ ���� �ֱ� ���� ����
	RECT m_rect;

	std::map< int, BaseScene *> m_SceneMap;

	int m_currScene;



private:
	SceneManager();
public:
	~SceneManager();

public:
	// �ʱ�ȭ �Լ�
	void Init();

	// ������ �Լ�.
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

