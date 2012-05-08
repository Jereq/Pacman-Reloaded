#include "MTAModel.h"

#include <boost/foreach.hpp>

namespace Resources
{
	MTAModel::MTAModel(std::string const& _filename)
		: Resource(_filename)
	{
	}

	MTAModel::~MTAModel()
	{
		assert(useCount == 0);
	}

	void MTAModel::freeResource()
	{
		BOOST_FOREACH(Animation& animation, animations)
		{
			BOOST_FOREACH(ID3DX10Mesh* sub, animation.subAnimations)
			{
				sub->Release();
			}
		}

		useCount = 0;
	}

	std::string MTAModel::getTextureName() const
	{
		return textureName;
	}

	void MTAModel::setTextureName(std::string const& _filename)
	{
		textureName = _filename;
	}

	Texture::ptr MTAModel::getTexture() const
	{
		return texture;
	}

	void MTAModel::setTexture(Texture::ptr const& _texture)
	{
		texture = _texture;
	}

	ID3DX10Mesh* MTAModel::getSubAnimation(size_t _aniIndex, size_t _subAniIndex) const
	{
		assert(_aniIndex < animations.size());
		assert(_subAniIndex < animations[_aniIndex].subAnimations.size());

		return animations[_aniIndex].subAnimations[_subAniIndex];
	}

	void MTAModel::setBoundingBox(D3DXVECTOR3 const& _minPos, D3DXVECTOR3 const& _maxPos)
	{
		bbMin = _minPos;
		bbMax = _maxPos;
	}

	void MTAModel::setAnimations(std::vector<Animation> const& _animations)
	{
		animations = _animations;
	}
}