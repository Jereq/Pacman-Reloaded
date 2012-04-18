#pragma once

#include <string>

#include "GridCell.h"

namespace GameplayFoundations
{
	class Grid
	{
	private:
		GridCell* cells;
		size_t sizeU;
		size_t sizeV;

		GridCell& getCell(size_t _u, size_t _v);

	public:
		Grid(std::string const& _filename);
		~Grid();

	};
}