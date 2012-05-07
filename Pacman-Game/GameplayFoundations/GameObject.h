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

	GO_STATE m_state;

	float m_speed, m_speedInit, m_speedFrenzy;
	float m_timer;

public:
	GameObject(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~GameObject();
	
	void init();
	void update(float _deltaTime);

	void changeState(GO_STATE _state);

	bool collision();
		
	void setSpeed(float _speed);
	void resetSpeed();

	D3DXVECTOR3 getPos();

	D3DXVECTOR3 getMinCorner();
	D3DXVECTOR3 getMaxCorner();

	GO_STATE getState();

private:
	void frenzyMode(float _deltaTime);
};