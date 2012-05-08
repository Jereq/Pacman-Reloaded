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
		MTAModel::ptr getModel(std::string const& _filename);
	};
}