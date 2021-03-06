#include "Game.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

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

		sm = Sound::SoundManager::getInstance();
		sm->startup();

		Camera* camera = new Camera();
		
		m_HID = HID::getInstance(hWnd);
		col = new GameplayFoundations::Collision();

		//set up scene camera properties
		camera->setPerspectiveProjectionLH( 45.0f, (float)windowWidth / windowHeight, 0.1f, 200.0f );		

		gManager->setActiveCamera(camera);

		Resources::Context context(rm);
		Resources::MapTexture::ptr test = context.getMapTexture("Maps/map1.png");

		currentGrid.reset(new GameplayFoundations::Grid(test));
		levelMesh = currentGrid->createMesh(gManager->pD3DDevice);

		std::vector<GameplayFoundations::CellIndex> testPath;
		currentGrid->findPath(GameplayFoundations::CellIndex(1, 78), currentGrid->getStartPos(), testPath);

		levelTex = rm->loadTexture("Textures/mapTex.png");

		int t = levelMesh->GetVertexCount();
		int f = levelMesh->GetFaceCount();

		pacman = rm->loadMTAModel("models/pacman.mta");
		foodmodel = rm->loadMTModel("models/food.mt");
		gPointModel = rm->loadMTAModel("models/Ghostblue.mta");
		gRandomModel = rm->loadMTAModel("models/Ghostorange.mta");
		gHuntModel = rm->loadMTAModel("models/Ghostred.mta");

		player = new Actors::Player(pacman, currentGrid->getStartPos(), currentGrid);
		player->init();

		std::vector<GameplayFoundations::CellIndex> ghostPos(currentGrid->getGhostStartPos());

		ghosts.push_back(new Actors::PointGhost(gPointModel, ghostPos[0], currentGrid));
		ghosts.push_back(new Actors::RandomGhost(gRandomModel, ghostPos[1], currentGrid));
		ghosts.push_back(new Actors::HuntGhost(gHuntModel, ghostPos[2], currentGrid));
		for(UINT i = 0; i < ghosts.size(); i++)
		{
			ghosts[i]->init(player->getToCell());
		}

		std::vector<GameplayFoundations::CellIndex> const& foodPos = currentGrid->getFoodPos();
		size_t numFood = static_cast<size_t>(foodPos.size() * 0.1f);

		boost::random::mt19937 gen;

		for(UINT i = 0; i < foodPos.size(); i++)
		{
			boost::random::uniform_int_distribution<size_t> dist(0U, foodPos.size() - i - 1U);
			if (dist(gen) <= numFood)
			{
				numFood--;
				Actors::Food* f = new Actors::Food(foodmodel, foodPos[i], Actors::NORMAL);
				f->init();
				food.push_back(f);
			}
		}
	}

	Game::~Game()
	{
		rm->shutdown();
		sm->shutdown();
	}

	void Game::update(float deltaTime)
	{
		static float d = 0.0f;
		d += deltaTime * 3.f;


	
		if(m_HID->pressKeyOnce(VK_ESCAPE))
		{
			PostQuitMessage(0);
		}
		if(m_HID->pressKey('W'))
		{
			player->setDirection(DIR_UP);
		}
		if(m_HID->pressKey('S'))
		{
			player->setDirection(DIR_DOWN);
		}
		if(m_HID->pressKey('A'))
		{
			player->setDirection(DIR_LEFT);
		}
		if(m_HID->pressKey('D'))
		{
			player->setDirection(DIR_RIGHT);
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

		const static float pitch = 80.0f;
		const static float heading = 0.0f;
		const static float height = 20.f;

		camera->setPositionAndView(player->getPos().x, player->getPos().y + height, 
			player->getPos().z - (height / (float)tan(D3DXToRadian(pitch))), heading, pitch );

		camera->update();
		sm->update(camera->getCameraPosition(),
			camera->getCameraForward(),
			camera->getCameraUp());

		D3DXMATRIX tmp;
		D3DXMatrixIdentity(&tmp);

		player->draw(gManager);

		bool t = true;

		for(UINT i = 0; i < ghosts.size(); i++)
		{
			ghosts[i]->update(deltaTime, player->getToCell());

			if(col->checkCollision(player, ghosts[i]))
			{
				if(player->beEatingOrNot())
				{
					ghosts[i]->changeState(DEAD);					
				}
				else
				{
					t = false;
				}
			}

			ghosts[i]->draw(gManager);
		}

		if(!t)
		{
			PostQuitMessage(0);
		}


		for(UINT i = 0; i < food.size(); i++)
		{
			food[i]->update(deltaTime);
			food[i]->draw(gManager);
			if(col->checkCollision(player, food[i]))
			{
				food.erase(food.begin() + i);
				i--;
			}
		}		

		gManager->AddStaticObject(Graphics::staticObject(levelMesh, levelTex, tmp));
		gManager->renderScene();
	}
}