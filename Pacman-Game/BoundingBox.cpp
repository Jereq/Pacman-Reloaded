#include "BoundingBox.h"

BoundingBox::BoundingBox()
{

}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::buildBoundingBox(D3DXVECTOR3 _min, D3DXVECTOR3 _max)
{
	m_index[NEAR_BOTTOMLEFT] = _min; m_index[FAR_TOPRIGHT] = _max;

	m_index[NEAR_BOTTOMRIGHT] = m_index[NEAR_BOTTOMLEFT]; m_index[NEAR_BOTTOMRIGHT].x += m_index[FAR_TOPRIGHT].x;
	m_index[NEAR_TOPLEFT] = m_index[NEAR_BOTTOMLEFT]; m_index[NEAR_TOPLEFT].y += m_index[FAR_TOPRIGHT].y;
	m_index[NEAR_TOPRIGHT] = m_index[FAR_TOPRIGHT]; m_index[NEAR_TOPRIGHT].z -= m_index[FAR_TOPRIGHT].z;

	m_index[FAR_BOTTOMLEFT] = m_index[NEAR_BOTTOMLEFT]; m_index[FAR_BOTTOMLEFT].z += m_index[FAR_TOPRIGHT].z;
	m_index[FAR_BOTTOMRIGHT] = m_index[NEAR_BOTTOMRIGHT]; m_index[FAR_BOTTOMRIGHT].z += m_index[FAR_TOPRIGHT].z;
	m_index[FAR_TOPLEFT] = m_index[NEAR_TOPLEFT]; m_index[FAR_TOPLEFT].z += m_index[FAR_TOPRIGHT].z;

	D3DXPlaneFromPoints(&m_planes[TOPPLANE], &m_index[NEAR_BOTTOMLEFT], &m_index[NEAR_BOTTOMRIGHT], &m_index[NEAR_TOPLEFT]);
}

D3DXVECTOR3 BoundingBox::getBoundingBox(int i)
{
	return m_index[i];
}

