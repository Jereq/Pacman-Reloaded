#include "ResourceManager.h"

#include <iostream>

namespace ResourceHandling
{
	ResourceManager::ResourceManager()
		: device(NULL)
	{
		std::cout << "Creating resource manager" << std::endl;
	}

	void ResourceManager::startup(ID3D10Device* _device)
	{
		std::cout << "Starting up resource manager" << std::endl;

		device = _device;
	}

	void ResourceManager::shutdown()
	{
		std::cout << "Shutting down resource manager" << std::endl;
	}

	Texture::ptr ResourceManager::loadTexture(std::string const& _filename)
	{
		assert(device != NULL);

		Texture::ptr res;

		if (loadedResources.count(_filename) == 1)
		{
			res = boost::dynamic_pointer_cast<Texture>(loadedResources[_filename]);
		}
		else
		{
			res.reset(new Texture(device, _filename));
			res->loadTexture();

			loadedResources[_filename] = res;
		}

		res->incrementUseCount();

		return res;
	}

	void ResourceManager::freeResource(Resource::ptr const& _resource)
	{
		std::string const& resName = _resource->getFilename();

		if (loadedResources.count(resName) != 1)
		{
			return;
		}

		Resource::ptr& res = loadedResources[resName];

		res->decrementUseCount();
		if (res->getUseCount() == 0)
		{
			res->freeResource();
			loadedResources.erase(resName);
		}
	}
}