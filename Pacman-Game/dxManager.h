#pragma once

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include <vector>

#include "vertexTypes.h"
#include "lights.h"
#include "ResourceHandling/mtaLoader.h"
#include "Camera.h"

namespace Graphics
{
	class dxManager
	{
		/*******************************************************************
		* Members
		********************************************************************/	
	private:

		//window handle shortcut
		HWND*									hWnd;
	
		//device vars
	
		IDXGISwapChain*							pSwapChain;
		ID3D10RenderTargetView*					pRenderTargetView;
		ID3D10Texture2D*						pDepthStencil;
		ID3D10DepthStencilView*					pDepthStencilView;	
		D3D10_VIEWPORT							viewPort;

		//input layout
		ID3D10InputLayout*						pVertexLayout;

		//effects and techniques
		ID3D10Effect*							pBasicEffect;
		ID3D10EffectTechnique*					pTechnique;

		//effect variable pointers
		ID3D10EffectMatrixVariable*				pViewMatrixEffectVariable;
		ID3D10EffectMatrixVariable*				pProjectionMatrixEffectVariable;
		ID3D10EffectMatrixVariable*				pWorldMatrixEffectVariable;
		ID3D10EffectShaderResourceVariable*		pColorMap;
		ID3D10EffectScalarVariable*				pBufferStart;
		ID3D10EffectScalarVariable*				pBufferStop;
		ID3D10EffectScalarVariable*				pTime;

		//projection and view matrices
		D3DXMATRIX								worldMatrix;

		//technique
		D3D10_TECHNIQUE_DESC					techDesc;
	
		//Lights
		D3DXVECTOR4								ambientLight;
		DirectionalLight						directionalLight;
		Material								material;

		std::vector<Resources::MTA::ptr>	mta;	
	
		//Active camera
		Camera*								camera;
	
		/*******************************************************************
		* Methods
		********************************************************************/	
	public:

		//constructor and destructor
		dxManager();
		~dxManager();

		ID3D10Device*						pD3DDevice;

		//initialize directx device
		bool initialize(HWND*);	

		//scene function
		void renderScene();	

		//Get and set the active camera
		Camera* getActiveCamera();
		Camera const* getActiveCamera() const;
		void setActiveCamera(Camera* _newCamera);

	private:

		//initialization methods
		bool createSwapChainAndDevice( UINT width, UINT height );
		bool loadShadersAndCreateInputLayouts();
		void createViewports( UINT width, UINT height );
		bool createRenderTargetsAndDepthBuffer( UINT width, UINT height );
		bool initializeObjects();

		//fatal error handler
		bool fatalError(const LPCSTR msg); 
	};
}