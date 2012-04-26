#ifndef APPMAIN
#define APPMAIN

#pragma region Includes

#include <d3d10.h>
#include <D3DX10.h>
#include <vector>
#include <Windows.h>
#include "dxManager.h"

#pragma endregion

class AppMain
{
public:

	AppMain();
	~AppMain();

	bool					Initialize(HWND* _hWnd);
	void					Run();

private:

	ID3D10Device*			pD3DDevice;
	bool					selfDestruct;
	HWND*					hW;
	dxManager*				gManager;


	void GameTransition();
};

#endif
