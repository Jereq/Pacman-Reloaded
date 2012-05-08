#pragma once

#include <D3D10.h>
#include <D3DX10math.h>
#include <vector>

#include "Resource.h"

namespace Resources
{
	class MapTexture : public Resource
	{
	public:
		typedef boost::shared_ptr<MapTexture> ptr;

		MapTexture(ID3D10Device* pDevice, std::string const& _filname);
		~MapTexture();
		HRESULT loadMapTexture();
		UINT getWidth() const;
		UINT getHeight() const;
		void extractColors(std::vector<D3DXCOLOR>& colors);

		virtual void freeResource();
	private:
		ID3D10Resource* texResource;
		ID3D10Device* device;
		ID3D10Texture2D* tex;
		UINT width;
		UINT height;
	};
}
