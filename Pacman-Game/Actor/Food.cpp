#include "Food.h"

Food::Food(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max, FOODTYPE _type)
	: GameObject(_pos, _min, _max)
{
	m_type = _type;
}

Food::~Food()
{

}

void Food::init()
{

}

void Food::foodType(FOODTYPE _type)
{
	m_type = _type;
	switch(m_type)
	{
	case NORMAL:
		m_score = 1;
		break;

	case SPECIAL:
		m_score = 10;
		break;

	case POWERUPS:
		//m_score = 5;
		break;
	}

}

void Food::update(float _deltaTime)
{

}

UINT Food::getScore()
{
	return m_score;
}