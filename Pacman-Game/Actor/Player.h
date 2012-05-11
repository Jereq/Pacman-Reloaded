#pragma once

#include "Actor.h"
#include "..\Resources\MTAModel.h"
#include "../Sound/Loop.h"

namespace Actors
{
	class Player : public Actor
	{
	private:
		UINT m_scoreAmount;
	float prevx, prevz;

	Sound::Loop::ptr eatSound;

	public:
		Player(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid);
		~Player();

		void init();
         	void update(float _deltaTime);

		void draw(Graphics::dxManager* _dxManager);

		bool beEatingOrNot();

		void setScore(int _score);
		UINT getScore();
	};
}