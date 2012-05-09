#include "HuntGhost.h"

HuntGhost::HuntGhost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos) 
	: Ghost(_model, _pos)
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
	Ghost::init();
	m_speedInit = 3.5f;
	m_speed = m_speedInit;
}