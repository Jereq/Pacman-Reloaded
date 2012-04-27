#include "ResourceManager.h"

#include <iostream>

namespace ResourceHandling
{
	ResourceManager::ResourceManager()
	{
		std::cout << "Creating resource manager" << std::endl;
	}

	void ResourceManager::startup()
	{
		std::cout << "Starting up resource manager" << std::endl;
	}

	void ResourceManager::shutdown()
	{
		std::cout << "Shuting down resource manager" << std::endl;
	}
}