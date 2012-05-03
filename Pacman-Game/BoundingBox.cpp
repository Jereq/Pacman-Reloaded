#include "BoundingBox.h"

BoundingBox::BoundingBox()
{

}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::buildBoundingBox(D3DXVECTOR3 _min, D3DXVECTOR3 _max)
{
	m_index[0] = _min; m_index[7] = _max;

	m_index[1] = m_index[0]; m_index[1].x += m_index[7].x;
	m_index[2] = m_index[0]; m_index[2].y += m_index[7].y;
	m_index[3] = m_index[7]; m_index[3].z -= m_index[7].z;

	m_index[4] = m_index[0]; m_index[4].z += m_index[7].z;
	m_index[5] = m_index[1]; m_index[5].z += m_index[7].z;
	m_index[6] = m_index[2]; m_index[6].z += m_index[7].z;
}

D3DXVECTOR3 BoundingBox::getBoundingBox(int i)
{
	return m_index[i];
}

