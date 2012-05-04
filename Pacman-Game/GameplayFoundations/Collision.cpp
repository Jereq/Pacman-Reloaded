#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::checkCollision(D3DXVECTOR3 _mainPos, D3DXVECTOR3 _mainMin, D3DXVECTOR3 _mainMax,
						D3DXVECTOR3 _pos, D3DXVECTOR3 _min, D3DXVECTOR3 _max)
{
	//POSSIBLY SOME ERRORS HERE
	//basic math
	_mainMin += _mainPos; _mainMax += _mainPos;
	_min += _pos; _max += _pos;

	if(_mainMin.x < _min.x && _mainMax.x > _min.x &&
		_mainMin.z < _min.z && _mainMax.z > _min.z)
	{
		return true;
	}
	if(_mainMin.x < _max.x && _mainMax.x > _max.x &&
		_mainMin.z < _max.z && _mainMax.z > _max.z)
	{
		return true;
	}

	return false;
}