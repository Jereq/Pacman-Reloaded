#ifndef TEXTURE_H
#define TEXTURE_H
#include <d3d10.h>
#include <D3DX10.h>
#include <vector>



class Texture
{
public:
	Texture(ID3D10Device* pDevice);
	~Texture();
	HRESULT loadTexture(LPCSTR filename);
	HRESULT loadMapTexture(LPCSTR filename, UINT widht, UINT height);
	ID3D10Texture2D* getTexture();
	std::vector<D3DXCOLOR> getColorVector();

private:
	ID3D10Resource*		texResource;
	ID3D10Device*		device;
	ID3D10Texture2D*	tex;
	std::vector<D3DXCOLOR>	colorVector;
};



#endif