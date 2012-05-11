#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::checkCollision(GameObject* _go1, GameObject* _go2)
{
	D3DXVECTOR3 goMin, goMax, go2Min, go2Max;
	goMin = _go1->getPos() + _go1->getMinCorner(); goMax = _go1->getPos() + (_go1->getMaxCorner()) ;
	go2Min = _go2->getPos() + _go2->getMinCorner(); go2Max = _go2->getPos() + (_go2->getMaxCorner()) ;

	if(goMin.x > go2Max.x || go2Min.x > goMin.x)
		return false;
	if(goMin.z > go2Max.z || go2Min.z > goMin.z)
		return false;

 	return true;
}