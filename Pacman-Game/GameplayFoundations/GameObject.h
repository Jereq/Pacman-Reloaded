#pragma once

#include <D3DX10math.h>
#include "../BoundingBox.h"



class GameObject
{
protected:
	D3DXVECTOR3 m_pos, m_min, m_max;

	float m_timer;

public:
	GameObject(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~GameObject();
	
	void init();
	void update(float _deltaTime);

	bool collision();

	D3DXVECTOR3 getPos();

	D3DXVECTOR3 getMinCorner();
	D3DXVECTOR3 getMaxCorner();

private:
};