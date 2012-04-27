#pragma once

#include <string>

namespace ResourceHandling
{
	class ResourceManager
	{
	private:

	public:
		ResourceManager();

		void startup();
		void shutdown();

		void loadTexture(std::string const& filename);
		void loadSound(std::string const& filename);
		void loadModel(std::string const& filename);

		void freeTexture();
		void freeSound();
		void freeModel();
	};
}