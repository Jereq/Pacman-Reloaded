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
		SoundManager::release();
	}

	void Game::update(float deltaTime)
	{
		const static FMOD_VECTOR cameraPos = { 0.f, 0.f, 0.f };
		const static FMOD_VECTOR cameraForward = { 0.f, 0.f, 1.f };
		const static FMOD_VECTOR cameraUp = { 0.f, 1.f, 0.f };

		sm.update(cameraPos, cameraForward, cameraUp);
	}
}