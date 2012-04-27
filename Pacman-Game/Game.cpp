#include "Game.h"

namespace Pacman
{
	Game::Game()
	{
		rm.startup();
	}

	Game::~Game()
	{
		rm.shutdown();
	}
}