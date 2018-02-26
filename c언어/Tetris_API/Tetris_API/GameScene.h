#pragma once

class GameScene : public BaseScene
{
private:
	Tetris m_tetris;
public:
	GameScene();
	virtual ~GameScene();

public:
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hdc, HWND hwnd);
	virtual void Enter();
	virtual void Exit();
	virtual void Reset();
};

