#include "stdafx.h"

#include "TitleScene.h"
#include "BaseScene.h"
#include "TSingleton.h"
#include <map>
#include "SceneManager.h"


TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{
}

void TitleScene::Input()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::GetInstance()->ChangeScene(SceneManager::GAME);
	}

}
void TitleScene::Update()
{

}
void TitleScene::Render(HDC hdc, HWND hwnd)
{
	m_background = (HBITMAP)LoadImage(NULL, TEXT("img/Title.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, m_background);
	BitBlt(hdc, 0, 0, 450, 300, memDC, 0, 0, SRCAND);
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
	SetBkColor(hdc, RGB(37, 235, 210));
	TextOut(hdc, 135, 300, TEXT("PRESS ENTER TO START"), lstrlen(TEXT("PRESS ENTER TO START")));
}
void TitleScene::Enter()
{

}
void TitleScene::Exit()
{

}
void TitleScene::Reset()
{

}
