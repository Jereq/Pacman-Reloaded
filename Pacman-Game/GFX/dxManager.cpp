#include "dxManager.h"
#include <math.h>
#include "../ResourceHandling\mtaLoader.h"
#include <cassert>

namespace Graphics
{
	dxManager::dxManager() :	
		pD3DDevice(NULL),
		pSwapChain(NULL),
		pRenderTargetView(NULL),
		pStaticEffect(NULL),
		pDynamicEffect(NULL),
		camera(NULL)
	{
		D3DXMatrixIdentity(&worldMatrix);
	}

	dxManager::~dxManager()
	{
		if ( pRenderTargetView ) pRenderTargetView->Release();
		if ( pSwapChain ) pSwapChain->Release();
		if ( pD3DDevice ) pD3DDevice->Release();
		if ( pStaticEffect ) pStaticEffect->Release();
		if ( pDynamicEffect ) pDynamicEffect->Release();
		if ( pDepthStencil ) pDepthStencil->Release();

		if (camera)
		{
			delete camera;
		}
	}

	#pragma region Init

	bool dxManager::initialize( HWND* hW )
	{
		//window handle
		hWnd = hW;

		//get window dimensions
		RECT rc;
		GetClientRect( *hWnd, &rc );
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		if ( !createSwapChainAndDevice(width, height) ) return false;

		if ( !loadShadersAndCreateInputLayouts() ) return false;			

		createViewports(width, height);

		if ( !createRenderTargetsAndDepthBuffer(width, height) ) return false;

		return true;
	}

	bool dxManager::createSwapChainAndDevice( UINT width, UINT height )
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
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

		if ( FAILED( D3D10CreateDeviceAndSwapChain(		NULL, 
			D3D10_DRIVER_TYPE_HARDWARE, 
			NULL, 
			0, 
			D3D10_SDK_VERSION, 
			&swapChainDesc, 
			&pSwapChain, 
			&pD3DDevice ) ) ) return fatalError((LPCSTR)"D3D device creation failed");
		return true;
	}

	void dxManager::createViewports( UINT width, UINT height )
	{	
		//create viewport structure	
		viewPort.Width = width;
		viewPort.Height = height;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;

		pD3DDevice->RSSetViewports(1, &viewPort);
	}

	bool dxManager::createRenderTargetsAndDepthBuffer( UINT width, UINT height )
	{
		//try to get the back buffer
		ID3D10Texture2D* pBackBuffer;	
		if ( FAILED( pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer) ) ) return fatalError((LPCSTR)"Could not get back buffer");

		//try to create render target view
		if ( FAILED( pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView) ) ) return fatalError((LPCSTR)"Could not create render target view");
		pBackBuffer->Release();

		//create depth stencil texture
		D3D10_TEXTURE2D_DESC descDepth;
		descDepth.Width = width;
		descDepth.Height = height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D10_USAGE_DEFAULT;
		descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;   

		if( FAILED( pD3DDevice->CreateTexture2D( &descDepth, NULL, &pDepthStencil ) ) )  return fatalError((LPCSTR)"Could not create depth stencil texture");

		// Create the depth stencil view
		D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		if( FAILED( pD3DDevice->CreateDepthStencilView( pDepthStencil, &descDSV, &pDepthStencilView ) ) ) return fatalError((LPCSTR)"Could not create depth stencil view");

		//set render targets
		pD3DDevice->OMSetRenderTargets( 1, &pRenderTargetView, pDepthStencilView );

		return true;
	}

	bool dxManager::loadShadersAndCreateInputLayouts()
	{
		if ( FAILED( D3DX10CreateEffectFromFile((LPCSTR)"GFX/static.fx", 
			NULL, NULL, 
			"fx_4_0", 
			D3D10_SHADER_ENABLE_STRICTNESS, 
			0, 
			pD3DDevice, 
			NULL, 
			NULL, 
			&pStaticEffect, 
			NULL,
			NULL	) ) ) return fatalError((LPCSTR)"Could not load effect file!");	

		if ( FAILED( D3DX10CreateEffectFromFile((LPCSTR)"GFX/dynamic.fx", 
			NULL, NULL, 
			"fx_4_0", 
			D3D10_SHADER_ENABLE_STRICTNESS, 
			0, 
			pD3DDevice, 
			NULL, 
			NULL, 
			&pDynamicEffect, 
			NULL,
			NULL	) ) ) return fatalError((LPCSTR)"Could not load effect file!");	

		pSingelVertexTechnique = pStaticEffect->GetTechniqueByName("RENDER");	
		pDoubelVertexTechnique = pDynamicEffect->GetTechniqueByName("RENDER");

		if ( pSingelVertexTechnique == NULL ) return fatalError((LPCSTR)"Could not find static technique!");	
		if ( pDoubelVertexTechnique == NULL ) return fatalError((LPCSTR)"Could not find dynamic technique!");	

		//create matrix effect pointers
		pViewMatrixEffectVariable = pStaticEffect->GetVariableByName( "View" )->AsMatrix();
		pProjectionMatrixEffectVariable = pStaticEffect->GetVariableByName( "Projection" )->AsMatrix();
		pWorldMatrixEffectVariable = pStaticEffect->GetVariableByName( "World" )->AsMatrix();	

		//create texture effect variable
		pColorMap = pStaticEffect->GetVariableByName( "colorMap" )->AsShaderResource();

		pTime = pDynamicEffect->GetVariableByName("time")->AsScalar();

		//create input layout simple vertex
		D3D10_PASS_DESC SimplePassDesc;

		pSingelVertexTechnique->GetPassByIndex( 0 )->GetDesc( &SimplePassDesc );

		if ( FAILED( pD3DDevice->CreateInputLayout( Resources::vertexInputLayout, 
			Resources::simpleVertexInputLayoutNumElements, 
			SimplePassDesc.pIAInputSignature,
			SimplePassDesc.IAInputSignatureSize, 
			&pVertexLayout ) ) ) return fatalError((LPCSTR)"Could not create Input Layout!");

		//create input layout double vertex
		D3D10_PASS_DESC DoublePassDesc;

		pDoubelVertexTechnique->GetPassByIndex( 0 )->GetDesc( &DoublePassDesc );

		HRESULT hr = pD3DDevice->CreateInputLayout( Resources::doubleVertexInputLayout, 
			Resources::doubleVertexInputLayoutNumElements, 
			DoublePassDesc.pIAInputSignature,
			DoublePassDesc.IAInputSignatureSize, 
			&pDoubleVertexLayout );

		if ( FAILED( hr ) ) return fatalError((LPCSTR)"Could not create Double Input Layout!");

		return true;
	}
	#pragma endregion Init

	bool dxManager::initializeObjects(Resources::ResourceManager::ptr _res)
	{
	
		std::string fileNames[] = {"pacman.mta"};//, "blinky.mta", "pinky.mta", "inky.mta", "clyde.mta" };
		Resources::mtaLoader init(pD3DDevice, _res);

		for (int i = 0; i < 1; i++)
		{			
			Resources::MTA::ptr tmp = init.loadmta(fileNames[i]);
			mta.push_back(tmp);
		}

		// Setup light and test material
		ambientLight = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);

		directionalLight.color = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
		directionalLight.direction = D3DXVECTOR3(.3f, -1, 0.5f);
		D3DXVec3Normalize(&directionalLight.direction, &directionalLight.direction);

		material.ambient = .1f;
		material.diffuse = .9f;
		material.specular = 0.5f;
		material.shininess = 30;

		ID3D10EffectVariable* pVar = pStaticEffect->GetVariableByName("light");
		pVar->SetRawValue(&directionalLight, 0, sizeof(DirectionalLight));

		pVar = pStaticEffect->GetVariableByName("material");
		pVar->SetRawValue(&material, 0, sizeof(Material));

		pVar = pStaticEffect->GetVariableByName("ambientLight");
		pVar->SetRawValue(&ambientLight, 0, sizeof(ambientLight));

		
	
		return true;
	}

	void dxManager::renderScene()
	{
		//Assert that there is a camera
		assert(camera != NULL);

		//clear scene
		pD3DDevice->ClearRenderTargetView( pRenderTargetView, D3DXCOLOR(0.82f,0.863f,0.953f,1) );
		pD3DDevice->ClearDepthStencilView( pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0 );

		//set effect variables
		//------------------------------------------------------------------------

		//set view & projection matrices
		pViewMatrixEffectVariable->SetMatrix(camera->getViewMatrix());
		pProjectionMatrixEffectVariable->SetMatrix(camera->getProjectionMatrix());

		//set view position
		ID3D10EffectVectorVariable* var = pStaticEffect->GetVariableByName( "eye" )->AsVector();
		var->SetFloatVector( (float*) camera->getCameraPosition() );

		//set world matrix
		D3DXMatrixIdentity(&worldMatrix);
		pWorldMatrixEffectVariable->SetMatrix(worldMatrix);

		pD3DDevice->IASetInputLayout( pVertexLayout );

		//draw terrain
		//------------------------------------------------------------------------

		pColorMap->SetResource(wallTex->getTexture());

		//get technique description
		pSingelVertexTechnique->GetDesc( &techDesc );

		//draw
		for( UINT p = 0; p < techDesc.Passes; p++ )
		{		
			//apply technique			
			pSingelVertexTechnique->GetPassByIndex( p )->Apply( 0 );
			walls->DrawSubset(0);
		}		

		//flip buffers
		pSwapChain->Present(0,0);
	}

	Camera* dxManager::getActiveCamera()
	{
		return camera;
	}

	Camera const* dxManager::getActiveCamera() const
	{
		return camera;
	}

	void dxManager::setActiveCamera(Camera* _newCamera)
	{
		camera = _newCamera;
	}

	bool dxManager::fatalError(const LPCSTR msg)
	{
		MessageBox(*hWnd, msg, "Fatal Error!", MB_ICONERROR);
		return false;
	}

	void dxManager::setWallMesh(ID3DX10Mesh* _mesh)
	{
		walls = _mesh;
	}

	void dxManager::setWallTex(Resources::Texture::ptr const& _tex)
	{
		wallTex = _tex;
	}

	minMax dxManager::getbounds(int _index)
	{
		return minMax(mta[_index]->vectorMin, mta[_index]->vectorMax);		
	}
}