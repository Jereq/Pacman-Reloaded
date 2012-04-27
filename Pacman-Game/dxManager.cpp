#include "dxManager.h"

dxManager::dxManager() : pD3DDevice(NULL), pSwapChain(NULL), pRenderTargetView(NULL), pVertexBuffer(0), pVertexLayout(0), pBasicEffect(0), pRS(0)
{
	result = true;
}

dxManager::~dxManager()
{
	if ( pRenderTargetView ) pRenderTargetView->Release();
	if ( pSwapChain ) pSwapChain->Release();
	if ( pD3DDevice ) pD3DDevice->Release();
	if ( pVertexBuffer ) pVertexBuffer->Release();
	if ( pVertexLayout ) pVertexLayout->Release();
	if ( pRS ) pRS->Release();
	if ( pBasicEffect ) pBasicEffect->Release();
}

bool dxManager::initialize( HWND* hW )
{
	//window handle
	hWnd = hW;
	
	//get window dimensions
	RECT rc;
    GetClientRect( *hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

	SetUpSwapChainDesc(width, height);

	result = CreateSwapChain();
	result = CreateEffect();

	pBasicTechnique = pBasicEffect->GetTechniqueByName("SimpleRender");
	
	//create matrix effect pointers
	pViewMatrixEffectVariable = pBasicEffect->GetVariableByName( "View" )->AsMatrix();
	pProjectionMatrixEffectVariable = pBasicEffect->GetVariableByName( "Projection" )->AsMatrix();
	pWorldMatrixEffectVariable = pBasicEffect->GetVariableByName( "World" )->AsMatrix();

	result = CreateInputLayout();

	pD3DDevice->IASetInputLayout( pVertexLayout );

	result = CreateVertexBuffer();

	pD3DDevice->IASetVertexBuffers( 0, 1, &pVertexBuffer, &stride, &offset );	
	
	CreateViewPort(width, height);	

	CreateAndSetRasterizer();	
		
	result = GetBackBuffer();

	result = CreateRenderTargetView();
	
	pBackBuffer->Release();

	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	D3DXMatrixLookAtLH(&viewMatrix, &cam.eye, &cam.at, &cam.up);
		
    D3DXMatrixPerspectiveFovLH(&projectionMatrix, (float)D3DX_PI * 0.5f, (float)width/(float)height, 0.1f, 100.0f);

	return result;
}

void dxManager::renderScene()
{
	//clear scene
	pD3DDevice->ClearRenderTargetView( pRenderTargetView, D3DXCOLOR(0,0,0,0) );

	//create world matrix
	static float r;
	D3DXMATRIX w;
	D3DXMatrixIdentity(&w);
	D3DXMatrixRotationY(&w, r); 
	r += 0.001f;

	//set effect matrices
	pWorldMatrixEffectVariable->SetMatrix(w);
	pViewMatrixEffectVariable->SetMatrix(viewMatrix);
	pProjectionMatrixEffectVariable->SetMatrix(projectionMatrix);

	//fill vertex buffer with vertices
		
	vertex* v = NULL;	

	//lock vertex buffer for CPU use
	pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &v );
	
	v[0] = vertex( D3DXVECTOR3(-1,-1,0), D3DXVECTOR4(1,0,0,1) );
	v[1] = vertex( D3DXVECTOR3(0,1,0), D3DXVECTOR4(0,1,0,1) );
	v[2] = vertex( D3DXVECTOR3(1,-1,0), D3DXVECTOR4(0,0,1,1) );
	v[3] = vertex( D3DXVECTOR3(1,1,0), D3DXVECTOR4(1,0,1,1) );

	pVertexBuffer->Unmap();

	// Set primitive topology 
	pD3DDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//get technique desc
	
	pBasicTechnique->GetDesc( &techDesc );
	
	for( UINT p = 0; p < techDesc.Passes; ++p )
	{
		//apply technique
		pBasicTechnique->GetPassByIndex( p )->Apply( 0 );
				
		//draw
		pD3DDevice->Draw( numVertices, 0 );
	}

	//flip buffers
	pSwapChain->Present(0,0);
}

void dxManager::SetUpSwapChainDesc( UINT width, UINT height )
{	
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//set buffer dimensions and format
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;

	//set refresh rate
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	//sampling settings
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;

	//output window handle
	swapChainDesc.OutputWindow = *hWnd;
	swapChainDesc.Windowed = true;
}
bool dxManager::CreateSwapChain()
{
	if ( FAILED( D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, 
				 &swapChainDesc, &pSwapChain, &pD3DDevice ) ) ) 
	{
		return fatalError("D3D device creation failed");
	}
	
	return true;
}
bool dxManager::CreateEffect()
{
	if ( FAILED( D3DX10CreateEffectFromFile("effects.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 
				 0, pD3DDevice,	NULL, NULL,	&pBasicEffect, NULL, NULL ) ) ) 
	{
		return fatalError("Could not load effect file!");
	}

	return true;
}
bool dxManager::CreateInputLayout()
{	
	pBasicTechnique->GetPassByIndex( 0 )->GetDesc( &PassDesc );

	if ( FAILED( pD3DDevice->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature,
				 PassDesc.IAInputSignatureSize, &pVertexLayout ) ) ) 
	{
		return fatalError("Could not create Input Layout!");
	}

	return true;
}
bool dxManager::CreateVertexBuffer()
{
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( vertex ) * numVertices;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	if ( FAILED( pD3DDevice->CreateBuffer( &bd, NULL, &pVertexBuffer ) ) ) 
	{
		return fatalError("Could not create vertex buffer!");
	}

	return true;
}
void dxManager::CreateViewPort( UINT width, UINT height )
{
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	pD3DDevice->RSSetViewports(1, &viewPort);
}
void dxManager::CreateAndSetRasterizer()
{
	rasterizerState.CullMode = D3D10_CULL_NONE;
	rasterizerState.FillMode = D3D10_FILL_SOLID;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = false;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = true;		

	pD3DDevice->CreateRasterizerState( &rasterizerState, &pRS);
	pD3DDevice->RSSetState(pRS);
}
bool dxManager::GetBackBuffer()
{
	if ( FAILED( pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer) ) ) 
	{
		return fatalError("Could not get back buffer");
	}

	return true;
}
bool dxManager::CreateRenderTargetView()
{
	if ( FAILED( pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView) ) ) 
	{
		return fatalError("Could not create render target view");
	}

	return true;
}

bool dxManager::fatalError(LPCSTR msg)
{
	MessageBox(*hWnd, msg, "Fatal Error!", MB_ICONERROR);
	return false;
}
