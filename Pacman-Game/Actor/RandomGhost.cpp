#include "RandomGhost.h"

RandomGhost::RandomGhost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max) : Ghost(_pos, _min, _max)
{

}

RandomGhost::~RandomGhost()
{

}

void RandomGhost::init()
{
	GameObject::init();
	m_speedInit = 4.5f;
	m_speed = m_speedInit;
}

void RandomGhost::update(float _deltaTime)
{
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