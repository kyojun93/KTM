#pragma once
class ButtonSceneManager : public TSingleton<ButtonSceneManager>
{
	friend TSingleton<ButtonSceneManager>;

public:

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



private:
	ButtonSceneManager();
public:
	~ButtonSceneManager();

public:
	// �ʱ�ȭ �Լ�
	void Init();

	// ������ �Լ�.
	void Render(HINSTANCE hInst);

	void SetHwnd(HWND hWnd);


};

