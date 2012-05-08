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
		ID3D10ShaderResourceView* getTexture();

		virtual void freeResource();

	private:
		ID3D10Device*		device;
		ID3D10ShaderResourceView* textureSRV;
	};
}