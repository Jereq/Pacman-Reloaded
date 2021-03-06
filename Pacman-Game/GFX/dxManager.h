#pragma once

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include <vector>

#include "../Resources/vertexTypes.h"
#include "lights.h"
#include "../Resources/mtaLoader.h"
#include "../Resources/Texture.h"
#include "Camera.h"
#include <DxErr.h>
#include <list>

namespace Graphics
{
	enum Actor
	{
		PACMAN,
		BLINKY,
		PINKY,
		INKY,
		CLYDE,
		COUNT
	};

	struct minMax 
	{
	public:
		D3DXVECTOR3 min;
		D3DXVECTOR3 max;

		minMax(D3DXVECTOR3 _min, D3DXVECTOR3 _max)
		{
			min = _min;
			max = _max;
		}
	};


	struct dynamicObject
	{
	public:
		float time;
		Resources::MTAModel::ptr mta;
		int aIndex, saIndex;
		D3DXMATRIX world;

		dynamicObject(Resources::MTAModel::ptr _mta, float _time, int _aIndex, int _saIndex, D3DXMATRIX _world)
		{
			mta = _mta;
			time = _time;
			aIndex = _aIndex;
			saIndex = _saIndex;
			world = _world;
		}
	};

	struct staticObject 
	{
		D3DXMATRIX world;
		ID3DX10Mesh* mesh;
		Resources::Texture::ptr tex;

		staticObject(ID3DX10Mesh* _mesh, Resources::Texture::ptr _tex, D3DXMATRIX _world)
		{
			mesh = _mesh;
			tex = _tex;
			world = _world;
		}
	};

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
		ID3D10InputLayout*						pDoubleVertexLayout;

		//effects and techniques
		ID3D10Effect*							pStaticEffect;
		ID3D10Effect*							pDynamicEffect;
		ID3D10EffectTechnique*					pSingelVertexTechnique;
		ID3D10EffectTechnique*					pDoubelVertexTechnique;

		//effect variable pointers
		ID3D10EffectMatrixVariable*				pSViewMatrixEffectVariable;
		ID3D10EffectMatrixVariable*				pSProjectionMatrixEffectVariable;
		ID3D10EffectMatrixVariable*				pSWorldMatrixEffectVariable;
		ID3D10EffectShaderResourceVariable*		pSColorMap;

		ID3D10EffectMatrixVariable*				pDViewMatrixEffectVariable;
		ID3D10EffectMatrixVariable*				pDProjectionMatrixEffectVariable;
		ID3D10EffectMatrixVariable*				pDWorldMatrixEffectVariable;
		ID3D10EffectShaderResourceVariable*		pDColorMap;
		ID3D10EffectScalarVariable*				pTime;

		//projection and view matrices
		D3DXMATRIX								worldMatrix;

		//technique
		D3D10_TECHNIQUE_DESC					techDesc;
	
		//Lights
		D3DXVECTOR4								ambientLight;
		DirectionalLight						directionalLight;
		Material								material;

		std::vector<Resources::MTAModel::ptr>	mta;	
	
		//Active camera
		Camera*									camera;

		typedef std::list<staticObject>			sol;
		typedef std::list<dynamicObject>		dol;

		sol										sObj;
		dol										dObj;

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

		void dynamicDraw();

		void StaticDraw();

		//Get and set the active camera
		Camera* getActiveCamera();
		Camera const* getActiveCamera() const;
		void setActiveCamera(Camera* _newCamera);

		void setWallMesh(ID3DX10Mesh* _mesh);
		void setWallTex(Resources::Texture::ptr const& _tex);

		minMax getbounds(int _index);
		bool initializeObjects();

		void AddDynamicObject(dynamicObject _dObj);
		void AddStaticObject(staticObject _sObj);

	private:

		//initialization methods
		bool createSwapChainAndDevice( UINT width, UINT height );
		bool loadShadersAndCreateInputLayouts();
		bool initDynamicObjects();
		bool initStaticObjects();
		void createViewports( UINT width, UINT height );
		bool createRenderTargetsAndDepthBuffer( UINT width, UINT height );

		//fatal error handler
		bool fatalError(const LPCSTR msg); 
	};
}