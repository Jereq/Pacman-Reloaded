#include "Ghost.h"

namespace Actors
{
	Ghost::Ghost(Resources::MTAModel::ptr _model, GameplayFoundations::CellIndex _pos, GameplayFoundations::Grid::ptr _grid) 
		: Actor(_model, _pos, _grid)
	{

	}

	Ghost::~Ghost()
	{

	}

	void Ghost::init(GameplayFoundations::CellIndex _target)
	{
		Actor::init();

		m_state = DEAD;
		m_speedFrenzy = 0.8f;

		m_aniNames = m_model->getAnimationNames();
		m_aniIndex =  m_model->getAnimationIndex(m_aniNames[0]);
		m_aniTime = m_model->getAnimationTime(m_aniIndex);

		D3DXMatrixScaling(&initScaleRotation, 0.35f, 0.35f, 0.35f);
		D3DXMATRIX rot;
		D3DXMatrixRotationY(&rot, (float)D3DX_PI);

		initScaleRotation = initScaleRotation * rot;

		D3DXVec3TransformCoord(&m_min, &m_min, &initScaleRotation);
		D3DXVec3TransformCoord(&m_max, &m_max, &initScaleRotation);

		if (m_max.x < m_min.x)
		{
			float tmp = m_max.x;
			m_max.x = m_min.x;
			m_min.x = tmp;
		}
		if (m_max.y < m_min.y)
		{
			float tmp = m_max.y;
			m_max.y = m_min.y;
			m_min.y = tmp;
		}
		if (m_max.z < m_min.z)
		{
			float tmp = m_max.z;
			m_max.z = m_min.z;
			m_min.z = tmp;
		}


		grid->findPath(fromCell, _target, path);
		toCell = path[1];
		setDir(path[2]);
	}

	void Ghost::update(float _deltaTime, GameplayFoundations::CellIndex _target)
	{
		GameplayFoundations::CellIndex currentTo = toCell;

		Actor::update(_deltaTime);
		
		if (!(currentTo == toCell))
		{
			path.clear();
			grid->findPath(toCell, _target, path);
			GameplayFoundations::CellIndex newTo = path[1];
			setDir(newTo);
		}
	}

	void Ghost::setDir(GameplayFoundations::CellIndex _c)
	{
		if(toCell.u > _c.u)
		{
			setDirection(DIR_RIGHT);
		}
		if(toCell.u < _c.u)
		{
			setDirection(DIR_LEFT);
		}
		if(toCell.v > _c.v)
		{
			setDirection(DIR_DOWN);
		}
		if(toCell.v < _c.v)
		{
			setDirection(DIR_UP);
		}
	}

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
	
		_dxManager->AddDynamicObject(Graphics::dynamicObject(m_model, time, 0, subA, initScaleRotation * m_scale * m_world));
	}
}
