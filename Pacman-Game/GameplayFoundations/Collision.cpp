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
	goMin = _go1->getPos() + _go1->getMinCorner(); goMax = _go1->getPos() + _go1->getMaxCorner();
	go2Min = _go2->getPos() + _go2->getMinCorner(); go2Max = _go2->getPos() + _go2->getMaxCorner();

	if(goMin.x > go2Max.x || go2Min.x > goMin.x)
		return false;
	if(goMin.z > go2Max.z || go2Min.z > goMin.z)
		return false;

	return true;
}

//bool Collision::checkCollision(D3DXVECTOR3 _mainPos, D3DXVECTOR3 _mainMinCorner, D3DXVECTOR3 _mainMaxCorner,
//						D3DXVECTOR3 _pos, D3DXVECTOR3 _minCorner, D3DXVECTOR3 _maxCorner)
//{
//	//POSSIBLY SOME ERRORS HERE
//	//basic math
//	_mainMinCorner += _mainPos; _mainMaxCorner += _mainPos;
//	_minCorner += _pos; _maxCorner += _pos;
//
//	if(_mainMinCorner.x < _minCorner.x && _mainMaxCorner.x > _minCorner.x &&
//		_mainMinCorner.z < _minCorner.z && _mainMaxCorner.z > _minCorner.z)
//	{
//		return true;
//	}
//	if(_mainMinCorner.x < _maxCorner.x && _mainMaxCorner.x > _maxCorner.x &&
//		_mainMinCorner.z < _maxCorner.z && _mainMaxCorner.z > _maxCorner.z)
//	{
//		return true;
//	}
//
//	return false;
//}