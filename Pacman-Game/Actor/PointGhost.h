#pragma once

#include "Ghost.h"

class PointGhost : public Ghost
{
private:

public:

	PointGhost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~PointGhost();

	void init();

	void update(float _deltaTime);
};