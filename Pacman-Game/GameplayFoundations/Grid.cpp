#include "Grid.h"

#include <iostream>
#include <cassert>

namespace GameplayFoundations
{
	const static bool fakeFile[][3] =
	{
		{true, false, true},
		{false, true, false},
		{false, false, true}
	};

	typedef float color[3];

	const static color testFile[] =
	{
		{0, 0, 0},
		{0, 0, 0},
		{1, 1, 1},
		{0, 0, 0},
		{0, 0, 0},
		{1, 1, 1},
		{0, 0, 0},
		{1, 1, 1},
		{1, 1, 1},
	};

	GridCell& Grid::getCell(size_t _u, size_t _v)
	{
		assert(_u < sizeU);
		assert(_v < sizeV);

		return cells[_u + _v * sizeU];
	}

	Grid::Grid(std::string const& filename)
	{
		std::cout << "Filename: " << filename << std::endl;

		sizeU = 3;
		sizeV = 3;

		cells = new GridCell[sizeU * sizeV];

		for (size_t cu = 0; cu < sizeU; cu++)
		{
			for (size_t cv = 0; cv < sizeV; cv++)
			{
				getCell(cu, cv).setFree(fakeFile[cu][cv]);
			}
		}

		for (size_t cu = 0; cu < sizeU; cu++)
		{
			for (size_t cv = 0; cv < sizeV; cv++)
			{
				std::cout << "Cell[" << cu << "][" << cv << "]: " << std::boolalpha << getCell(cu, cv).isFree() << std::endl;
			}
		}
	}

	Grid::~Grid()
	{
		if (cells)
		{
			delete[] cells;
		}
	}
}