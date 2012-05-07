#pragma once

#include <D3DX10math.h>
#include "../BoundingBox.h"

enum GO_STATE
{
	ALIVE,
	DEAD,
	FRENZY,
	COUNT
};

class GameObject
{
protected:
	D3DXVECTOR3 m_pos, m_min, m_max;

	//BoundingBox* m_aabb;

	GO_STATE m_state;

	float m_initSpeed, m_speed;

public:
	GameObject(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~GameObject();
	
	void init();
	void update();

	void changeState(GO_STATE _state);

	bool collision();
		
	void setSpeed(float _speed);
	void resetSpeed();

	D3DXVECTOR3 getPos();

	D3DXVECTOR3 getMinCorner();
	D3DXVECTOR3 getMaxCorner();

	GO_STATE getState();
};