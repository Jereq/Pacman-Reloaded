#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

#include <boost/shared_ptr.hpp>

#include <D3DX10math.h>

#include "GridCell.h"
#include "CellIndex.h"

#include "../Resources/vertexTypes.h"
#include "../Resources/Texture.h"
#include "../Resources/MapTexture.h"

namespace GameplayFoundations
{
	struct Paths
	{
		union
		{
			bool vals[4];
			struct
			{
				bool pU;
				bool pV;
				bool nU;
				bool nV;
			};
		};
	};

	class Grid
	{
	private:
		typedef std::map<Resources::vertex, UINT16> vertexMap_t;
		typedef std::vector<Resources::vertex> vertexVector_t;
		typedef std::vector<UINT16> indexVector_t;

		GridCell* cells;
		CellIndex size;
		CellIndex startPos;
		std::vector<CellIndex> ghostStartPos;

		GridCell& getCell(size_t _u, size_t _v);
		GridCell const& getCell(size_t _u, size_t _v) const;
		GridCell& getCell(CellIndex _index);
		GridCell const& getCell(CellIndex _index) const;

		void addVertex(vertexMap_t& _vertexMap,
			vertexVector_t& _vertices,
			indexVector_t& _indices,
			Resources::vertex const& _vert);

		class NavigationGrid
		{
		private:
			struct NavigationNode
			{
				enum State
				{
					OPEN,
					CLOSED,
					UNUSED,
				};

				Paths paths;
				State state;
				NavigationNode* prevNode;

				float g_score;
				float h_score;
				float f_score;
				
				NavigationNode(Paths const& _paths);
			};

			class NodeComparer
			{
			public:
				bool operator()(NavigationNode* _lhs, NavigationNode* _rhs) const;
			};

			typedef std::set<NavigationNode*, NodeComparer> NodeQueue_t;
			NodeQueue_t openNodes;
		};

	public:
		typedef boost::shared_ptr<Grid> ptr;

		Grid(Resources::MapTexture::ptr const& _map);
		~Grid();

		CellIndex getSize() const;
		Paths getOpenPaths(CellIndex const& _cell) const;

		CellIndex getStartPos() const;

		template<typename Coll>
		void getObjects(CellIndex const& _cell, Coll& _objs);

		void removeObject(CellIndex const& _cell, void* _obj);
		void addObject(CellIndex const& _cell, void* _obj);

		ID3DX10Mesh* createMesh(ID3D10Device* _device);

		bool findPath(CellIndex const& _from, CellIndex const& _to, std::vector<CellIndex>& _out) const;
	};

	template<typename Coll>
	void Grid::getObjects(CellIndex const& _index, Coll& _objs)
	{
		getCell(_index).getObjects(_objs);
	}
}