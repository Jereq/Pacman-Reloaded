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

bool AppMain::Initialize(HWND* _hWnd)
{
	gManager = new dxManager();
	hW = _hWnd;

	if (!gManager->initialize(hW))
	{
		return false;
	}

	return true;
}

void AppMain::Run()
{
	//gManager->renderScene();
}