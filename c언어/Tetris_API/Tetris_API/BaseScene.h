#pragma once

class BaseScene
{
public:
	virtual ~BaseScene() {}
public:
	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc, HWND hwnd) = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Reset() = 0;
};