#include "RandomGhost.h"

namespace Actors
{
	RandomGhost::RandomGhost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid) 
		: Ghost(_model, _pos, _grid)
	{

	}

	RandomGhost::~RandomGhost()
	{

	}

	void RandomGhost::init()
	{
		Ghost::init();
		m_speedInit = 4.5f;
		m_speed = m_speedInit;
	}

	void RandomGhost::update(float _deltaTime)
	{
		Ghost::update(_deltaTime);
		/*
		if(Wall == true)
		{
			if(roads == right/left/back)
			{
				random [0,2];
				go[random];
			}
			else if(walls == right)
				go left;
			else if(walls == left)
				go right;
			else
		}
		else if(roads < 2)
		{
			if(roads == 3)
				random[0,3];
			else if(roads == 4)
				random[0,4];

			go[random];
		}
		else
		{
			go(cell in front);
		}
		*/	
	}
}