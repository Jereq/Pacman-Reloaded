#pragma once

#include "GFX/dxManager.h"
#include "ResourceHandling/ResourceManager.h"
#include "Sound/SoundManager.h"
#include "GFX/Camera.h"
#include "GameplayFoundations/Grid.h"
#include "HID\HID.h"

namespace Pacman
{
	class Game
	{
	private:
		int windowWidth;
		int windowHeight;

		HWND hWnd;
		Graphics::dxManager* gManager;

		HID* m_HID;

		Resources::ResourceManager::ptr rm;
		Sound::SoundManager::ptr sm;

		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		bool initWindow(HINSTANCE hInstance);

		GameplayFoundations::Grid::ptr currentGrid;
		ID3DX10Mesh* levelMesh;
		Resources::Texture::ptr levelTex;

	public:
		Game(HINSTANCE _hInstance);
		~Game();

		void update(float deltaTime);
	};
}