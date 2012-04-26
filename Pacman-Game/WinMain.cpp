#pragma region Include Statements

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include "AppMain.h"

#pragma region Globals

AppMain		appMain;
HWND		hWnd;
int			windowWidth;
int			windowHeight;

static const std::string versionNumber =		" 0.01 Dev";
static const std::string appName =				"BTH Project: Pacman Reloaded" + versionNumber;

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY :	PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool initWindow(HWND &hWnd, HINSTANCE hInstance, int width, int height)
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= TEXT("FOOT");
	wcex.hIconSm		= 0;

	RegisterClassEx(&wcex);

	width = 1280;
	height = 720;

	// Set size and adjust window
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	// Create window
	hWnd = CreateWindow("FOOT",
		appName.c_str(),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);


	// handle creation failed
	if (!hWnd)
		return false;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	return true;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// Set up window
	if ( !initWindow (hWnd, hInstance, windowWidth, windowHeight) )
		return 0;

	// Set up d3dManager
	//if (appMain.Initialize(&hWnd, hInstance, &cfg) == false)
	//{
	//	return 0;
	//}

	// Main message loop

	MSG msg = {0};

	while (WM_QUIT != msg.message)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}		
		appMain.Run();
	}

	appMain.~AppMain();

	return (int)msg.wParam;
}