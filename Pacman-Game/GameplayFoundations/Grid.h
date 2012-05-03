#pragma once

#include <string>
#include <vector>
#include <map>

#include <D3DX10math.h>

#include "GridCell.h"
#include "CellIndex.h"

#include "../vertexTypes.h"
#include "../ResourceHandling/Texture.h"

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

	public:
		Grid(Resources::Texture::ptr const& _map);
		~Grid();

		CellIndex getSize() const;
		Paths getOpenPaths(CellIndex const& _cell) const;

		template<typename Coll>
		void getObjects(CellIndex const& _cell, Coll& _objs);

		void removeObject(CellIndex const& _cell, void* _obj);
		void addObject(CellIndex const& _cell, void* _obj);
	};

	template<typename Coll>
	void Grid::getObjects(CellIndex const& _index, Coll& _objs)
	{
		getCell(_index).getObjects(_objs);
	}
}