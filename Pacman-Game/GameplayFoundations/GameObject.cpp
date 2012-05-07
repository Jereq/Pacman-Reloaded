#include "GameObject.h"

GameObject::GameObject(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max) 
	: m_pos(_pos), m_min(_min), m_max(_max)
{

}

GameObject::~GameObject()
{

}

void GameObject::init()
{
	m_speedInit = 1.f;
	m_speed = m_speedInit;
	//m_pos offset depending on model
}

void GameObject::update(float _deltaTime)
{
	if(m_state == FRENZY)
	{
		frenzyMode(_deltaTime);
	}
}

void GameObject::changeState(GO_STATE _state)
{
	switch(_state)
	{
	case ALIVE:
		m_timer = 0;
		resetSpeed();
		m_state = ALIVE;
		break;

	case DEAD:
		m_state = DEAD;
		break;

	case FRENZY:
		setSpeed(m_speedFrenzy);
		m_state = FRENZY;
		break;
	//case COUNT:
	//	break;
	}

	//It would be neat with an Observer here
	//signed
}

void GameObject::frenzyMode(float _deltaTime)
{
	m_timer += _deltaTime;
	if(m_timer > 5.f)
	{
		changeState(ALIVE);
	}
}


void GameObject::setSpeed(float _speed)
{
	m_speed = _speed;
}

void GameObject::resetSpeed()
{
	m_speed = m_speedInit;
}

D3DXVECTOR3 GameObject::getPos()
{
	return m_pos;
}

D3DXVECTOR3 GameObject::getMinCorner()
{
	return m_min;
}

D3DXVECTOR3 GameObject::getMaxCorner()
{
	return m_max;
}

GO_STATE GameObject::getState()
{
	return m_state;
}