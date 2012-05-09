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

	std::vector<std::string> MTAModel::getAnimationNames() const
	{
		std::vector<std::string> res;
		res.reserve(animations.size());

		BOOST_FOREACH(Animation const& a, animations)
		{
			res.push_back(a.name);
		}

		return res;
	}

	size_t MTAModel::getAnimationIndex(std::string const& _aniName) const
	{
		for (size_t i = 0; i < animations.size(); i++)
		{
			if (animations[i].name == _aniName)
			{
				return i;
			}
		}

		return 0;
	}

	size_t MTAModel::getSubAnimationCount(size_t _aniIndex) const
	{
		assert(_aniIndex < animations.size());

		return animations[_aniIndex].subAnimations.size();
	}

	ID3DX10Mesh* MTAModel::getSubAnimation(size_t _aniIndex, size_t _subAniIndex) const
	{
		assert(_aniIndex < animations.size());
		assert(_subAniIndex < animations[_aniIndex].subAnimations.size());

		return animations[_aniIndex].subAnimations[_subAniIndex];
	}

	float MTAModel::getAnimationTime(size_t _aniIndex) const
	{
		assert(_aniIndex < animations.size());

		return animations[_aniIndex].time;
	}

	void MTAModel::setBoundingBox(D3DXVECTOR3 const& _minPos, D3DXVECTOR3 const& _maxPos)
	{
		bbMin = _minPos;
		bbMax = _maxPos;
	}

	D3DXVECTOR3 MTAModel::getbbMin()
	{
		return bbMin;
	}

	D3DXVECTOR3 MTAModel::getbbMin()
	{
		return bbMax;
	}

	void MTAModel::setAnimations(std::vector<Animation> const& _animations)
	{
		animations = _animations;
	}
}