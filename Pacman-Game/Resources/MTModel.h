#pragma once

#include "Resource.h"
#include "Texture.h"
#include <D3D10.h>

namespace Resources
{
	class MTModel : public Resource
	{

	private:
		std::string textureName;
		Texture::ptr texture;
		D3DXVECTOR3 bbMin, bbMax;
		ID3DX10Mesh* mesh;


	public:
		typedef boost::shared_ptr<MTModel> ptr;

		MTModel(std::string const& _filename);
		~MTModel();

		virtual void freeResource();

		std::string getTextureName() const;
		void setTextureName(std::string const& _filename);

		Texture::ptr getTexture() const;
		void setTexture(Texture::ptr const& _texture);

		void setBoundingBox(D3DXVECTOR3 const& _minPos, D3DXVECTOR3 const& _maxPos);
		D3DXVECTOR3 getbbMin();
		D3DXVECTOR3 getbbMax();

		void setMesh(ID3DX10Mesh* _mesh);

		ID3DX10Mesh* getMesh();
	};
}