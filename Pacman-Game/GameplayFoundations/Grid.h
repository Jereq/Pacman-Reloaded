#pragma once

#include <string>

#include "GridCell.h"
#include "CellIndex.h"

namespace GameplayFoundations
{
	class Grid
	{
	private:
		GridCell* cells;
		CellIndex size;
		CellIndex startPos;

		GridCell& getCell(size_t _u, size_t _v);
		GridCell& getCell(CellIndex _index);

	public:
		Grid(std::string const& _filename);
		~Grid();

		CellIndex getSize() const;
	};
}