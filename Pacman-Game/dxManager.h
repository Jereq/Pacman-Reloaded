#ifndef DXMANAGER
#define DXMANAGER

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

class dxManager
{
private:

	HWND*						hWnd;
	ID3D10Device*				pD3DDevice;
	IDXGISwapChain*				pSwapChain;
	ID3D10RenderTargetView*		pRenderTargetView;
	D3D10_VIEWPORT				viewPort;

	D3DXMATRIX                  viewMatrix;
	D3DXMATRIX                  projectionMatrix;

public:

	dxManager();
	~dxManager();
	bool initialize(HWND*);	
	void renderScene();	

private:

	bool fatalError(LPCSTR msg); 
};

#endif