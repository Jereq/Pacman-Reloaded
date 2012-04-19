#include "Texture.h"

Texture::Texture(ID3D10Device* pDevice) : texResource(0)
{
	device = pDevice;
}


Texture::~Texture()
{
	if( device )
		device->Release();
	if( texResource )
		texResource->Release();
}

ID3D10Texture2D* Texture::loadTexture(char* filename)
{
	if( texResource )
		texResource->Release();

	HRESULT hr = S_OK;
	
	hr = D3DX10CreateTextureFromFileW( device, (LPCWSTR)filename, NULL, NULL, &texResource, 0 );

	if( FAILED(hr) )
	{
		MessageBoxA( 0, "Failed to load Texture", NULL, NULL );
		return NULL;
	}

	return ( ID3D10Texture2D* )texResource;
}