#pragma once

#include "Ghost.h"

class HuntGhost : public Ghost
{
private:

public:

	HuntGhost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	virtual ~HuntGhost();

	void init();

	void update(float _deltaTime);
};