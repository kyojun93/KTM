// SceneProject.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <map>
#include "TSingleton.h"
#include "BaseScene.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "Block.h"
#include "Tetris.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Tetris_API.h"
#include "ButtonSceneManager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hWnd2;						// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL isGame = true;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TETRISAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRISAPI));

	MSG msg;

	ZeroMemory(&msg, sizeof(msg));

	SceneManager::GetInstance()->Add(SceneManager::LOGO, new LogoScene());
	SceneManager::GetInstance()->Add(SceneManager::TITLE, new TitleScene());
	SceneManager::GetInstance()->Add(SceneManager::GAME, new GameScene());
	SceneManager::GetInstance()->SetScene(SceneManager::LOGO);


	// 기본 메시지 루프입니다.
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SceneManager::GetInstance()->Input();
			SceneManager::GetInstance()->Update();
			SceneManager::GetInstance()->Render();
			if (SceneManager::GetInstance()->IsGameScene(SceneManager::GAME) && isGame) {
				ButtonSceneManager::GetInstance()->Render(hInst);
				isGame = false;
			}
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	HBRUSH m_brush = CreateSolidBrush(RGB(37, 235, 210));
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRISAPI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(m_brush);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND MainWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 450, 500, nullptr, nullptr, hInstance, nullptr);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_CHILD | WS_VISIBLE,
		CW_USEDEFAULT, 0, 450, 400, MainWindow, nullptr, hInstance, nullptr);

	SceneManager::GetInstance()->SetHwnd(hWnd);
	SceneManager::GetInstance()->Init();

	hWnd2 = CreateWindow(szWindowClass,NULL, WS_CHILD | WS_VISIBLE ,
		0, 400, 450, 100, MainWindow, nullptr, hInstance, NULL);
	ButtonSceneManager::GetInstance()->SetHwnd(hWnd2);
	ButtonSceneManager::GetInstance()->Init();

	if (!MainWindow)
	{
		return FALSE;
	}

	ShowWindow(MainWindow, nCmdShow);
	UpdateWindow(MainWindow);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1:
			if (MessageBox(hWnd, L"Game Reset?", L"Reset", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				SceneManager::GetInstance()->GameReset();
			}
			break;
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

