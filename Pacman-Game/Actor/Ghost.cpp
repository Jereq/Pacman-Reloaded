#include "Ghost.h"

Ghost::Ghost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos) 
	: Actor(_model, _pos)
{

}

Ghost::~Ghost()
{

}

void Ghost::init()
{
	Actor::init();

	m_state = DEAD;
	m_speedFrenzy = 0.8f;

	m_aniNames = m_model->getAnimationNames();
	m_aniIndex =  m_model->getAnimationIndex(m_aniNames[0]);
	m_aniTime = m_model->getAnimationTime(m_aniIndex);

	D3DXMatrixScaling(&m_scale, 0.4f, 0.4f, 0.4f);

	D3DXVec3TransformCoord(&m_min, &m_min, &m_scale);
	D3DXVec3TransformCoord(&m_max, &m_max, &m_scale);
}

void Ghost::update(float _deltaTime)
{
	Actor::update(_deltaTime);
}
	//D3DXMatrixScaling(&scale, 0.38f, 0.7f, 0.38f );
void Ghost::draw(Graphics::dxManager* _dxManager)
{
	static float time = 0;
	static int subA = 0;
	
	time += dt / m_aniTime;
	if (time >= 1)
	{
		time = 0;
		subA = 1 - subA;
	}
	
	_dxManager->AddDynamicObject(Graphics::dynamicObject(m_model, time, 0, subA, m_scale * m_world));
}
