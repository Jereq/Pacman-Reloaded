#include "Texture.h"

Texture::Texture(ID3D10Device* pDevice) : texResource(0), tex(0)
{
	device = pDevice;
}

Texture::~Texture()
{
	if( device )
		device->Release();
	if( texResource )
		texResource->Release();
	if( tex )
		tex->Release();

	if( !colorVector.empty() )
	{
		colorVector.clear();
		colorVector.shrink_to_fit();
	}

}

//Load function for normal textures
HRESULT Texture::loadTexture(LPCSTR filename)
{
	HRESULT hr = S_OK;
	
	hr = D3DX10CreateTextureFromFileA( device, filename, NULL, NULL, &texResource, 0 );

	if( FAILED(hr) )
	{
		MessageBoxA( 0, "Failed to load a texture", NULL, NULL );
		return hr;
	}
	tex = ( ID3D10Texture2D* )texResource;

	return hr;
}

//Load function for map texture. (This has to be done differently than other
//textures becasue we want to extract the colors of the map texture)
HRESULT Texture::loadMapTexture(LPCSTR filename, UINT width, UINT height)
{
	HRESULT hr = S_OK;


	D3DX10_IMAGE_LOAD_INFO loadinfo;
	ZeroMemory( &loadinfo, sizeof(D3DX10_IMAGE_LOAD_INFO) );
	loadinfo.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	loadinfo.Height = height;
	loadinfo.Width = width;
	loadinfo.CpuAccessFlags = D3D10_CPU_ACCESS_READ;
	loadinfo.Usage = D3D10_USAGE_STAGING;
	loadinfo.MipLevels = 1;


	hr = D3DX10CreateTextureFromFileA( device, filename, &loadinfo, NULL, &texResource, 0 );
	if( FAILED(hr) )
	{
		MessageBoxA( 0, "Failed to load map Texture", NULL, NULL );
		return hr;
	}
	tex = ( ID3D10Texture2D* )texResource;

	extractColors(width, height);

	return hr;
}

//Creates a vector containing all the color values for each pixel in the texture.
void Texture::extractColors(UINT width, UINT height)
{
	D3D10_MAPPED_TEXTURE2D mappedTex;
	tex->Map( D3D10CalcSubresource(0, 0, 1), D3D10_MAP_READ, 0, &mappedTex );

	float* texels = (float*)mappedTex.pData;

	int count = 0;
	for(UINT i = 0; i <= height; i++)
	{
		UINT rowStart = i * mappedTex.RowPitch/4;

		for(UINT j = 0; j <= width; j++)
		{
			float x = texels[rowStart + j*4 + 0];
			float y = texels[rowStart + j*4 + 1];
			float z = texels[rowStart + j*4 + 2];
			colorVector.push_back(D3DXCOLOR( x, y, z, 0.f));
		}
	}
	tex->Unmap(0);
	colorVector.shrink_to_fit();
}

ID3D10Texture2D* Texture::getTexture()
{
	return tex;
}

std::vector<D3DXCOLOR> Texture::getColorVector()
{
	return colorVector;
}