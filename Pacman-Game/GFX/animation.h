#pragma once

#include "dxManager.h"

namespace Graphics
{
	class Animation
	{
	public:

		Animation(Resources::MTA::ptr _mta);
		void Draw(float _t);

	private:

		Resources::MTA::ptr mta;
	};
}