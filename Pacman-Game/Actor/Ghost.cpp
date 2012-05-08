#include "Ghost.h"

Ghost::Ghost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max) 
	: Actor(_pos, _min, _max)
{

}

Ghost::~Ghost()
{

}

void Ghost::init()
{
	Actor::init();
	m_state = DEAD;
	m_speedFrenzy = 0.8f;
}

void Ghost::update(float _deltaTime)
{

}
