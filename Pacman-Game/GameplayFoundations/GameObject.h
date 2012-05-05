#pragma once

#include <D3DX10math.h>
#include "../BoundingBox.h"

class GameObject
{
protected:
	D3DXVECTOR3 m_pos, m_min, m_max;

	//BoundingBox* m_aabb;

	float m_initSpeed, m_speed;

public:
	GameObject(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~GameObject();
	
	void init();
	void update();

	bool collision();
		
	void setSpeed(float _speed);
	void resetSpeed();

	D3DXVECTOR3 getPos();

	D3DXVECTOR3 getMinCorner();
	D3DXVECTOR3 getMaxCorner();
};