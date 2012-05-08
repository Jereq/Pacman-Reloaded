#include "MTLoader.h"

namespace Resources
{
	MTLoader::MTLoader() : device(NULL)
	{
	}

	MTLoader::~MTLoader()
	{
	}

	void MTLoader::startup(ID3D10Device* _device)
	{
		device = _device;
	}

	void MTLoader::shutdown()
	{
	}

	void MTLoader::loadMT(MTModel::ptr const& _model)
	{
		assert(_model);

		LoadData loadData;

		loadData.file.open( _model->getFilename(), std::ios::in | std::ios::binary );

		if(!loadData.file.is_open())
		{			
			MessageBox( 0, "Could not open .mt file", 0, 0 );
			return;
		}

		//Header
		loadHeader(loadData);
		//Vertices
		loadVertices(loadData);
		//Indices
		loadIndices(loadData);		

		loadData.file.close();

		createMesh(loadData, _model);

		return;
	}

	void MTLoader::loadHeader(LoadData& _loadData)
	{
		//Vertex count
		_loadData.vertexCount = byteToInt(_loadData.file);
		//Indices Count
		_loadData.indexCount = byteToInt(_loadData.file);
		//Texture Name String Length
		int textstrLength = byteToInt(_loadData.file);
		//Texture name
		_loadData.textureName = byteToString(textstrLength, _loadData.file);
	}

	void MTLoader::loadIndices(LoadData& _loadData)
	{
		_loadData.IB.reserve(_loadData.indexCount);

		for(int j = 0; j < _loadData.indexCount; j++)
		{
			_loadData.IB.push_back(byteToInt(_loadData.file));
		}
	}

	void MTLoader::loadVertices(LoadData& _loadData)
	{
		_loadData.VB.reserve(_loadData.vertexCount);
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

			_loadData.VB.push_back(v);
			findMinMax(_loadData, v.pos);
		}
	}

	void MTLoader::createMesh(LoadData& _loadData, MTModel::ptr const& _model)
	{
		ID3DX10Mesh* mesh;
		D3DX10CreateMesh(device, Resources::vertexInputLayout, Resources::simpleVertexInputLayoutNumElements,
			"POSITION", _loadData.VB.size(), _loadData.IB.size(), 0, &mesh);

		mesh->SetVertexData(NULL, _loadData.VB.data());
		mesh->SetIndexData(_loadData.IB.data(), _loadData.IB.size());		

		_model->setTextureName(_loadData.textureName);
		_model->setBoundingBox(_loadData.minPos, _loadData.maxPos);
	}

	void MTLoader::findMinMax(LoadData& _loadData, D3DXVECTOR3 _vector3)
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

	int MTLoader::byteToInt(std::ifstream& _file)
	{
		char b[4];
		int temp = 0;;

		_file.read( b, sizeof(int) );
		memcpy( &temp, b, sizeof(int) );

		return temp;
	}

	float MTLoader::byteToFloat(std::ifstream& _file)
	{
		char b[4];
		float temp = 0;;

		_file.read( b, sizeof(float) );
		memcpy( &temp, b, sizeof(float) );

		return temp;
	}

	std::string MTLoader::byteToString(int strLength, std::ifstream& _file)
	{
		int pos = (int)_file.tellg();
		_file.seekg( pos + 1 );
		char* c = new char[strLength];
		_file.read( c, strLength);
		std::string s(c, strLength);

		return s;
	}
}