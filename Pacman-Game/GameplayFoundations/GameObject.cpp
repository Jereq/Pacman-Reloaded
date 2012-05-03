#include "GameObject.h"


GameObject::GameObject(D3DXVECTOR3 _pos) 
	: m_pos(_pos)
{

}

GameObject::~GameObject()
{

}

void GameObject::init()
{
	m_initSpeed = 1.f;
	m_speed = m_initSpeed;
}

void GameObject::setSpeed(float _speed)
{
	m_speed = _speed;
}

void GameObject::resetSpeed()
{
	m_speed = m_initSpeed;
}

D3DXVECTOR3 GameObject::getPos()
{
	return m_pos;
}