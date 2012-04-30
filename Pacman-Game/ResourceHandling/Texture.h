#ifndef TEXTURE_H
#define TEXTURE_H
#include <D3D10.h>
#include <D3DX10.h>
#include <vector>



class Texture
{
public:
	Texture(ID3D10Device* pDevice);
	~Texture();
	HRESULT loadTexture(LPCSTR filename);
	HRESULT loadMapTexture(LPCSTR filename);
	ID3D10ShaderResourceView* getTexture();
	std::vector<D3DXCOLOR> getColorVector();

private:
	ID3D10Resource*		texResource;
	ID3D10Device*		device;
	ID3D10Texture2D*	tex;
	ID3D10ShaderResourceView* textureSRV;
	std::vector<D3DXCOLOR>	colorVector;
	void extractColors(UINT width, UINT height);
};



#endif