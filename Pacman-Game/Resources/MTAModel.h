#pragma once

#include "Resource.h"
#include "Texture.h"

namespace Resources
{
	class MTAModel : public Resource
	{
	public:
		struct Animation
		{
			std::string name;
			float time;
			std::vector<ID3DX10Mesh*> subAnimations;
		};

	private:
		std::string textureName;
		Texture::ptr texture;
		std::vector<Animation> animations;

		D3DXVECTOR3 bbMin, bbMax;

	public:
		typedef boost::shared_ptr<MTAModel> ptr;

		MTAModel(std::string const& _filename);
		~MTAModel();

		virtual void freeResource();

		std::string getTextureName() const;
		void setTextureName(std::string const& _filename);

		Texture::ptr getTexture() const;
		void setTexture(Texture::ptr const& _texture);

		ID3DX10Mesh* getSubAnimation(size_t _aniIndex, size_t _subAniIndex) const;
		float getAnimationTime(size_t _aniIndex) const;

		void setBoundingBox(D3DXVECTOR3 const& _minPos, D3DXVECTOR3 const& _maxPos);
		void setAnimations(std::vector<Animation> const& _animations);
	};
}