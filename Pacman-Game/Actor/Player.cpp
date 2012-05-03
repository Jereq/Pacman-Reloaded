#include "Player.h"

Player::Player(D3DXVECTOR3 _pos) : GameObject(_pos)
{}

Player::~Player()
{}

void Player::init()
{
	GameObject::init();
	m_state = ALIVE;

	m_timer = 0;
}

bool Player::collisionGhost()
{
	if(m_state != FRENZY)
	{
		//If it returns false will pacman die?
		//m_state = DEAD;
		return true;
	}

	return false;
}

bool Player::collision()
{
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
		m_timer = 0;
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