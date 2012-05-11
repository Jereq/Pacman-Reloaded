#pragma once

#include "Actor.h"
#include "..\Resources\MTAModel.h"
#include "../Sound/Loop.h"

class Player : public Actor
{
private:
	UINT m_scoreAmount;
	float prevx, prevz;

	Sound::Loop::ptr eatSound;

public:
	Player(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos);
	~Player();

	void init();
	void update(float _deltaTime);

	void draw(Graphics::dxManager* _dxManager);

	bool beEatingOrNot();

	void setScore(int _score);
	UINT getScore();
};