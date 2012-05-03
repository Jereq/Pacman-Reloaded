#pragma once

#include <D3D10.h>
#include <D3DX10.h>
#include <vector>

#include "Resource.h"

namespace Resources
{
	class Texture : public Resource
	{
	public:
		typedef boost::shared_ptr<Texture> ptr;

		Texture(ID3D10Device* pDevice, std::string const& _filename);
		~Texture();
		HRESULT loadTexture();
		HRESULT loadMapTexture();
		ID3D10ShaderResourceView* getTexture();
		std::vector<D3DXCOLOR> getColorVector();

		virtual void freeResource();

	private:
		ID3D10Resource*		texResource;
		ID3D10Device*		device;
		ID3D10Texture2D*	tex;
		ID3D10ShaderResourceView* textureSRV;
		std::vector<D3DXCOLOR>	colorVector;
		void extractColors(UINT width, UINT height);
	};
}