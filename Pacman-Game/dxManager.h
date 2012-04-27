#ifndef DXMANAGER
#define DXMANAGER

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>
#include <string>

//create a basic vertex container
struct vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR4 color;
	D3DXVECTOR2 texCoord;

	vertex( D3DXVECTOR3 pos, D3DXVECTOR4 color )
	{
		pos = pos;
		color = color;
	}

	vertex( D3DXVECTOR3 pos, D3DXVECTOR4 color, D3DXVECTOR2 texCoord )
	{
		pos = pos;
		color = color;
		texCoord = texCoord;
	}
};

struct camera
{
	D3DXVECTOR3 up;
	D3DXVECTOR3 eye;
	D3DXVECTOR3 at;
 
	camera()
	{
		up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		eye = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
		at = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}
};

const D3D10_INPUT_ELEMENT_DESC layout[] = 
{	
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

class dxManager
{
private:

	HWND*						hWnd;
	
	//device vars
	ID3D10Device*				pD3DDevice;
	IDXGISwapChain*				pSwapChain;
	ID3D10RenderTargetView*		pRenderTargetView;
	D3D10_VIEWPORT				viewPort;
	ID3D10RasterizerState*		pRS;

	//Texture buffers
	ID3D10Texture2D*			pBackBuffer;

	//input layout and vertex buffer
	ID3D10Buffer*				pVertexBuffer;
	ID3D10InputLayout*			pVertexLayout;

	//effects and techniques
	ID3D10Effect*				pBasicEffect;
	ID3D10EffectTechnique*		pBasicTechnique;

	//Desc
	DXGI_SWAP_CHAIN_DESC		swapChainDesc;
	D3D10_PASS_DESC				PassDesc;
	D3D10_BUFFER_DESC			bd;
	D3D10_RASTERIZER_DESC		rasterizerState;
	D3D10_TECHNIQUE_DESC		techDesc;

	//effect variable pointers
	ID3D10EffectMatrixVariable* pViewMatrixEffectVariable;
	ID3D10EffectMatrixVariable* pProjectionMatrixEffectVariable;
	ID3D10EffectMatrixVariable* pWorldMatrixEffectVariable;
	
	//projection and view matrices
	D3DXMATRIX                  viewMatrix;
	D3DXMATRIX                  projectionMatrix;

	//Texture storage
	std::vector<ID3D10ShaderResourceView*> textureSRV;
	ID3D10EffectShaderResourceVariable* pTextureSR;
	int textureIndex;

	camera cam;

	const static UINT numElements = sizeof( layout ) / sizeof( layout[0] );
	const static UINT numVertices = 4;
	const static UINT stride = sizeof( vertex );
	const static UINT offset = 0;

	bool result;


public:

	//constructor and destructor
	dxManager();
	~dxManager();

	//initialize directx device
	bool initialize(HWND*);	





	//renderScene
	void renderScene();	

private:

	//fatal error handler
	bool fatalError(LPCSTR msg); 

	void CreateViewPort( UINT width, UINT height );
	bool CreateVertexBuffer();
	bool CreateInputLayout();
	bool CreateEffect();
	bool CreateSwapChain();
	bool createSwapChainAndDevice( UINT width, UINT height );
	bool createRenderTargets();
	void CreateAndSetRasterizer();
	bool loadTextures();
};

#endif