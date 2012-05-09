#include "Game.h"

#include "InputManager.h"
#include "Resources/Context.h"
#include "Resources/MTAModel.h"

#include "GameplayFoundations/Grid.h"
#include "GameplayFoundations/Events/KeyboardKeyEvent.h"
using GameplayFoundations::Events::Event;
using GameplayFoundations::Events::KeyboardKeyEvent;

namespace Pacman
{
	LRESULT Game::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		HID* m_HID = HID::getInstance(hWnd);

		m_HID->input(message, wParam);

		switch (message) 
		{
			//raw input handler
	/*	case WM_INPUT:
			{
				HandleRawInput( hWnd, (HRAWINPUT&) lParam );
			}
			break;*/	

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
		: windowWidth(1024), windowHeight(768)
	{
		bool result = initWindow(hInstance);
		assert(result);

		//set up input devices
		result = RegisterInputDevices(hWnd);
		assert(result);

		gManager = new Graphics::dxManager();

		//Player* player = new Player(D3DXVECTOR3(0,0,0));
		

		result = gManager->initialize(&hWnd);
		assert(result);

		rm.reset(new Resources::ResourceManager());
		rm->startup(gManager->pD3DDevice);

		gManager->initializeObjects();

		sm.reset(new Sound::SoundManager());
		sm->startup();

		Camera* camera = new Camera();
		
		m_HID = HID::getInstance(hWnd);
		col = new Collision();

		//set up scene camera properties
		camera->setPerspectiveProjectionLH( 45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f );
		camera->setPositionAndView( -6.0f, 15.f, -6.0f, 45.0f, 40.0f );

		gManager->setActiveCamera(camera);

		Resources::Context context(rm);
		Resources::MapTexture::ptr test = context.getMapTexture("Maps/test.png");

		currentGrid.reset(new GameplayFoundations::Grid(test));
		levelMesh = currentGrid->createMesh(gManager->pD3DDevice);

		levelTex = rm->loadTexture("Textures/mapTex.png");

		pacman = rm->loadMTAModel("models/pacman.mta");
		player = new Player(pacman, D3DXVECTOR3(0,0,0));
		player->init();

		fd = new Food(food, D3DXVECTOR3(0,0,0), NORMAL);
		fd->init();

	}

	Game::~Game()
	{
		rm->shutdown();
		sm->shutdown();
	}

	void Game::update(float deltaTime)
	{

		if(m_HID->pressKeyOnce(VK_ESCAPE))
		{
			PostQuitMessage(0);
		}
		
		while (!eventQueue.isEmpty())
		{
			Event::ptr ev = eventQueue.popEvent();

			switch (ev->eventType)
			{
			case Event::KEYBOARD_KEY_EVENT:
				exit(0);
				break;
			}
		}

		player->update(deltaTime);

		Camera* camera = gManager->getActiveCamera();

		camera->update();
		sm->update(camera->getCameraPosition(),
			camera->getCameraForward(),
			camera->getCameraUp());

		D3DXMATRIX tmp;
		D3DXMatrixIdentity(&tmp);

	/*	static float time = 0;
		}*/


		player->draw(gManager);
		fd->draw(gManager);

		/*if(col->checkCollision(player->getPos(), player->getMinCorner(), player->getMaxCorner(),
			fd->getPos(), fd->getMinCorner(), fd->getMaxCorner()) == true)*/
		if(col->checkCollision(player, fd) == true)
		{
			PostQuitMessage(0);

		gManager->AddStaticObject(Graphics::staticObject(levelMesh, levelTex, tmp));
		//gManager->AddDynamicObject(Graphics::dynamicObject(pacman, time, 0, subA, tmp));

		gManager->renderScene();
	}
}