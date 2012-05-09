#pragma once

#include <D3DX10math.h>

#include "../GameplayFoundations/GameObject.h"
#include "..\Resources\MTModel.h"

enum FOODTYPE
{
	NORMAL,
	SPECIAL,
	POWERUPS,
	//COUNT
};

class Food : public GameObject
{
private:
	Resources::MTModel::ptr m_model;
	
	UINT m_score;

	FOODTYPE m_type;
public:
	Food(Resources::MTModel::ptr _model, D3DXVECTOR3 _pos, FOODTYPE _type);
	virtual ~Food();

	void init();
	void update(float _deltaTime);
	void draw(Graphics::dxManager* _dxManager);

	void foodType(FOODTYPE _type);

	UINT getScore();
	FOODTYPE getType();
};