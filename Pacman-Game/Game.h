#pragma once

#include "dxManager.h"
#include "ResourceHandling/ResourceManager.h"
#include "SoundManager.h"
#include "Camera.h"

namespace Pacman
{
	class Game
	{
	private:
		int windowWidth;
		int windowHeight;

		HWND hWnd;
		dxManager* gManager;

		ResourceHandling::ResourceManager rm;
		SoundManager sm;

		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		bool initWindow(HINSTANCE hInstance);

	public:
		Game(HINSTANCE _hInstance);
		~Game();

		void update(float deltaTime);
	};
}