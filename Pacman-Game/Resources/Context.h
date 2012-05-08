#pragma once

#include "ResourceManager.h"

namespace Resources
{
	class Context
	{
	private:
		ResourceManager::ptr resourceManager;

		ResourceManager::resMap_t reservedResources;

	public:
		Context(ResourceManager::ptr const& _resourceManager);
		~Context();

		Texture::ptr getTexture(std::string const& _filename);
		MapTexture::ptr getMapTexture(std::string const& _filename);
		MTAModel::ptr getMTAModel(std::string const& _filename);
		MTModel::ptr getMTModel(std::string const& _filename);
	};
}