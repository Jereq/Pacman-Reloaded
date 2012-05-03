#pragma once

#include <D3DX10math.h>

class BoundingBox
{
private:
	D3DXVECTOR3 m_index[8];

public:
	BoundingBox();
	~BoundingBox();

	void buildBoundingBox(D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	
	D3DXVECTOR3 getBoundingBox(int i);
};