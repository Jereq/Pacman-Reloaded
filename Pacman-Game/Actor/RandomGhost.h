#pragma once

#include "Ghost.h"
namespace Actors
{
	class RandomGhost : public Ghost
	{
	private:

	public:

		RandomGhost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid);
		virtual ~RandomGhost();

		void init();

		void update(float _deltaTime);
	};
}