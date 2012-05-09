#pragma once

#include "Actor.h"

class Ghost : public Actor
{	
private:

public:
	Ghost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos);
	virtual ~Ghost();

	void init();

	void update(float _deltaTime);
};