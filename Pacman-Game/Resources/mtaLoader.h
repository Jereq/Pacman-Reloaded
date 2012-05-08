#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include <D3DX10.h>

#include <boost\shared_ptr.hpp>
#include <boost\foreach.hpp>

#include "vertexTypes.h"
#include "MTAModel.h"

namespace Resources
{
	const static float INFINITY = std::numeric_limits<float>::infinity();

	class mtaLoader
	{
	public:
		mtaLoader();
		~mtaLoader();
		void startup(ID3D10Device* pdevice);
		void shutdown();

		void loadmta(MTAModel::ptr const& _model);

	private:
		struct AnimationData
		{
			std::string name;
			float time;
			std::vector<int> sequence;
		};

		struct LoadData
		{
			std::ifstream file;

			int objCount;
			int indexCount;
			int vertexCount;
			int animCount;
			std::string textureName;
			std::vector<AnimationData> animations;

			typedef std::vector<int> indexv;
			std::vector<indexv> tmpIBuffer;

			std::vector<vertex> globalVB;

			D3DXVECTOR3 minPos, maxPos;

			LoadData()
				: objCount(0), indexCount(0), vertexCount(0), animCount(0),
				minPos(INFINITY, INFINITY, INFINITY),
				maxPos(-INFINITY, -INFINITY, -INFINITY)
			{
			}
		};

		ID3D10Device* device;

		int  byteToInt(std::ifstream& _file);
		std::string byteToString(int strLength, std::ifstream& _file);
		float byteToFloat(std::ifstream& _file);

		void loadHeader(LoadData& _loadData);
		void loadAnimations(LoadData& _loadData);
		void loadIndices(LoadData& _loadData);
		void loadVertices(LoadData& _loadData);
		void createVertexBuffers(LoadData& _loadData, MTAModel::ptr const& _model);

		void findMinMax(LoadData& _loadData, D3DXVECTOR3 _vector3);
	};
}