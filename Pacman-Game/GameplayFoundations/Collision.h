#pragma once

#include <D3DX10math.h>

class Collision
{
private:

public:
	Collision();
	~Collision();

	bool checkCollision(D3DXVECTOR3 _mainPos, D3DXVECTOR3 _mainMin, D3DXVECTOR3 _mainMax,
						D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max);
};