#include "ResourceManager.h"

#include <iostream>
#include <boost/foreach.hpp>

namespace Resources
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

		mtaLoad.startup(device);
		mtLoader.startup(device);
	}

	void ResourceManager::shutdown()
	{
		std::cout << "Shutting down resource manager" << std::endl;

		if (loadedResources.size() != 0)
		{
			std::cout << "Freeing unreleased resources (" << loadedResources.size() << ")" << std::endl;

			BOOST_FOREACH(resMap_t::value_type& val, loadedResources)
			{
				val.second->freeResource();
			}

			loadedResources.clear();
		}

		mtaLoad.shutdown();
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

	MapTexture::ptr ResourceManager::loadMapTexture(std::string const& _filename)
	{
		assert(device != NULL);

		MapTexture::ptr res;

		if (loadedResources.count(_filename) == 1)
		{
			res = boost::dynamic_pointer_cast<MapTexture>(loadedResources[_filename]);
		}
		else
		{
			res.reset(new MapTexture(device, _filename));
			res->loadMapTexture();

			loadedResources[_filename] = res;
		}

		res->incrementUseCount();

		return res;
	}

	MTAModel::ptr ResourceManager::loadMTAModel(std::string const& _filename)
	{
		assert(device != NULL);

		MTAModel::ptr res;

		if (loadedResources.count(_filename) == 1)
		{
			res = boost::dynamic_pointer_cast<MTAModel>(loadedResources[_filename]);
		}
		else
		{
			res.reset(new MTAModel(_filename));
			mtaLoad.loadmta(res);

			res->setTexture(loadTexture(res->getTextureName()));

			loadedResources[_filename] = res;
		}

		res->incrementUseCount();

		return res;
	}

	MTModel::ptr ResourceManager::loadMTModel(std::string const& _filename)
	{
		assert(device != NULL);

		MTModel::ptr res;

		if (loadedResources.count(_filename) == 1)
		{
			res = boost::dynamic_pointer_cast<MTModel>(loadedResources[_filename]);
		}
		else
		{
			res.reset(new MTModel(_filename));
			mtLoader.loadMT(res);

			res->setTexture(loadTexture(res->getTextureName()));

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
			
			MTAModel::ptr model = boost::dynamic_pointer_cast<MTAModel>(res);
			if (model)
			{
				freeResource(model->getTexture());
			}

			loadedResources.erase(resName);
		}
	}
}