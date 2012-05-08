#include "mtaLoader.h"

namespace Resources
{
	mtaLoader::mtaLoader()
		: device(NULL)
	{
	}

	mtaLoader::~mtaLoader()
	{
	}

	void mtaLoader::startup(ID3D10Device* _device)
	{
		device = _device;
	}

	void mtaLoader::shutdown()
	{
	}

	void mtaLoader::loadmta(MTAModel::ptr const& _model)
	{
		assert(_model);
		
		LoadData loadData;

		loadData.file.open( _model->getFilename(), std::ios::in | std::ios::binary );

		if(!loadData.file.is_open())
		{
			MessageBox( 0, "Could not open .mta file", 0, 0 );
			return;
		}

		//Header
		loadHeader(loadData);
		//Animations
		loadAnimations(loadData);
		//Indices
		loadIndices(loadData);
		//Vertices
		loadVertices(loadData);

		loadData.file.close();

		createVertexBuffers(loadData, _model);

		return;
	}

	void mtaLoader::loadHeader(LoadData& _loadData)
	{
		//OBJ file Count
		_loadData.objCount = byteToInt(_loadData.file);
		//Indices Count
		_loadData.indexCount = byteToInt(_loadData.file);
		//Vertices Count
		_loadData.vertexCount = byteToInt(_loadData.file);
		//Texture Name String Length
		int textstrLength = byteToInt(_loadData.file);
		//Texture name
		_loadData.textureName = byteToString(textstrLength, _loadData.file);
		//Animations Count
		_loadData.animCount = byteToInt(_loadData.file);
	}

	void mtaLoader::loadAnimations(LoadData& _loadData)
	{
		_loadData.animations.reserve( _loadData.animCount );

		for(int i = 0; i < _loadData.animCount; i++)
		{
			AnimationData a;
			//Animation Name Length
			int animNameLength = byteToInt(_loadData.file);

			//Animation Name
			a.name = byteToString(animNameLength, _loadData.file);

			//Animation Time
			a.time = byteToFloat(_loadData.file);

			//Animation Sequence Count
			int tmp = byteToInt(_loadData.file);

			//Animation Sequence
			for(int i = 0; i < tmp; i++)
			{
				a.sequence.push_back(byteToInt(_loadData.file));
			}

			_loadData.animations.push_back(a);
		}
	}

	void mtaLoader::loadIndices(LoadData& _loadData)
	{
		for (int i = 0; i < _loadData.objCount; i++)
		{
			std::vector<int> indices;
			indices.reserve(_loadData.indexCount);

			for(int j = 0; j < _loadData.indexCount; j++)
			{
				indices.push_back(byteToInt(_loadData.file));
			}

			_loadData.tmpIBuffer.push_back(indices);
		}
	}

	void mtaLoader::loadVertices(LoadData& _loadData)
	{
		_loadData.globalVB.reserve(_loadData.vertexCount);
		for(int i = 0; i < _loadData.vertexCount; i++)
		{
			vertex v;

			v.pos.x = byteToFloat(_loadData.file);
			v.pos.y = byteToFloat(_loadData.file);
			v.pos.z = byteToFloat(_loadData.file);

			v.normal.x = byteToFloat(_loadData.file);
			v.normal.y = byteToFloat(_loadData.file);
			v.normal.z = byteToFloat(_loadData.file);

			v.texCoords.x = byteToFloat(_loadData.file);
			v.texCoords.y = byteToFloat(_loadData.file);

			_loadData.globalVB.push_back(v);
			findMinMax(_loadData, v.pos);
		}
	}

	void mtaLoader::createVertexBuffers(LoadData& _loadData, MTAModel::ptr const& _model)
	{
		std::vector<UINT16> indexBuff;
		indexBuff.reserve(_loadData.indexCount);

		for (int i = 0; i < _loadData.indexCount; i++)
		{
			indexBuff.push_back(i);
		}

		std::vector<MTAModel::Animation> animationsRes;
		animationsRes.reserve(_loadData.animations.size());

		BOOST_FOREACH(AnimationData &a, _loadData.animations )
		{
			MTAModel::Animation animRes;
			animRes.name = a.name;
			animRes.time = a.time;
			animRes.subAnimations.reserve(a.sequence.size() - 1);

			for (size_t i = 0; i < a.sequence.size() - 1; i++ )
			{
				std::vector<int>& tmpb1 = _loadData.tmpIBuffer[a.sequence[i]];
				std::vector<int>& tmpb2 = _loadData.tmpIBuffer[a.sequence[i + 1]];

				std::vector<doubleVertex> tmp;
				tmp.reserve(_loadData.indexCount);

				for (int j = 0; j < _loadData.indexCount; j++ )
				{
					vertex &v1 = _loadData.globalVB[tmpb1[j]];
					vertex &v2 = _loadData.globalVB[tmpb2[j]];
					doubleVertex d(v1, v2);
					tmp.push_back(d);
				}

				ID3DX10Mesh* mesh;
				D3DX10CreateMesh(device, Resources::doubleVertexInputLayout, Resources::doubleVertexInputLayoutNumElements,
					"POSITION", tmp.size(), indexBuff.size(), 0, &mesh);

				mesh->SetVertexData(NULL, tmp.data());
				mesh->SetIndexData(indexBuff.data(), indexBuff.size());

				animRes.subAnimations.push_back(mesh);
			}

			animationsRes.push_back(animRes);
		}

		_model->setTextureName(_loadData.textureName);
		_model->setAnimations(animationsRes);
		_model->setBoundingBox(_loadData.minPos, _loadData.maxPos);
	}

	void mtaLoader::findMinMax(LoadData& _loadData, D3DXVECTOR3 _vector3)
	{
		if(_loadData.minPos.x > _vector3.x)
			_loadData.minPos.x = _vector3.x;
		if(_loadData.minPos.y > _vector3.y)
			_loadData.minPos.y = _vector3.y;
		if(_loadData.minPos.z > _vector3.z)
			_loadData.minPos.z = _vector3.z;

		if(_loadData.maxPos.x < _vector3.x)
			_loadData.maxPos.x = _vector3.x;
		if(_loadData.maxPos.y < _vector3.y)
			_loadData.maxPos.y = _vector3.y;
		if(_loadData.maxPos.z < _vector3.z)
			_loadData.maxPos.z = _vector3.z;
	}

	int mtaLoader::byteToInt(std::ifstream& _file)
	{
		char b[4];
		int temp = 0;;

		_file.read( b, sizeof(int) );
		memcpy( &temp, b, sizeof(int) );

		return temp;
	}

	float mtaLoader::byteToFloat(std::ifstream& _file)
	{
		char b[4];
		float temp = 0;;

		_file.read( b, sizeof(float) );
		memcpy( &temp, b, sizeof(float) );

		return temp;
	}

	std::string mtaLoader::byteToString(int strLength, std::ifstream& _file)
	{
		int pos = (int)_file.tellg();
		_file.seekg( pos + 1 );
		char* c = new char[strLength];
		_file.read( c, strLength);
		std::string s(c, strLength);
	
		return s;
	}
}