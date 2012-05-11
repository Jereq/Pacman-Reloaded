#include "Food.h"

Food::Food(Resources::MTModel::ptr _model, D3DXVECTOR3 _pos, FOODTYPE _type)
	: GameObject(_pos)
{
	m_model = _model;
	m_type = _type;
}



Food::~Food()
{

}

void Food::init()
{
	m_min = m_model->getbbMin();
	m_max = m_model->getbbMax();
	foodType(m_type);
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, 0.2f, 0.2f, 0.2f );
	D3DXVec3TransformCoord( &m_min, &m_min, &scale );
	D3DXVec3TransformCoord( &m_max, &m_max, &scale );

	D3DXMatrixTranslation(&m_world, m_pos.x, m_pos.y, m_pos.z);
	m_world = scale * m_world;
	
}

void Food::foodType(FOODTYPE _type)
{
	//m_type = _type;
	switch(m_type)
	{
	case NORMAL:
		m_score = 1;
		break;

	case SPECIAL:
		m_score = 10;
		break;

	case POWERUPS:
		m_score = 0;
		break;
	}

}

void Food::update(float _deltaTime)
{
	GameObject::update(_deltaTime);
	D3DXMATRIX rot;
	D3DXMatrixRotationY(&rot, _deltaTime);
	m_world = rot * m_world;
}

void Food::draw(Graphics::dxManager* _dxManager)
{
	_dxManager->AddStaticObject(Graphics::staticObject(m_model->getMesh(), m_model->getTexture(), m_world));
}

UINT Food::getScore()
{
	return m_score;
}