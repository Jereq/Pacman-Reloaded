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

	Texture::ptr Context::getMapTexture(std::string const& _filename)
	{
		if (reservedResources.count(_filename) == 1)
		{
			return boost::dynamic_pointer_cast<Texture>(reservedResources[_filename]);
		}

		Texture::ptr newRes = resourceManager->loadMapTexture(_filename);
		reservedResources[_filename] = newRes;

		return newRes;
	}
}