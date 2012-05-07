#pragma once

#include "..\GameplayFoundations\GameObject.h"

class Player : public GameObject
{
private:
	//PLAYERSTATE m_state;

	UINT m_score;

	//float m_speed;
	//float m_initSpeed;

public:
	Player(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	~Player();

	void init();

	bool beEatingOrNot();

	void movement();

	//void changeState(GO_STATE _goState);

	//GO_STATE getState();

	void setScore(int _score);
	UINT getScore();
};