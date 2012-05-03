#pragma once
//create a basic vertex type

#include <D3DX10.h>

namespace Resources
{
	struct vertex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 texCoords;


		vertex () : normal( D3DXVECTOR3(0,0,0) )
		{			
		}

		vertex( D3DXVECTOR3 p, D3DXVECTOR3 n ) : pos(p), normal(n)
		{		
		}	

		vertex( D3DXVECTOR3 p, D3DXVECTOR2 t, D3DXVECTOR3 n ) : pos(p), normal(n), texCoords(t)
		{
		}	
	};

	struct doubleVertex
	{
		D3DXVECTOR3 pos0, pos1;
		D3DXVECTOR3 normal0, normal1;
		D3DXVECTOR2 texCoords0, texCoords1;

		doubleVertex( D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 n0, D3DXVECTOR3 n1, D3DXVECTOR2 t0, D3DXVECTOR2 t1 )
		{
			pos0 = p0;
			pos1 = p1;
			normal0 = n0;
			normal1 = n1;
			texCoords0 = t0;
			texCoords1 = t1;
		}

		doubleVertex(vertex const& _v0, vertex const& _v1)
		{
			pos0 = _v0.pos;
			pos1 = _v1.pos;
			normal0 = _v0.normal;
			normal1 = _v1.normal;
			texCoords0 = _v0.texCoords;
			texCoords1 = _v1.texCoords;
		}
	};

	const D3D10_INPUT_ELEMENT_DESC vertexInputLayout[] = 
	{	
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 }	
	};

	const int vertexInputLayoutNumElements = sizeof(vertexInputLayout)/sizeof(vertexInputLayout[0]);
}