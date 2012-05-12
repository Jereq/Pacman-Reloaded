#pragma once

#include <D3DX10math.h>
#include "..\GFX\dxManager.h"
#include "CellIndex.h"

namespace GameplayFoundations
{
	class GameObject
	{
	protected:
		D3DXVECTOR3 m_pos, m_min, m_max;

		D3DXMATRIX m_world;

		float m_timer;

	public:
		GameObject();
		virtual ~GameObject();
	
		virtual void init();
		virtual void update(float _deltaTime) = 0;

		virtual D3DXVECTOR3 getPos();

		virtual D3DXVECTOR3 getMinCorner();
		virtual D3DXVECTOR3 getMaxCorner();

	private:
	};
}