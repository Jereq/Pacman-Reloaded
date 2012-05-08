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

}

void GameObject::update(float _deltaTime)
{
	//
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