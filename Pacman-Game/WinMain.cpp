#include <windows.h>
#include <tchar.h>

#include "Game.h"

int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	Pacman::Game game(hInstance);

	// Main message loop
	MSG msg = {0};
	while (WM_QUIT != msg.message)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}

		game.update(0);
	}

	return (int) msg.wParam;
}
