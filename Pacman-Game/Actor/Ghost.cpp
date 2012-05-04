#include "Ghost.h"

Ghost::Ghost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max) 
	: GameObject(_pos, _min, _max)
{

}

Ghost::~Ghost()
{

}

void Ghost::init()
{
	GameObject::init();
	m_state = DEAD;

}

void Ghost::changeState(AISTATE _state)
{
	switch(_state)
	{
	case ALIVE:
		break;

	case DEAD:
		break;

	case ESCAPE:
		break;
	}
}