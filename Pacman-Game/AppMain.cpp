#include "AppMain.h"

enum GAMESTATE
{
	GAME = 0,
	MENU = 1,
	SPLASH = 2,
	PROTOTYPE = 3,
	LOADING = 4,
	GAMETRANSITION = 5
};
int pGameState = MENU;

AppMain::AppMain()
{

}


AppMain::~AppMain()
{

}

bool AppMain::Initialize(HWND* _hWnd, HINSTANCE _hInstance)
{
	//d3dManager = new D3DManager();

	//if ( FAILED ( d3dManager->Initialize(_hWnd, _hInstance, cfg) ) )
	//	return print->fatalError(*_hWnd, "D3DManager failed to initialize");

	//pD3DDevice = d3dManager->pD3DDevice;

	return true;
}

void AppMain::GameTransition()
{
	//isInGame = true;
	//pGameState = LOADING;
	//currentLevel = currentLevel + 1;//(currentLevel + 1) % (levels.size());

	//if (currentLevel < levels.size())
	//	screens[LOADING]->Load(levels[currentLevel]);
	//else
	//{
	//	stringstream get;
	//	get << totScore;
	//	ss->gui->setHeadMsg(0, get.str());
	//	currentLevel = -1;
	//	pGameState = 2;
	//	isInGame = false;
	//}
}

void AppMain::Run()
{
	//pD3DDevice->ClearRenderTargetView( d3dManager->pRenderTargetView, D3DXCOLOR(0.0, 0.0, 0.0, 0.0) );

	//switch(pGameState)
	//{
	//case GAME:
	//	screens[GAME]->Update();
	//	screens[GAME]->Draw();
	//	break;
	//case MENU:
	//	screens[MENU]->Update();
	//	screens[MENU]->Draw();
	//	break;
	//case SPLASH:
	//	screens[SPLASH]->Update();
	//	screens[SPLASH]->Draw();
	//	break;
	//case PROTOTYPE:
	//	screens[PROTOTYPE]->Update();
	//	screens[PROTOTYPE]->Draw();
	//	break;
	//case LOADING:
	//	screens[LOADING]->Update();
	//	screens[LOADING]->Draw();
	//	break;
	//case GAMETRANSITION:
	//	GameTransition();
	//	break;
	//}

	//d3dManager->pSwapChain->Present(1,0);
}