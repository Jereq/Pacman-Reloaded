#include "Player.h"

Player::Player(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max) 
	: Actor(_model, _pos, _min, _max)
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

	m_scoreAmount = 0;

	m_timer = 0;
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