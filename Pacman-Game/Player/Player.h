#pragma once

#include <Windows.h>
#include <d3dx10math.h>

enum PLAYERSTATE
{
	ALIVE,
	DEAD,
	FRENZY,
	COUNT
};

class Player
{
private:
	PLAYERSTATE m_state;

	UINT m_score;

	D3DXVECTOR3 m_pos;

	float m_speed;
	float m_initSpeed;


public:
	Player(D3DXVECTOR3 m_pos);
	~Player();

	bool eatingTime();

	void movement();

	void changeState(PLAYERSTATE _ps);

	PLAYERSTATE getState();

	void setScore(int _score);
	UINT getScore();

	void setSpeed(float _speed);
	void resetSpeed();

	D3DXVECTOR3 getPos();


};