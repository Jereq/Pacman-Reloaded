#pragma once

#include "Ghost.h"

class PointGhost : public Ghost
{
private:

public:

	PointGhost(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~PointGhost();

};