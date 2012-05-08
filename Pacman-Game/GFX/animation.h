#pragma once

#include "dxManager.h"

namespace Graphics
{
	class Animation
	{
	public:

		Animation(Resources::MTAModel::ptr _mta);
		void Draw(float _t);

	private:

		Resources::MTAModel::ptr mta;
	};
}