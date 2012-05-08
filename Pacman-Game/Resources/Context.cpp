#include "Context.h"

#include <boost/foreach.hpp>

namespace Resources
{
	Context::Context(ResourceManager::ptr const& _resourceManager)
		: resourceManager(_resourceManager)
	{
	}

	Context::~Context()
	{
		BOOST_FOREACH(ResourceManager::resMap_t::value_type& val, reservedResources)
		{
			resourceManager->freeResource(val.second);
		}
	}

	Texture::ptr Context::getTexture(std::string const& _filename)
	{
		if (reservedResources.count(_filename) == 1)
		{
			return boost::dynamic_pointer_cast<Texture>(reservedResources[_filename]);
		}

		Texture::ptr newRes = resourceManager->loadTexture(_filename);
		reservedResources[_filename] = newRes;

		return newRes;
	}

	MapTexture::ptr Context::getMapTexture(std::string const& _filename)
	{
		if (reservedResources.count(_filename) == 1)
		{
			return boost::dynamic_pointer_cast<MapTexture>(reservedResources[_filename]);
		}

		MapTexture::ptr newRes = resourceManager->loadMapTexture(_filename);
		reservedResources[_filename] = newRes;

		return newRes;
	}

	MTAModel::ptr Context::getMTAModel(std::string const& _filename)
	{
		if (reservedResources.count(_filename) == 1)
		{
			return boost::dynamic_pointer_cast<MTAModel>(reservedResources[_filename]);
		}

		MTAModel::ptr newRes = resourceManager->loadMTAModel(_filename);
		reservedResources[_filename] = newRes;

		return newRes;
	}

	MTModel::ptr Context::getMTModel(std::string const& _filename)
	{
		if (reservedResources.count(_filename) == 1)
		{
			return boost::dynamic_pointer_cast<MTModel>(reservedResources[_filename]);
		}

		MTModel::ptr newRes = resourceManager->loadMTModel(_filename);
		reservedResources[_filename] = newRes;

		return newRes;
	}
}