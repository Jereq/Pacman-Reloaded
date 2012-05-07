#pragma once
#include <d3d10.h>

namespace Graphics
{
	struct DirectionalLight
	{
		D3DXVECTOR4 color;
		D3DXVECTOR3 direction;
	};

	struct Material
	{
		float ambient, diffuse, specular, shininess;
	};
}