#include "stdafx.h"
#include <map>
#include "BaseScene.h"
#include "TSingleton.h"
#include "ButtonSceneManager.h"
ButtonSceneManager::ButtonSceneManager()
{

}


ButtonSceneManager::~ButtonSceneManager()
{
}

void ButtonSceneManager::Init()
{
	HDC hdc = GetDC(m_hWnd);
	m_BackDC = CreateCompatibleDC(hdc);

	m_brush = CreateSolidBrush(RGB(37, 235, 210));

	GetClientRect(m_hWnd, &m_rect);

	m_backBitmap = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom);

	SelectObject(m_BackDC, m_backBitmap);

	ReleaseDC(m_hWnd, hdc);
}

void ButtonSceneManager::Render(HINSTANCE hInst)
{
	HDC frontDC = GetDC(m_hWnd);
	FillRect(m_BackDC, &m_rect, m_brush);
		CreateWindow(L"button", L"RESET", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			300, 0, 100, 50, m_hWnd, (HMENU)1, hInst, NULL);
	BitBlt(frontDC, 0, 0, m_rect.right, m_rect.bottom, m_BackDC, 0, 0, SRCCOPY);

	ReleaseDC(m_hWnd, frontDC);
	
}


void ButtonSceneManager::SetHwnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

