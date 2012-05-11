#pragma once

#include "Ghost.h"

namespace Actors
{
	class HuntGhost : public Ghost
	{
	private:

	public:

		HuntGhost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid);
		virtual ~HuntGhost();

		void init(GameplayFoundations::CellIndex _target);

		void update(float _deltaTime, GameplayFoundations::CellIndex _target);
	};
}