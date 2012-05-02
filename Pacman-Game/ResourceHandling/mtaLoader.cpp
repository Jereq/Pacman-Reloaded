#include "mtaLoader.h"

mtaLoader::mtaLoader(ID3D10Device* pdevice) : pos(0), objCount(0), vertCount(0), indCount(0), animCount(0)
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
	objCount = byteToInt();
	//Indices Count
	m->indexCount = byteToInt();
	//Vertices Count
	vertCount = byteToInt();
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
	indices.reserve(m->indexCount*objCount);

	for(int i = 0; i < m->indexCount*objCount; i++)
	{
		indices.push_back(byteToInt());
	}

	D3D10_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	bd.ByteWidth = sizeof(DWORD)*((m->indexCount * objCount)/3);
	bd.CPUAccessFlags = 0;
	bd.Usage = D3D10_USAGE_DEFAULT;
	D3D10_SUBRESOURCE_DATA data;
	data.pSysMem = indices.data();
	device->CreateBuffer( &bd, &data, &m->iBuffer );
}

void mtaLoader::loadVertices(const MTA::ptr &m)
{
	std::vector<vertex> vertices;
	vertices.reserve(vertCount);
	for(int i = 0; i < vertCount; i++)
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
	}
	D3D10_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.ByteWidth = sizeof(vertex)*( vertCount );
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	D3D10_SUBRESOURCE_DATA data;
	data.pSysMem = vertices.data();
	device->CreateBuffer( &bd, &data, &m->vBuffer );
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