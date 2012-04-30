#pragma once

#include "ResourceHandling/ResourceManager.h"
#include "SoundManager.h"

namespace Pacman
{
	class Game
	{
	private:
		ResourceHandling::ResourceManager rm;
		SoundManager sm;

	public:
		Game();
		~Game();

		void update(float deltaTime);
	};
}