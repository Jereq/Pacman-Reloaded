#pragma once

#include "Ghost.h"

class RandomGhost : public Ghost
{
private:

public:

	RandomGhost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~RandomGhost();

	void update(float _deltaTime);
};