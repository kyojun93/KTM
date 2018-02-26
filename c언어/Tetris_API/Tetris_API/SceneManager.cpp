#include "stdafx.h"
#include <map>
#include "BaseScene.h"
#include "TSingleton.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	HDC hdc = GetDC(m_hWnd);

	m_BackDC = CreateCompatibleDC(hdc);

	m_brush = CreateSolidBrush(RGB(37, 235, 210));

	GetClientRect(m_hWnd, &m_rect);
	m_backBitmap = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom);

	SelectObject(m_BackDC, m_backBitmap);

	ReleaseDC(m_hWnd, hdc);

	m_currScene = -1;

}

void SceneManager::Add(SCENE scene, BaseScene * pScene)
{
	if (m_SceneMap.find(scene) == m_SceneMap.end())
	{
		m_SceneMap[scene] = pScene;
	}
}

void SceneManager::ChangeScene(SCENE nextScene)
{
	if (m_currScene == nextScene)
		return;
	if (m_SceneMap.find(nextScene) == m_SceneMap.end())
		return;

	m_SceneMap[m_currScene]->Exit();

	m_SceneMap[nextScene]->Enter();

	m_currScene = nextScene;
}


void SceneManager::Render()
{
	HDC frontDC = GetDC(m_hWnd);

	FillRect(m_BackDC, &m_rect, m_brush);

	if (m_SceneMap.find(m_currScene) != m_SceneMap.end())
	{
		m_SceneMap[m_currScene]->Render(m_BackDC, m_hWnd);
	}

	BitBlt(frontDC, 0, 0, m_rect.right, m_rect.bottom, m_BackDC, 0, 0, SRCCOPY);

	ReleaseDC(m_hWnd, frontDC);
}

void SceneManager::Input()
{
	if (m_SceneMap.find(m_currScene) != m_SceneMap.end())
		m_SceneMap[m_currScene]->Input();
}

void SceneManager::SetHwnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

void SceneManager::SetScene(SCENE scene)
{
	m_currScene = scene;
}

void SceneManager::Update()
{
	if (m_SceneMap.find(m_currScene) != m_SceneMap.end())
		m_SceneMap[m_currScene]->Update();
}
void SceneManager::GameReset() {
	if (m_SceneMap.find(m_currScene) != m_SceneMap.end())
		m_SceneMap[m_currScene]->Reset();
}
bool SceneManager::IsGameScene(SCENE scene) {
	 if (m_currScene == scene) {
		 return true;
	 }
	 return false;
}