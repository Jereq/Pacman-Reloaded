#pragma once

#include "Ghost.h"

class RandomGhost : public Ghost
{
private:

public:

	RandomGhost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos);
	virtual ~RandomGhost();

	void init();

	void update(float _deltaTime);
};