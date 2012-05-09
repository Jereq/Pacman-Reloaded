#pragma once

#include "..\GameplayFoundations\GameObject.h"
#include "..\Resources\MTAModel.h"

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
	Resources::MTAModel::ptr m_model;

	ACTOR_STATE m_state;
	float m_speed, m_speedInit, m_speedFrenzy;
	
	float m_timer, m_time;

public:
	Actor(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos);
	virtual ~Actor();

	void init();
	void update(float _deltatime);
	void draw(Graphics::dxManager* _dxManager);

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