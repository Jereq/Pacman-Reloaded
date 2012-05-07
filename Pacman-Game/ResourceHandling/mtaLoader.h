#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <D3DX10.h>
#include "vertexTypes.h"
#include <boost\shared_ptr.hpp>
#include <boost\foreach.hpp>
#include "ResourceManager.h"

namespace Resources
{
	struct Animation
	{
		std::string name;
		float time;
		std::vector<int> sequence;
		std::vector<ID3DX10Mesh*> subAnimation;
	};


	struct MTA
	{
		typedef boost::shared_ptr<MTA> ptr;

		std::vector<Animation> animations;
		Resources::Texture::ptr texture;
		int indexCount;
		int objCount;
		int vertexCount;
		D3DXVECTOR3 vectorMin, vectorMax;

	};

	class mtaLoader
	{
	public:
		mtaLoader(ID3D10Device* pdevice, Resources::ResourceManager::ptr _res);
		~mtaLoader();
		MTA::ptr loadmta(std::string fileName);

		//D3DXVECTOR3 

	private:

		typedef std::vector<int> indexv;
		Resources::ResourceManager::ptr res;

		ID3D10Device* device;
		int pos, indCount, animCount;
		std::ifstream file;

		std::vector<vertex> globalVB;
		std::vector<indexv> tmpIBuffer;

		int  byteToInt();
		std::string byteToString(int strLength);
		float byteToFloat();
		void loadHeader(const MTA::ptr &m);
		void loadAnimations(const MTA::ptr &m);
		void loadIndices(const MTA::ptr &m);
		void loadVertices(const MTA::ptr &m);
		void createVertexBuffers(const MTA::ptr &m);
		void findMinMax(const MTA::ptr &m, D3DXVECTOR3 _vector3);
	};
}