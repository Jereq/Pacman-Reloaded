#pragma once

#include "Actor.h"
#include "..\Resources\MTAModel.h"

class Ghost : public Actor
{	
private:

public:
	Ghost(Resources::MTAModel::ptr _model, D3DXVECTOR3 _pos);
	virtual ~Ghost();

	void init();
	void update(float _deltaTime);
	void draw(Graphics::dxManager* _dxManager);
};