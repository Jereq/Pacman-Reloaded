#pragma once

#include "dxManager.h"
#include "ResourceHandling/ResourceManager.h"
#include "Sound/SoundManager.h"
#include "Camera.h"

namespace Pacman
{
	class Game
	{
	private:
		int windowWidth;
		int windowHeight;

		HWND hWnd;
		Graphics::dxManager* gManager;

		Resources::ResourceManager::ptr rm;
		Sound::SoundManager::ptr sm;

		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		bool initWindow(HINSTANCE hInstance);

	public:
		Game(HINSTANCE _hInstance);
		~Game();

		void update(float deltaTime);
	};
}