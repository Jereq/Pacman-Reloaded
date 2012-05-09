#pragma once

#include "Ghost.h"

class RandomGhost : public Ghost
{
private:

public:

	RandomGhost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~RandomGhost();

	void init();

	void update(float _deltaTime);
};