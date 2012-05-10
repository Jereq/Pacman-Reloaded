#include "RandomGhost.h"

RandomGhost::RandomGhost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos) 
	: Ghost(_model, _pos)
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