#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Resource.h"
#include "Texture.h"
#include "MapTexture.h"
#include "mtaLoader.h"
#include "MTLoader.h"

namespace Resources
{
	class ResourceManager
	{
	public:
		typedef boost::shared_ptr<ResourceManager> ptr;
		typedef std::map<std::string, Resource::ptr> resMap_t;

	private:
		ID3D10Device* device;
		mtaLoader mtaLoad;
		MTLoader mtLoader;

		resMap_t loadedResources;

	public:
		ResourceManager();

		void startup(ID3D10Device* _device);
		void shutdown();

		Texture::ptr loadTexture(std::string const& _filename);
		MapTexture::ptr loadMapTexture(std::string const& _filename);
		MTAModel::ptr loadMTAModel(std::string const& _filename);
		MTModel::ptr loadMTModel(std::string const& _filename);

		void freeResource(Resource::ptr const& _resource);
	};
}