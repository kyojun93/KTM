#include "stdafx.h"
#include <map>

#include "TSingleton.h"
#include "LogoScene.h"
#include "SceneManager.h"

LogoScene::LogoScene()
{
	m_startTime = timeGetTime();
}


LogoScene::~LogoScene()
{

}

void LogoScene::Input()
{


}
void LogoScene::Update()
{
	DWORD elapsedTime = timeGetTime() - m_startTime;
	if (elapsedTime >= 2000) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::TITLE);
	}
}
void LogoScene::Render(HDC hdc, HWND hwnd)
{
	/*SetBkColor(hdc, RGB(37, 235, 210));
	TextOut(hdc, 150, 150, TEXT("LogoScene::Render()"), lstrlen(TEXT("LogoScene::Render()")));*/
	m_background = (HBITMAP)LoadImage(NULL, TEXT("img/Logo.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, m_background);
	BitBlt(hdc, 0, 0, 450, 400, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
}
void LogoScene::Enter()
{

}
void LogoScene::Exit()
{

}
void LogoScene::Reset()
{

}