
#include "Actor.h"

Actor::Actor(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos)
	 : GameObject(_pos)
{
	m_model = _model;
}

Actor::~Actor()
{
	
}

void Actor::init()
{
	GameObject::init();

	m_min = m_model->getbbMin();
	m_max = m_model->getbbMax();

	m_speedInit = 1.f;
	m_speed = m_speedInit;

}

void Actor::update(float _deltaTime)
{
	dt = _deltaTime;

	D3DXMatrixTranslation(&m_world, m_pos.x, m_pos.y, m_pos.z);

	if(m_state == FRENZY)
	{
		frenzyMode(_deltaTime);
	}

	moveDirection();
}

void Actor::changeState(ACTOR_STATE _state)
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

void Actor::setDirection(DIRECTION _direction)
{
	m_direction = _direction;
}

void Actor::moveDirection()
{
	if(m_direction == DIR_LEFT)
		m_pos.x -= m_speed * dt;
	if(m_direction == DIR_RIGHT)
		m_pos.x += m_speed * dt;
	if(m_direction == DIR_UP)
		m_pos.z += m_speed * dt;
	if(m_direction == DIR_DOWN)
		m_pos.z -= m_speed * dt;
}		
void Actor::frenzyMode(float _deltaTime)
{
	m_timer += _deltaTime;
	if(m_timer > 5.f)
	{
		changeState(ALIVE);
	}
}

void Actor::setSpeed(float _speed)
{
	m_speed = _speed;
}

void Actor::resetSpeed()
{
	m_speed = m_speedInit;
}

ACTOR_STATE Actor::getState()
{
	return m_state;
}