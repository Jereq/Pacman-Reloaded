#pragma once

#include "../GameplayFoundations/GameObject.h"

enum AISTATE
{
	ALIVE,
	DEAD,
	ESCAPE,
	COUNT
};

class Ghost : public GameObject
{	
private:
	AISTATE m_state;

public:
	Ghost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~Ghost();

	void init();

	void update(float _deltaTime);

	void changeState(AISTATE _state);

};