#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <D3DX10.h>
#include "..\vertexTypes.h"
#include <boost\shared_ptr.hpp>

namespace Resources
{
	struct Animation
	{
		std::string name;
		float time;
		int seqCount;
		std::vector<int> sequence;
	};


	struct MTA
	{
		typedef boost::shared_ptr<MTA> ptr;

		std::vector<Animation> animations;
		std::string textureName;
		int indexCount;
		int objCount;
		int vertexCount;

		D3DXVECTOR3 vectorMin, vectorMax;

		ID3D10Buffer* vBuffer;
		ID3D10Buffer* iBuffer;
	};

	class mtaLoader
	{
	public:
		mtaLoader(ID3D10Device* pdevice);
		~mtaLoader();
		MTA::ptr loadmta(std::string fileName);

		//D3DXVECTOR3 

	private:
		ID3D10Device* device;
		int pos, indCount, animCount;
		std::ifstream file;

		int  byteToInt();
		std::string byteToString(int strLength);
		float byteToFloat();
		void loadHeader(const MTA::ptr &m);
		void loadAnimations(const MTA::ptr &m);
		void loadIndices(const MTA::ptr &m);
		void loadVertices(const MTA::ptr &m);

		void findMinMax(const MTA::ptr &m, D3DXVECTOR3 _vector3);
	};
}