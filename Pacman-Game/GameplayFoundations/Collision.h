#pragma once

#include <D3DX10math.h>
#include "GameObject.h"

namespace GameplayFoundations
{
	class Collision
	{
	private:

	public:
		Collision();
		~Collision();

		bool checkCollision(GameObject* _go1, GameObject* _go2);
	};
}