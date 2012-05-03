#pragma once

#include "..\GameplayFoundations\GameObject.h"

enum PLAYERSTATE
{
	ALIVE,
	DEAD,
	FRENZY,
	COUNT
};

class Player : public GameObject
{
private:
	PLAYERSTATE m_state;

	UINT m_score;

	float m_speed;
	float m_initSpeed;

	float m_timer;


public:
	Player(D3DXVECTOR3 _pos);
	~Player();

	void init();

	bool collisionGhost();
	bool collision();

	void movement();

	void changeState(PLAYERSTATE _ps);

	PLAYERSTATE getState();

	void setScore(int _score);
	UINT getScore();
};