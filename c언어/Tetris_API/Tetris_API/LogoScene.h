#pragma once
#include "BaseScene.h"
class LogoScene : public BaseScene
{
private:
	DWORD m_startTime;
	HBITMAP m_background;
public:
	LogoScene();
	virtual ~LogoScene();

public:
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hdc, HWND hwnd);
	virtual void Enter();
	virtual void Exit();
	virtual void Reset();
};

