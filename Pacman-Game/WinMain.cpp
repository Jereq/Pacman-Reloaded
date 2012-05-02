#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include <vector>
using namespace std;

#include "camera.h"
#include "dxManager.h"
#include "InputManager.h"


HWND hWnd;
int windowWidth = 1280;	
int windowHeight = 720;

//directX manager
dxManager dx;
Camera* pCamera = new Camera();

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		//raw input handler
	case WM_INPUT:
		{
			HandleRawInput( hWnd, (HRAWINPUT&) lParam );
		}
		break;	

		// The user hit the close button, close the application
	case WM_DESTROY	:	PostQuitMessage(0);
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
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= TEXT("PacMan");
	wcex.hIconSm		= 0;
	RegisterClassEx(&wcex);

	//Resize the window
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	//create the window from the class defined above	
	hWnd = CreateWindow( (LPCSTR)"PacMan", 
		(LPCSTR)"Pacman - Reloaded",
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		rect.right - rect.left, 
		rect.bottom - rect.top, 
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	//window handle not created
	if (!hWnd) return false;

	//if window creation was successful
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	return true;
}

int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// Set up the application window
	if ( !initWindow(hWnd, hInstance, windowWidth, windowHeight)) return 0;

	//set up input devices
	RegisterInputDevices(hWnd);

	//set up scene camera properties
	pCamera->setPerspectiveProjectionLH( 45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f );
	pCamera->setPositionAndView( 0.0f, 1.0f, 0.0f, 0.0f, 0.0f );
	pCamera->setMovementSpeed(10);

	//set up directx manager
	if ( !dx.initialize(&hWnd) ) return 0;

	// Main message loop
	MSG msg = {0};
	while (WM_QUIT != msg.message)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}	

		dx.renderScene();
		pCamera->update();
	}

	return (int) msg.wParam;
}
