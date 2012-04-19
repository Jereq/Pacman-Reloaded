#ifndef TEXTURE_H
#define TEXTURE_H
#include <d3d10.h>
#include <D3DX10.h>



class Texture
{
public:
	Texture(ID3D10Device* pDevice);
	~Texture();
	ID3D10Texture2D* loadTexture(char* filename);

private:
	ID3D10Resource*	 texResource;
	ID3D10Device*	 device;
};



#endif