#pragma once

#include "Actor.h"

//enum GHOSTSTATE
//{
//	ALIVE,
//	DEAD,
//	ESCAPE,
//	COUNT
//};

class Ghost : public Actor
{	
private:
	//GHOSTSTATE m_state;

public:
	Ghost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~Ghost();

	void init();

	void update(float _deltaTime);

	//void changeState(GHOSTSTATE _state);

	//GHOSTSTATE getState();



};