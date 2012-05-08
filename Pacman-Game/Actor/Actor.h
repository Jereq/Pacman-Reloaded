#pragma once

#include "..\GameplayFoundations\GameObject.h"

enum ACTOR_STATE
{
	ALIVE,
	DEAD,
	FRENZY,
	COUNT
};


class Actor : public GameObject
{
protected:
	ACTOR_STATE m_state;
	float m_speed, m_speedInit, m_speedFrenzy;

public:
	Actor(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~Actor();

	void init();
	void update(float _deltatime);

	void changeState(ACTOR_STATE _state);

	void collision();

	void setSpeed(float _speed);
	void resetSpeed();

	D3DXVECTOR3 getPos();

	D3DXVECTOR3 getMinCorner();
	D3DXVECTOR3 getMaxCorner();

	ACTOR_STATE getState();

private:
	void frenzyMode(float d_deltaTime);
};