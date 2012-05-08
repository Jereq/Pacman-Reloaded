#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include <D3DX10.h>

#include <boost\shared_ptr.hpp>
#include <boost\foreach.hpp>

#include "vertexTypes.h"
#include "MTModel.h"

namespace Resources
{
	class MTLoader
	{
	public:
		MTLoader();
		~MTLoader();
		void startup(ID3D10Device* pdevice);
		void shutdown();

		void loadMT(MTModel::ptr const& _model);

	private:

		struct LoadData
		{
			std::ifstream file;


			int indexCount;
			int vertexCount;

			std::string textureName;

			std::vector<UINT16> IB;
			std::vector<vertex> VB;

			D3DXVECTOR3 minPos, maxPos;

			LoadData()
				: indexCount(0), vertexCount(0),
				minPos(
					std::numeric_limits<float>::infinity(),
					std::numeric_limits<float>::infinity(),
					std::numeric_limits<float>::infinity()),
				maxPos(
					-std::numeric_limits<float>::infinity(),
					-std::numeric_limits<float>::infinity(),
					-std::numeric_limits<float>::infinity())
			{
			}
		};

		ID3D10Device* device;

		int  byteToInt(std::ifstream& _file);
		std::string byteToString(int strLength, std::ifstream& _file);
		float byteToFloat(std::ifstream& _file);

		void loadHeader(LoadData& _loadData);
		void loadIndices(LoadData& _loadData);
		void loadVertices(LoadData& _loadData);
		void createMesh(LoadData& _loadData, MTModel::ptr const& _model);

		void findMinMax(LoadData& _loadData, D3DXVECTOR3 _vector3);
	};
}