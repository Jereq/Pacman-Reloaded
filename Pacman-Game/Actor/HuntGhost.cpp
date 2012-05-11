#include "HuntGhost.h"

namespace Actors
{
	HuntGhost::HuntGhost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid) 
		: Ghost(_model, _pos, _grid)
	{

	}

	HuntGhost::~HuntGhost()
	{

	}

	void HuntGhost::init(GameplayFoundations::CellIndex _target)
	{
		Ghost::init(_target);
		m_speedInit = 3.5f;
		m_speed = m_speedInit;
	}

	void HuntGhost::update(float _deltaTime, GameplayFoundations::CellIndex _target)
	{
		Ghost::update(_deltaTime, _target);
	}
}

