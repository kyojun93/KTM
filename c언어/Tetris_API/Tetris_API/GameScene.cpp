#include "stdafx.h"
#include "BaseScene.h"
#include "Block.h"
#include "Tetris.h"
#include "GameScene.h"


GameScene::GameScene()
{

}


GameScene::~GameScene()
{
}

void GameScene::Input()
{
	m_tetris.Input();
}

void GameScene::Update()
{
	m_tetris.Update();
	m_tetris.CheckLevel();
}
void GameScene::Render(HDC hdc, HWND hwnd)
{
	m_tetris.endGame(hwnd);
	m_tetris.DrawTable(hdc);
	m_tetris.DrawPolygon(hdc);
	m_tetris.DrawNextPolygon(hdc);
}
void GameScene::Enter()
{

}
void GameScene::Exit()
{

}
void GameScene::Reset() {
	m_tetris.InitData();
	m_tetris.Reset();
}