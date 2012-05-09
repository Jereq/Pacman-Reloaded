#include "PointGhost.h"

PointGhost::PointGhost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max) 
	: Ghost(_model, _pos, _min, _max)
{

}

PointGhost::~PointGhost()
{

}

void PointGhost::update(float _deltaTime)
{

}

void PointGhost::init()
{
	Ghost::init();
	m_speedInit = 4.0f;
	m_speed = m_speedInit;
}