#include "HuntGhost.h"

HuntGhost::HuntGhost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max) : Ghost(_pos, _min, _max)
{

}

HuntGhost::~HuntGhost()
{

}

void HuntGhost::update(float _deltaTime)
{

}

void HuntGhost::init()
{
	GameObject::init();
	m_speedInit = 3.5f;
	m_speed = m_speedInit;
}