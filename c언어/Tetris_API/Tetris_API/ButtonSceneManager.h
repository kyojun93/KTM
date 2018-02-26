#pragma once
class ButtonSceneManager : public TSingleton<ButtonSceneManager>
{
	friend TSingleton<ButtonSceneManager>;

public:

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



private:
	ButtonSceneManager();
public:
	~ButtonSceneManager();

public:
	// 초기화 함수
	void Init();

	// 렌더링 함수.
	void Render(HINSTANCE hInst);

	void SetHwnd(HWND hWnd);


};

