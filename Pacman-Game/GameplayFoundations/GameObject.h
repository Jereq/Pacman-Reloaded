#pragma once

#include <D3DX10math.h>

class GameObject
{
protected:
	D3DXVECTOR3 m_pos;

	float m_initSpeed, m_speed;

public:
	GameObject(D3DXVECTOR3 _pos);
	virtual ~GameObject();
	
	void init();
		
	void setSpeed(float _speed);
	void resetSpeed();

	D3DXVECTOR3 getPos();
};