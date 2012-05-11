#pragma once

#include "Actor.h"
#include "..\Resources\MTAModel.h"

namespace Actors
{
	class Ghost : public Actor
	{	
	private:
		std::vector<GameplayFoundations::CellIndex> path;
		float dt;
		void setDir(GameplayFoundations::CellIndex _c);
	public:
		Ghost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid);
		virtual ~Ghost();

		virtual void init(GameplayFoundations::CellIndex _target);
		virtual void update(float _deltaTime, GameplayFoundations::CellIndex _target);
		virtual void draw(Graphics::dxManager* _dxManager);
	};
}