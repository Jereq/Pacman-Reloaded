#pragma once

#include <D3DX10math.h>

#include "../GameplayFoundations/GameObject.h"

enum FOODTYPE
{
	NORMAL,
	SPECIAL,
	POWERUPS,
	COUNT
};

class Food : public GameObject
{
private:
	UINT m_score;

	FOODTYPE m_type;
public:
	Food(D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max, FOODTYPE _type);
	virtual ~Food();

	void init();
	void update(float _deltaTime);

	void foodType(FOODTYPE _type);

	UINT getScore();
	FOODTYPE getType();
};