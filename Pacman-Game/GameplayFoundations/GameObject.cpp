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
	m_initSpeed = 1.f;
	m_speed = m_initSpeed;
	//m_pos offset depending on model
}

void GameObject::update()
{

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