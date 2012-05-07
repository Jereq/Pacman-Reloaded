#include "Texture.h"

namespace Resources
{
	Texture::Texture(ID3D10Device* pDevice, std::string const& _filename)
		: Resource(_filename), device(pDevice), texResource(0), tex(0), textureSRV(0)
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
		if( texResource )
		{
			texResource->Release();
			texResource = NULL;
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

	//Load function for map texture. (This has to be done differently than other
	//textures because we want to extract the colors of the map texture)
	HRESULT Texture::loadMapTexture()
	{
		HRESULT hr = S_OK;


		D3DX10_IMAGE_LOAD_INFO loadinfo;
		ZeroMemory( &loadinfo, sizeof(D3DX10_IMAGE_LOAD_INFO) );
		loadinfo.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		loadinfo.Height = D3DX10_DEFAULT;
		loadinfo.Width = D3DX10_DEFAULT;
		loadinfo.CpuAccessFlags = D3D10_CPU_ACCESS_READ;
		loadinfo.Usage = D3D10_USAGE_STAGING;
		loadinfo.MipLevels = 1;


		hr = D3DX10CreateTextureFromFileA( device, getFilename().c_str(), &loadinfo, NULL, &texResource, 0 );
		if( FAILED(hr) )
		{
			MessageBoxA( 0, "Failed to load map Texture", NULL, NULL );
			return hr;
		}
		tex = ( ID3D10Texture2D* )texResource;

		D3D10_TEXTURE2D_DESC desc;
		tex->GetDesc(&desc);
		width = desc.Width;
		height = desc.Height;
		extractColors();

		return hr;
	}

	//Creates a vector containing all the color values for each pixel in the texture.
	void Texture::extractColors()
	{
		D3D10_MAPPED_TEXTURE2D mappedTex;
		tex->Map( D3D10CalcSubresource(0, 0, 1), D3D10_MAP_READ, 0, &mappedTex );

		float* texels = (float*)mappedTex.pData;

		int count = 0;
		for(UINT i = 0; i < height; i++)
		{
			UINT rowStart = i * mappedTex.RowPitch / 4;

			for(UINT j = 0; j < width; j++)
			{
				float x = texels[rowStart + j*4 + 0];
				float y = texels[rowStart + j*4 + 1];
				float z = texels[rowStart + j*4 + 2];
				float w = texels[rowStart + j*4 + 3];
				colorVector.push_back(D3DXCOLOR( x, y, z, w));
			}
		}
		tex->Unmap(0);
		colorVector.shrink_to_fit();
	}

	ID3D10ShaderResourceView* Texture::getTexture()
	{
		return textureSRV;
	}

	std::vector<D3DXCOLOR> const& Texture::getColorVector() const
	{
		return colorVector;
	}

	UINT Texture::getWidth() const
	{
		return width;
	}

	UINT Texture::getHeight() const
	{
		return height;
	}
}