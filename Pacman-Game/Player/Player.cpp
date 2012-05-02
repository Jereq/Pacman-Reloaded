#include "Player.h"

Player::Player(D3DXVECTOR3 _pos)
{
	m_state = ALIVE;
	m_pos = _pos;

	m_initSpeed = 1.f;
	m_speed = m_initSpeed;
}

Player::~Player()
{

}

bool Player::eatingTime()
{
	if(m_state == FRENZY)
	{
		return true;
	}

	//If it returns false will pacman die?
	//m_state = DEAD;
	return false;
}

void Player::changeState(PLAYERSTATE _state)
{
	switch(_state)
	{
	case ALIVE:
		m_state = ALIVE;
		resetSpeed();
		break;

	case DEAD:
		m_state = DEAD;
		break;

	case FRENZY:
		m_state = FRENZY;
		setSpeed(2.0f);
		break;

	//case COUNT:
	//	break;
	}
}

PLAYERSTATE Player::getState()
{
	return m_state;
}

void Player::setScore(int _score)
{
	m_score = _score;
}

UINT Player::getScore()
{
	return m_score;
}

void Player::setSpeed(float _speed)
{
	m_speed = _speed;
}

void Player::resetSpeed()
{
	m_speed = m_initSpeed;
}

D3DXVECTOR3 Player::getPos()
{
	return m_pos;
}

