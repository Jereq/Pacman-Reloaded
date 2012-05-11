#pragma once

#include "Ghost.h"

namespace Actors
{
	class PointGhost : public Ghost
	{
	private:

	public:

		PointGhost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid);
		virtual ~PointGhost();

		void init();

		void update(float _deltaTime);
	};
}