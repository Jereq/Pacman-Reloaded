#pragma once

#include "ResourceHandling/ResourceManager.h"

namespace Pacman
{
	class Game
	{
	private:
		ResourceHandling::ResourceManager rm;

	public:
		Game();
		~Game();
	};
}