#include "MTModel.h"

namespace Resources
{
	MTModel::MTModel(std::string const& _filename)	: Resource(_filename)
	{
		mesh = NULL;
	}

	MTModel::~MTModel()
	{
		assert(useCount == 0);
	}

	void MTModel::freeResource()
	{
		mesh->Release();
		useCount = 0;
	}

	std::string MTModel::getTextureName() const
	{
		return textureName;
	}

	void MTModel::setTextureName(std::string const& _filename)
	{
		textureName = _filename;
	}

	Texture::ptr MTModel::getTexture() const
	{
		return texture;
	}

	void MTModel::setTexture(Texture::ptr const& _texture)
	{
		texture = _texture;
	}

	void MTModel::setBoundingBox(D3DXVECTOR3 const& _minPos, D3DXVECTOR3 const& _maxPos)
	{
		bbMin = _minPos;
		bbMax = _maxPos;
	}

	void MTModel::setMesh(ID3DX10Mesh* _mesh)
	{
		mesh = _mesh;
	}

	ID3DX10Mesh* MTModel::getMesh()
	{
		return mesh;
	}
}