#pragma once

#include <D3DX10math.h>

class Collision
{
private:

public:
	Collision();
	~Collision();

	bool checkCollision(D3DXVECTOR3 _mainPos, D3DXVECTOR3 _mainMinCorner, D3DXVECTOR3 _mainMaxCorner,
						D3DXVECTOR3 _pos, D3DXVECTOR3 _minCorner, D3DXVECTOR3 _maxCorner);
};