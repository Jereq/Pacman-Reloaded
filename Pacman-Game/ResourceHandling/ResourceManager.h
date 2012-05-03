#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Resource.h"
#include "Texture.h"

namespace Resources
{
	class ResourceManager
	{
	public:
		typedef boost::shared_ptr<ResourceManager> ptr;
		typedef std::map<std::string, Resource::ptr> resMap_t;

	private:
		ID3D10Device* device;

		resMap_t loadedResources;

	public:
		ResourceManager();

		void startup(ID3D10Device* _device);
		void shutdown();

		Texture::ptr loadTexture(std::string const& _filename);
		Texture::ptr loadMapTexture(std::string const& _filename);
		//void loadSound(std::string const& _filename);
		//void loadModel(std::string const& _filename);

		void freeResource(Resource::ptr const& _resource);
	};
}