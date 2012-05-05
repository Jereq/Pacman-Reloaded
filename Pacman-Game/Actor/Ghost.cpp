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

void Ghost::update(float _deltaTime)
{

}

void Ghost::changeState(GHOSTSTATE _state)
{
	switch(_state)
	{
	case ALIVE:
		m_state = ALIVE;
		break;

	case DEAD:
		m_state = DEAD;
		break;

	case ESCAPE:
		m_state = ESCAPE;
		break;
	}
}

GHOSTSTATE Ghost::getState()
{
	return m_state;
}