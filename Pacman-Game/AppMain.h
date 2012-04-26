#ifndef APPMAIN
#define APPMAIN

#pragma region Includes

#include <d3d10.h>
#include <D3DX10.h>
#include <vector>
//#include "D3DManager.h"

#pragma endregion

class AppMain
{
public:
	AppMain();
	~AppMain();

public:
	//D3DManager*				d3dManager;
	bool					Initialize(HWND* _hWnd, HINSTANCE _hInstance);
	void					Run();

private:
	//std::vector<Screen*>	screens;
	ID3D10Device*			pD3DDevice;
	bool					selfDestruct;

	void GameTransition();
};

#endif
