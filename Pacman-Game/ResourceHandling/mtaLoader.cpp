#include "mtaLoader.h"

namespace Resources
{
	mtaLoader::mtaLoader(ID3D10Device* pdevice) : pos(0), indCount(0), animCount(0)
	{
		device = pdevice;
	}

	mtaLoader::~mtaLoader()
	{

	}

	MTA::ptr mtaLoader::loadmta(std::string fileName)
	{
		MTA::ptr m(new MTA());

		file.open( fileName, std::ios::in | std::ios::binary );

		if(!file.is_open())
		{
			MessageBox( 0, "Could not open .mta file", 0, 0 );
			return m;
		}

		m->vectorMin = D3DXVECTOR3(0,0,0);
		m->vectorMax = D3DXVECTOR3(0,0,0);

		//Header
		loadHeader(m);
		//Animations
		loadAnimations(m);
		//Indices
		loadIndices(m);
		//Vertices
		loadVertices(m);

		file.close();

		return m;

	}

	void mtaLoader::loadHeader(const MTA::ptr &m)
	{
		//OBJ file Count
		m->objCount = byteToInt();
		//Indices Count
		m->indexCount = byteToInt();
		//Vertices Count
		m->vertexCount = byteToInt();
		//Texture Name String Length
		int textstrLength	= 0;
		textstrLength = byteToInt();
		//Texture file name
		m->textureName = byteToString(textstrLength);
		//Animations Count
		animCount = byteToInt();
	}

	void mtaLoader::loadAnimations(const MTA::ptr &m)
	{
		m->animations.reserve( animCount );

		for(int i = 0; i < animCount; i++)
		{
			Animation a;
			//Animation Name Length
			int animNameLength = 0;
			animNameLength = byteToInt();

			//Animation Name
			a.name = byteToString(animNameLength);

			//Animation Time
			a.time = byteToFloat();

			//Animation Sequence Count
			a.seqCount = byteToInt();

			//Animation Sequence
			for(int i = 0; i < a.seqCount; i++)
			{
				a.sequence.push_back(byteToInt());
			}
			m->animations.push_back(a);
		}
	}

	void mtaLoader::loadIndices(const MTA::ptr &m)
	{
		std::vector<DWORD> indices;
		indices.reserve(m->indexCount*m->objCount);

		for(int i = 0; i < m->indexCount*m->objCount; i++)
		{
			indices.push_back(byteToInt());
		}

		D3D10_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.BindFlags = D3D10_BIND_SHADER_RESOURCE;
		bd.ByteWidth = sizeof(DWORD)*((m->indexCount * m->objCount)/3);
		bd.CPUAccessFlags = 0;
		bd.Usage = D3D10_USAGE_DEFAULT;
		D3D10_SUBRESOURCE_DATA data;
		data.pSysMem = indices.data();
		device->CreateBuffer( &bd, &data, &m->iBuffer );
	}

	void mtaLoader::loadVertices(const MTA::ptr &m)
	{
		std::vector<vertex> vertices;
		vertices.reserve(m->vertexCount);
		for(int i = 0; i < m->vertexCount; i++)
		{
			vertex v;

			v.pos.x = byteToFloat();
			v.pos.y = byteToFloat();
			v.pos.z = byteToFloat();

			v.normal.x = byteToFloat();
			v.normal.y = byteToFloat();
			v.normal.z = byteToFloat();

			v.texCoords.x = byteToFloat();
			v.texCoords.y = byteToFloat();

			vertices.push_back(v);

			findMinMax(m, v.pos);
		}

		D3D10_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.BindFlags = D3D10_BIND_SHADER_RESOURCE;
		bd.ByteWidth = sizeof(vertex)*( m->vertexCount );
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		bd.Usage = D3D10_USAGE_DYNAMIC;
		D3D10_SUBRESOURCE_DATA data;
		data.pSysMem = vertices.data();
		device->CreateBuffer( &bd, &data, &m->vBuffer );
	}

	void mtaLoader::findMinMax(const MTA::ptr &m, D3DXVECTOR3 _vector3)
	{
		if(m->vectorMin.x > _vector3.x)
			m->vectorMin.x = _vector3.x;
		if(m->vectorMin.y > _vector3.y)
			m->vectorMin.y = _vector3.y;
		if(m->vectorMin.z > _vector3.z)
			m->vectorMin.z = _vector3.z;

		if(m->vectorMax.x < _vector3.x)
			m->vectorMax.x = _vector3.x;
		if(m->vectorMax.y < _vector3.y)
			m->vectorMax.y = _vector3.y;
		if(m->vectorMax.z < _vector3.z)
			m->vectorMax.z = _vector3.z;
	}

	int mtaLoader::byteToInt()
	{
		char b[4];
		int temp = 0;;

		file.read( b, sizeof(int) );
		memcpy( &temp, b, sizeof(int) );

		return temp;
	}

	float mtaLoader::byteToFloat()
	{
		char b[4];
		float temp = 0;;

		file.read( b, sizeof(float) );
		memcpy( &temp, b, sizeof(float) );

		return temp;
	}

	std::string mtaLoader::byteToString(int strLength)
	{
		pos = (int)file.tellg();
		file.seekg( pos + 1 );
		char* c = new char[strLength];
		file.read( c, strLength);
		std::string s(c, strLength);
	
		return s;
	}
}