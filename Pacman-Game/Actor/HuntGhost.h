#pragma once

#include "Ghost.h"

class HuntGhost : public Ghost
{
private:

public:

	HuntGhost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~HuntGhost();

	void update(float _deltaTime);
};