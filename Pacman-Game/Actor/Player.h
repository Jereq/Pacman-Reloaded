#pragma once

#include "Actor.h"

class Player : public Actor
{
private:
	UINT m_scoreAmount;

public:
	Player(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos);
	~Player();

	void init();

	bool beEatingOrNot();

	void movement();

	void setScore(int _score);
	UINT getScore();
};