#include "Grid.h"

#include <iostream>
#include <cassert>

namespace GameplayFoundations
{
	struct Color
	{
		union
		{
			float col[3];
			struct
			{
				float r;
				float g;
				float b;
			};
		};

		bool operator==(Color const& rhs) const
		{
			return r == rhs.r &&
				g == rhs.g &&
				b == rhs.b;
		}
	};

	struct ColorCode
	{
		unsigned char val;
		Color col;
		char charPresentation;
		bool free;
	};

	const static ColorCode empty = {0, {0, 0, 0}, ' ', true};
	const static ColorCode wall = {1, {1, 1, 1}, 'X', false};
	const static ColorCode pacmanStart = {2, {0, 1, 0}, 'S', true};
	const static ColorCode ghostStart = {3, {1, 0, 0}, 'G', true};
	const static ColorCode food = {4, {0, 0, 1}, 'F', true};
	const static ColorCode candy = {5, {0, 1, 1}, 'C', true};

	const static ColorCode colorCodes[] =
	{
		empty,
		wall,
		pacmanStart,
		ghostStart,
		food,
		candy,
	};

	const static Color testFile[] =
	{
		pacmanStart.col,	empty.col,	empty.col,	wall.col,
		wall.col,			food.col,	food.col,	wall.col,
		wall.col,			candy.col,	food.col,	wall.col,
		wall.col,			food.col,	empty.col,	ghostStart.col,
	};

	static bool readColor(Color& _out)
	{
		const static size_t filesize = sizeof(testFile) / sizeof(Color);
		static size_t curr = 0;

		if (curr >= filesize)
		{
			return false;
		}
		else
		{
			_out = testFile[curr++];
			return true;
		}
	}

	GridCell& Grid::getCell(size_t _u, size_t _v)
	{
		assert(_u < size.u);
		assert(_v < size.v);

		return cells[_u + _v * size.u];
	}

	GridCell& Grid::getCell(CellIndex _index)
	{
		return getCell(_index.u, _index.v);
	}

	Grid::Grid(std::string const& filename)
	{
		std::cout << "Filename: " << filename << std::endl;

		size_t numColors = sizeof(testFile) / sizeof(Color);

		size.v = 4;
		size.u = numColors / size.v;

		cells = new GridCell[size.u * size.v];

		bool startFound = false;

		size_t cCount = 0;
		for (size_t cu = 0; cu < size.u; cu++)
		{
			for (size_t cv = 0; cv < size.v; cv++)
			{
				Color cellC;
				bool res = readColor(cellC);
				assert(res);

				for (size_t i = 0; i < sizeof(colorCodes) / sizeof(ColorCode); i++)
				{
					ColorCode const& code = colorCodes[i];
					if (cellC == code.col)
					{
						GridCell& cell = getCell(cu, cv);
						cell.setFree(colorCodes[i].free);
						cell.type = code.val;

						if (code.val == pacmanStart.val)
						{
							startFound = true;
							startPos.u = cu;
							startPos.v = cv;
						}

						break;
					}
				}
			}
		}

		assert(startFound);

		std::cout << "Loaded grid:" << std::endl;
		std::cout << '+';
		for (size_t i = 0; i < size.v; i++)
		{
			std::cout << "-";
		}
		std::cout << '+' << std::endl;

		for (size_t cu = 0; cu < size.u; cu++)
		{
			std::cout << '|';
			for (size_t cv = 0; cv < size.v; cv++)
			{
				GridCell const& cell = getCell(cu, cv);

				std::cout << colorCodes[cell.type].charPresentation;
				assert(colorCodes[cell.type].free == cell.isFree());
			}
			std::cout << '|' << std::endl;
		}

		std::cout << '+';
		for (size_t i = 0; i < size.v; i++)
		{
			std::cout << "-";
		}
		std::cout << '+' << std::endl << std::endl;

		std::cout << "Pacman starts at (" << startPos.u << ", " << startPos.v << ")" << std::endl;
	}

	Grid::~Grid()
	{
		if (cells)
		{
			delete[] cells;
		}
	}

	CellIndex Grid::getSize() const
	{
		return size;
	}
}