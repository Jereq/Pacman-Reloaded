#include "PointGhost.h"

namespace Actors
{
	PointGhost::PointGhost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid) 
		: Ghost(_model, _pos, _grid)
	{

	}

	PointGhost::~PointGhost()
	{

	}

	void PointGhost::init(GameplayFoundations::CellIndex _target)
	{
		Ghost::init(_target);
		m_speedInit = 4.0f;
		m_speed = m_speedInit;
	}

	void PointGhost::update(float _deltaTime, GameplayFoundations::CellIndex _target)
	{
		Ghost::update(_deltaTime, _target);
	}
}

