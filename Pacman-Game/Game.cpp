#include "Game.h"

#include "InputManager.h"
#include "ResourceHandling/Texture.h"

namespace Pacman
{
	LRESULT Game::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

	bool Game::initWindow(HINSTANCE _hInstance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC)wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= _hInstance;
		wcex.hIcon			= 0;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= TEXT("PacMan");
		wcex.hIconSm		= 0;
		RegisterClassEx(&wcex);

		//Resize the window
		RECT rect = { 0, 0, windowWidth, windowHeight };
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
			_hInstance, 
			NULL);

		//window handle not created
		if (!hWnd) return false;

		//if window creation was successful
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
		return true;
	}

	Game::Game(HINSTANCE hInstance)
		: windowWidth(1280), windowHeight(720)
	{
		bool result = initWindow(hInstance);
		assert(result);

		//set up input devices
		result = RegisterInputDevices(hWnd);
		assert(result);

		gManager = new dxManager();

		result = gManager->initialize(&hWnd);
		assert(result);

		rm.startup(gManager->pD3DDevice);

		Camera* camera = new Camera();

		//set up scene camera properties
		camera->setPerspectiveProjectionLH( 45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f );
		camera->setPositionAndView( 0.0f, 1.0f, 0.0f, 0.0f, 0.0f );
		camera->setMovementSpeed(10);

		gManager->setActiveCamera(camera);

		ResourceHandling::Texture::ptr test = rm.loadMapTexture("Terrain_texture.jpg");
		std::vector<D3DXCOLOR> cols = test->getColorVector();
	}

	Game::~Game()
	{
		rm.shutdown();
		SoundManager::release();
	}

	void Game::update(float deltaTime)
	{
		Camera* camera = gManager->getActiveCamera();
		
		camera->update();
		sm.update(camera->getCameraPosition(),
			camera->getCameraForward(),
			camera->getCameraUp());
		
		gManager->renderScene();
	}
}