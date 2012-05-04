#pragma once

#include <D3DX10math.h>

enum PLANENR
{
	TOPPLANE = 0,
	BOTTOMPLANE = 1,
	NEARPLANE,
	FARPLANE,
	LEFTPLANE,
	RIGHTPLANE,
	COUNTPLANE
};

enum CORNERS
{
	NEAR_BOTTOMLEFT,
	NEAR_BOTTOMRIGHT,
	NEAR_TOPLEFT,
	NEAR_TOPRIGHT,
	FAR_BOTTOMLEFT,
	FAR_BOTTOMRIGHT,
	FAR_TOPLEFT,
	FAR_TOPRIGHT
};

class BoundingBox
{
private:
	D3DXVECTOR3 m_index[8];
	D3DXPLANE m_planes[6];

public:
	BoundingBox();
	~BoundingBox();

	void buildBoundingBox(D3DXVECTOR3 _min, D3DXVECTOR3 _max);
	
	D3DXVECTOR3 getBoundingBox(int i);
};