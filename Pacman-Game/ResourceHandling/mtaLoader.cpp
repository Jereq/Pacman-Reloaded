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

		createVertexBuffers(m);

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
		for (int i = 0; i < m->objCount; i++)
		{
			std::vector<int> indices;
			indices.reserve(m->indexCount);

			for(int j = 0; j < m->indexCount; j++)
			{
				indices.push_back(byteToInt());
			}

			tmpIBuffer.push_back(indices);
		}
	}

	void mtaLoader::loadVertices(const MTA::ptr &m)
	{
		globalVB.reserve(m->vertexCount);
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

			globalVB.push_back(v);
			findMinMax(m, v.pos);
		}
	}

			

	void mtaLoader::createVertexBuffers(const MTA::ptr &m)
	{
		D3D10_BUFFER_DESC VertexbuffDesc;
		VertexbuffDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		VertexbuffDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		VertexbuffDesc.MiscFlags = 0;
		VertexbuffDesc.Usage = D3D10_USAGE_DYNAMIC;

		D3D10_BUFFER_DESC IndexBuffDesc;
		IndexBuffDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
		IndexBuffDesc.ByteWidth = sizeof(UINT) * m->indexCount;
		IndexBuffDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		IndexBuffDesc.MiscFlags = 0;
		IndexBuffDesc.Usage = D3D10_USAGE_DYNAMIC;

		std::vector<UINT> indexBuff;
		indexBuff.reserve(m->indexCount);

		for (int i = 0; i < m->indexCount; i++)
		{
			indexBuff.push_back(i);
		}

		BOOST_FOREACH(Animation &a , m->animations )
		{
			for (size_t i = 0; i < a.sequence.size() - 1; i++ )
			{
				std::vector<doubleVertex> tmp;
				subAnimation sa;
				std::vector<int> tmpb1 = tmpIBuffer[a.sequence[i]];
				std::vector<int> tmpb2 = tmpIBuffer[a.sequence[i + 1]];

				for (int j = 0; j < m->indexCount; j++ )
				{
					vertex &v1 = globalVB[tmpb1[j]];
					vertex &v2 = globalVB[tmpb2[j]];
					doubleVertex d(v1, v2);
					tmp.push_back(d);
				}

				D3D10_SUBRESOURCE_DATA data;
				data.pSysMem = tmp.data();
				VertexbuffDesc.ByteWidth = sizeof(doubleVertex) * tmp.size();
				device->CreateBuffer(&VertexbuffDesc, NULL, &sa.vBuffer);

				D3D10_SUBRESOURCE_DATA ind;
				ind.pSysMem = indexBuff.data();
				device->CreateBuffer(&IndexBuffDesc, &ind, &sa.iBuffer);

				a.subAni.push_back(sa);
			}
		}

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