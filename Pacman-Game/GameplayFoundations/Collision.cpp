#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::checkCollision(D3DXVECTOR3 _mainPos, D3DXVECTOR3 _mainMinCorner, D3DXVECTOR3 _mainMaxCorner,
						D3DXVECTOR3 _pos, D3DXVECTOR3 _minCorner, D3DXVECTOR3 _maxCorner)
{
	//POSSIBLY SOME ERRORS HERE
	//basic math
	_mainMinCorner += _mainPos; _mainMaxCorner += _mainPos;
	_minCorner += _pos; _maxCorner += _pos;

	if(_mainMinCorner.x < _minCorner.x && _mainMaxCorner.x > _minCorner.x &&
		_mainMinCorner.z < _minCorner.z && _mainMaxCorner.z > _minCorner.z)
	{
		return true;
	}
	if(_mainMinCorner.x < _maxCorner.x && _mainMaxCorner.x > _maxCorner.x &&
		_mainMinCorner.z < _maxCorner.z && _mainMaxCorner.z > _maxCorner.z)
	{
		return true;
	}

	return false;
}