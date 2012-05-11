#pragma once

#include "GFX/dxManager.h"
#include "Resources/ResourceManager.h"
#include "Sound/SoundManager.h"
#include "GFX/Camera.h"
#include "Actor\Player.h"
#include "Actor\Food.h"
#include "GameplayFoundations/Grid.h"
#include "GameplayFoundations/Events/EventQueue.h"
#include "HID\HID.h"
#include "GameplayFoundations\Collision.h"

#include "Actor\HuntGhost.h"
#include "Actor\PointGhost.h"
#include "Actor\RandomGhost.h"


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

		Actors::Player* player;

		std::vector<Actors::Ghost*> ghosts; 		
		std::vector<Actors::Food*> food;

		GameplayFoundations::Collision* col;

		Resources::ResourceManager::ptr rm;
		Sound::SoundManager::ptr sm;

		GameplayFoundations::Events::EventQueue eventQueue;

		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		bool initWindow(HINSTANCE hInstance);

		GameplayFoundations::Grid::ptr currentGrid;
		ID3DX10Mesh* levelMesh;
		Resources::Texture::ptr levelTex;

		Resources::MTAModel::ptr pacman;
		Resources::MTModel::ptr foodmodel;
		Resources::MTAModel::ptr gRandomModel;
		Resources::MTAModel::ptr gPointModel;
		Resources::MTAModel::ptr gHuntModel;
		
	public:
		Game(HINSTANCE _hInstance);
		~Game();

		void update(float deltaTime);
	};
}