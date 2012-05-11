#include "Actor.h"

namespace Actors
{
	Actor::Actor(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid)
		 : GameplayFoundations::GameObject()
	{
		m_model = _model;
		grid = _grid;
		fromCell = _pos;
	}

	Actor::~Actor()
	{

	}

	void Actor::init()
	{
		GameplayFoundations::GameObject::init();

		m_pos.x = fromCell.u + 0.5f;
		m_pos.z = fromCell.v + 0.5f;
		m_pos.y = 0.5f;

		toCell = fromCell;

		m_min = m_model->getbbMin();
		m_max = m_model->getbbMax();

		currentRelPos = 0;

		D3DXMatrixIdentity(&rotation);
		D3DXMatrixIdentity(&m_scale);
	}

	void Actor::update(float _deltaTime)
	{
		dt = _deltaTime;	

		if(m_state == FRENZY)
		{
			frenzyMode(_deltaTime);
		}

		if(fromCell == toCell)
		{
			changeDirection();
		}
		else
		{
			currentRelPos += m_speed * _deltaTime;

			if (currentRelPos >= 1)
			{
				currentRelPos -= 1;
				changeDirection();
			}
		}

		if (!(fromCell == toCell))
		{
			moveDirection();
		}

		D3DXMATRIX tmp;

		D3DXMatrixTranslation(&tmp, m_pos.x, m_pos.y, m_pos.z);

		m_world = rotation * tmp;
	}

	void Actor::changeState(ACTOR_STATE _state)
	{
		switch(_state)
		{
		case ALIVE:
			m_timer = 0;
			resetSpeed();
			m_state = ALIVE;
			break;

		case DEAD:
			m_state = DEAD;
			break;

		case FRENZY:
			setSpeed(m_speedFrenzy);
			m_state = FRENZY;
			break;
		//case COUNT:
		//	break;
		}

		//It would be neat with an Observer here
		//signed
	}

	void Actor::setDirection(DIRECTION _direction)
	{
		GameplayFoundations::Paths p = grid->getOpenPaths(toCell);

		switch(_direction)
		{
		case DIR_RIGHT:
			if(p.pU)
				m_direction = _direction;
			break;

		case DIR_LEFT:
			if(p.nU)
				m_direction = _direction;
			break;

		case DIR_DOWN:
			if(p.nV)
				m_direction = _direction;
			break;

		case DIR_UP:
			if(p.pV)
				m_direction = _direction;
			break;
		}
	}

	void Actor::changeDirection()
	{
		fromCell = toCell;
		GameplayFoundations::Paths p = grid->getOpenPaths(fromCell);

		if(m_direction == DIR_RIGHT && p.pU)
		{
			toCell.u += 1;
		}
		else if(m_direction == DIR_LEFT && p.nU)
		{
			toCell.u -= 1;
		}
		else if(m_direction == DIR_DOWN && p.nV)
		{
			toCell.v -= 1;
		}
		else if(m_direction == DIR_UP && p.pV)
		{
			toCell.v += 1;
		}
	}

	void Actor::moveDirection()
	{
		D3DXVECTOR3 from = D3DXVECTOR3(fromCell.u + 0.5f, 0.5f, fromCell.v + 0.5f);
		D3DXVECTOR3 to = D3DXVECTOR3(toCell.u + 0.5f, 0.5f, toCell.v + 0.5f);
		D3DXVECTOR3 look = to - from;
		D3DXVec3Normalize(&look, &look);

		float angle = atan2(look.x, look.z);

		D3DXMatrixRotationY(&rotation, angle);

		D3DXVec3Lerp(&m_pos, &from, &to, currentRelPos);
	}	

	void Actor::frenzyMode(float _deltaTime)
	{
		m_timer += _deltaTime;
		if(m_timer > 5.f)
		{
			changeState(ALIVE);
		}
	}

	void Actor::setSpeed(float _speed)
	{
		m_speed = _speed;
	}

	void Actor::resetSpeed()
	{
		m_speed = m_speedInit;
	}

	GameplayFoundations::CellIndex Actor::getToCell()
	{
		return toCell;
	}

	GameplayFoundations::CellIndex Actor::getFromCell()
	{
		return fromCell;
	}

	ACTOR_STATE Actor::getState()
	{
		return m_state;
	}
}