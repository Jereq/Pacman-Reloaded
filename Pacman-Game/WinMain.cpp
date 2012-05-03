#include <windows.h>
#include <tchar.h>

#include "Game.h"
#include "GameplayFoundations\Timer.h"

int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	Pacman::Game game(hInstance);

	Timer* m_timer = new Timer();
	m_timer->reset();

	// Main message loop
	MSG msg = {0};
	while (WM_QUIT != msg.message)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}

		m_timer->tick();

		game.update(m_timer->getDeltaTime());
	}

	return (int) msg.wParam;
}
