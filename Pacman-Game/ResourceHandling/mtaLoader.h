#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <D3DX10.h>
#include "..\vertexTypes.h"


struct Animation
{
	std::string name;
	float time;
	int seqCount;
	std::vector<int> sequence;
};


struct MeshData
{
	std::vector<Animation> animations;
	std::string textureName;
	int indexCount;

	ID3D10Buffer* vBuffer;
	ID3D10Buffer* iBuffer;
};

class mtaLoader
{
public:
	mtaLoader(ID3D10Device* pdevice);
	~mtaLoader();
	void loadmta(char* fileName);
private:
	ID3D10Device* device;
	int pos, objCount, vertCount, indCount, animCount;
	std::ifstream file;
	MeshData m;

	int  byteToInt();
	std::string byteToString(int strLength);
	float byteToFloat();
	void loadHeader();
	void loadAnimations();
	void loadIndices();
	void loadVertices();


};