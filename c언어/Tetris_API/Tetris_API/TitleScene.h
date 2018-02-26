#pragma once
#include "BaseScene.h"
class TitleScene :public BaseScene
{
public:
	HBITMAP m_background;
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hdc, HWND hwnd);
	virtual void Enter();
	virtual void Exit();
	virtual void Reset();
};

