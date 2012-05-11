#pragma once

#include "..\GameplayFoundations\GameObject.h"
#include "..\Resources\MTAModel.h"
#include "..\Sound\SoundManager.h"

enum ACTOR_STATE
{
	ALIVE,
	DEAD,
	FRENZY,
	COUNT
};

enum DIRECTION
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
};


class Actor : public GameObject
{
protected:
	Resources::MTAModel::ptr m_model;

	ACTOR_STATE m_state;
	float m_speed, m_speedInit, m_speedFrenzy;
	
	float m_timer, dt;
	
	float time;
	int subA;

	std::vector<std::string> m_aniNames;
	int m_aniIndex;
	float m_aniTime;

	D3DXMATRIX m_scale;
	

public:
	Actor(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos);
	virtual ~Actor();

	void init();
	void update(float _deltatime);

	void changeState(ACTOR_STATE _state);

	void setDirection(DIRECTION _direction);

	void moveDirection();

	void setSpeed(float _speed);
	void resetSpeed();

	ACTOR_STATE getState();

private:

	DIRECTION m_direction;
	
	void frenzyMode(float d_deltaTime);

};