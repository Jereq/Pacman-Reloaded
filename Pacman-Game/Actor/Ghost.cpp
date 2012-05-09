#include "Ghost.h"

Ghost::Ghost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos) 
	: Actor(_model, _pos)
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
