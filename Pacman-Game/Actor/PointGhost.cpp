#include "PointGhost.h"

PointGhost::PointGhost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos) 
	: Ghost(_model, _pos)
{

}

PointGhost::~PointGhost()
{

}

void PointGhost::init()
{
	Ghost::init();
	m_speedInit = 4.0f;
	m_speed = m_speedInit;
}

void PointGhost::update(float _deltaTime)
{
	Ghost::update(_deltaTime);
}

