#include "MapTexture.h"

namespace Resources
{
	MapTexture::MapTexture(ID3D10Device* pDevice, std::string const& _filename)
		: Resource(_filename), device(pDevice), texResource(0), tex(0)
	{
	}

	MapTexture::~MapTexture()
	{
		assert(useCount == 0);
	}

	void MapTexture::freeResource()
	{
		if( texResource )
		{
			texResource->Release();
			texResource = NULL;
		}

		useCount = 0;
	}

	HRESULT MapTexture::loadMapTexture()
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

		return hr;
	}

	void MapTexture::extractColors(std::vector<D3DXCOLOR> colors)
	{
		D3D10_MAPPED_TEXTURE2D mappedTex;
		tex->Map( D3D10CalcSubresource(0, 0, 1), D3D10_MAP_READ, 0, &mappedTex );

		float* texels = (float*)mappedTex.pData;
		colors.reserve(width*height);

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
				colors.push_back(D3DXCOLOR( x, y, z, w));
			}
		}
		tex->Unmap(0);
	}

	UINT MapTexture::getWidth() const
	{
		return width;
	}

	UINT MapTexture::getHeight() const
	{
		return height;
	}

}


