#include "Player.h"

Player::Player(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos) 
	: Actor(_model, _pos)
{}

Player::~Player()
{}

void Player::init()
{
	Actor::init();

	m_state = ALIVE;

	m_speedInit = 4.f;
	m_speed = m_speedInit;
	m_speedFrenzy = m_speedInit * 1.2f;

	m_aniNames = m_model->getAnimationNames();
	m_aniIndex =  m_model->getAnimationIndex(m_aniNames[0]);
	m_aniTime = m_model->getAnimationTime(m_aniIndex);

	D3DXMatrixScaling(&m_scale, 0.7f, 0.7f, 0.7f);

	D3DXVec3TransformCoord(&m_min, &m_min, &m_scale);
	D3DXVec3TransformCoord(&m_max, &m_max, &m_scale);

	m_scoreAmount = 0;

	m_timer = 0;

	eatSound = Sound::SoundManager::getInstance()->getLoop("Sound Files/pacman_chomp.wav");
	eatSound->setMinDistance(5.f);
}

void Player::update(float _deltaTime)
{
	prevx = m_pos.x;
	prevz = m_pos.z;

	Actor::update(_deltaTime); 

	if (prevx != m_pos.x || prevz != m_pos.z)
	{
		eatSound->setPosition(m_pos);
		eatSound->start();
	}
	else
	{
		eatSound->pause();
	}
}

void Player::draw(Graphics::dxManager* _dxManager)
{
	static float time = 0;
	static int subA = 0;
	
	time += dt / m_aniTime;
	if (time >= 1)
	{
		time = 0;
		subA = 1 - subA;
	}
	
	_dxManager->AddDynamicObject(Graphics::dynamicObject(m_model, time, 0, subA,  m_world));
}

bool Player::beEatingOrNot()
{
	if(m_state == FRENZY)
	{
		return true;
	}

	//If it returns false will pacman die?
	changeState(DEAD);
	return false;
}

void Player::setScore(int _score)
{
	m_scoreAmount = _score;
}

UINT Player::getScore()
{
	return m_scoreAmount;
}