#pragma once

#include "Actor.h"
#include "..\Resources\MTAModel.h"

namespace Actors
{
	class Ghost : public Actor
	{	
	private:

	public:
		Ghost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid);
		virtual ~Ghost();

		void init();
		void update(float _deltaTime);
		void draw(Graphics::dxManager* _dxManager);
	};
}