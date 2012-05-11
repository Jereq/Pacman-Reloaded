#pragma once

#include "..\Resources\MTAModel.h"
#include "..\Sound\SoundManager.h"
#include "..\GameplayFoundations\GameObject.h"
#include "..\GameplayFoundations\Grid.h"

enum ACTOR_STATE
{
	ALIVE,
	DEAD,
	FRENZY,
	COUNT
};

enum DIRECTION
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
};

namespace Actors
{
	class Actor : public GameplayFoundations::GameObject
	{
	protected:
		Resources::MTAModel::ptr m_model;

		ACTOR_STATE m_state;
		float m_speed, m_speedInit, m_speedFrenzy;
	
		float m_timer, dt;
	
		float time;
		int subA;

		D3DXMATRIX rotation;
		D3DXMATRIX initScaleRotation;

		std::vector<std::string> m_aniNames;
		int m_aniIndex;
		float m_aniTime;

		GameplayFoundations::Grid::ptr grid;

		GameplayFoundations::CellIndex fromCell, toCell;
		float currentRelPos;

		D3DXMATRIX m_scale;
	

	public:
		Actor(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid);
		virtual ~Actor();

		void init();
		void update(float _deltatime);

		void changeState(ACTOR_STATE _state);

		void setDirection(DIRECTION _direction);

		void moveDirection();

		void setSpeed(float _speed);
		void resetSpeed();

		GameplayFoundations::CellIndex getFromCell();
		GameplayFoundations::CellIndex getToCell();

		ACTOR_STATE getState();

	private:

		DIRECTION m_direction;

		void changeDirection();
	
		void frenzyMode(float d_deltaTime);

	};
}