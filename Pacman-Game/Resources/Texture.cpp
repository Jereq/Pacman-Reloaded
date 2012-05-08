#include "Texture.h"

namespace Resources
{
	Texture::Texture(ID3D10Device* pDevice, std::string const& _filename)
		: Resource(_filename), device(pDevice), textureSRV(0)
	{
	}

	Texture::~Texture()
	{
		assert(useCount == 0);
	}

	void Texture::freeResource()
	{
		if( device )
		{
			device->Release();
			device = NULL;
		}
		if( textureSRV )
		{
			textureSRV->Release();
			textureSRV = NULL;
		}

		useCount = 0;
	}

	//Load function for normal textures
	HRESULT Texture::loadTexture()
	{
		HRESULT hr = S_OK;
		if( textureSRV )
		{
			textureSRV->Release();
		}

		hr = D3DX10CreateShaderResourceViewFromFile( device, getFilename().c_str(), NULL, NULL, &textureSRV, NULL );

		if( FAILED(hr) )
		{
			MessageBoxA( 0, "Failed to load a texture", NULL, NULL );
			return hr;
		}

		return hr;
	}

	ID3D10ShaderResourceView* Texture::getTexture()
	{
		return textureSRV;
	}
}