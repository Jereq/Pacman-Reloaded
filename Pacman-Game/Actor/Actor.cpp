
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
	m_min = m_model->getbbMin();
	m_max = m_model->getbbMax();
	m_speedInit = 1.f;
	m_speed = m_speedInit;
	//m_pos offset depending on model
}

void Actor::update(float _deltaTime)
{
	D3DXMatrixTranslation(&m_world, m_pos.x, m_pos.y, m_pos.z);

	if(m_state == FRENZY)
	{
		frenzyMode(_deltaTime);
	}
}

void Actor::draw(Graphics::dxManager* _dxManager)
{
	_dxManager->AddDynamicObject(Graphics::dynamicObject(m_model, m_time, 0, , m_world));
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