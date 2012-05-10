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
	D3DXMatrixTranslation(&m_world, m_pos.x, m_pos.y, m_pos.z);
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