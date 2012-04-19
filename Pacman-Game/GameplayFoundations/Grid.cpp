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
		pacmanStart.col,	empty.col,	empty.col,	wall.col,		empty.col,	empty.col,	empty.col,	food.col,	food.col,		wall.col,
		wall.col,			food.col,	food.col,	wall.col,		empty.col,	empty.col,	empty.col,	food.col,	food.col,		wall.col,
		wall.col,			candy.col,	food.col,	wall.col,		empty.col,	empty.col,	empty.col,	food.col,	food.col,		wall.col,
		wall.col,			food.col,	empty.col,	ghostStart.col,	empty.col,	empty.col,	empty.col,	food.col,	food.col,		wall.col,
		wall.col,			food.col,	food.col,	wall.col,		empty.col,	empty.col,	empty.col,	food.col,	food.col,		wall.col,
		wall.col,			candy.col,	food.col,	wall.col,		empty.col,	empty.col,	empty.col,	food.col,	food.col,		wall.col,
		wall.col,			food.col,	empty.col,	ghostStart.col,	empty.col,	empty.col,	empty.col,	food.col,	food.col,		wall.col,
		wall.col,			food.col,	food.col,	wall.col,		empty.col,	empty.col,	empty.col,	food.col,	food.col,		wall.col,
		wall.col,			candy.col,	food.col,	wall.col,		empty.col,	empty.col,	empty.col,	food.col,	ghostStart.col,	wall.col,
		wall.col,			food.col,	empty.col,	ghostStart.col,	wall.col,	wall.col,	wall.col,	wall.col,	wall.col,		wall.col,
	};
	CellIndex testFileDim(10, 10);

	const static Color testFileSmall[] =
	{
		empty.col,		wall.col,	pacmanStart.col,
		wall.col,		empty.col,	food.col,
		ghostStart.col,	candy.col,	wall.col,
	};
	CellIndex testFileSmallDim(3, 3);

	static bool readColor(Color const* _file, Color& _out)
	{
		size_t filesize = (_file == testFile ? sizeof(testFile) : sizeof(testFileSmall)) / sizeof(Color);
		static size_t curr = 0;

		if (curr >= filesize)
		{
			return false;
		}
		else
		{
			_out = _file[curr++];
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

		Color const* file = testFileSmall;
		size = testFileSmallDim;

		cells = new GridCell[size.u * size.v];

		bool startFound = false;

		size_t cCount = 0;
		for (size_t cu = 0; cu < size.u; cu++)
		{
			for (size_t cv = 0; cv < size.v; cv++)
			{
				Color cellC;
				bool res = readColor(file, cellC);
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
						else if (code.val == ghostStart.val)
						{
							ghostStartPos.push_back(CellIndex(cu, cv));							
						}

						break;
					}
				}
			}
		}

		assert(startFound);
		assert(ghostStartPos.size() > 0);

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

		std::cout << "Ghosts starts at:" << std::endl;
		for (size_t i = 0; i < ghostStartPos.size(); i++)
		{
			CellIndex const& pos = ghostStartPos[i];
			std::cout << "(" << pos.u << ", " << pos.v << ")" << std::endl;
		}

		std::vector<Vertex> vertices;
		vertices.reserve(size.u * size.v * 8);

		for (size_t cu = 0; cu < size.u; cu++)
		{
			for (size_t cv = 0; cv < size.v; cv++)
			{
				if (!getCell(cu, cv).isFree())
				{
					continue;
				}

				const static Vec3 blockSize(1.f);
				const static Vec3 up(0.f, 1.f, 0.f);

				Vec3 basePos = Vec3((float)cu, 0.f, (float)cv) * blockSize;
				Vec3 bPosX = basePos + Vec3(1.f, 0.f, 0.f) * blockSize;
				Vec3 bPosZ = basePos + Vec3(0.f, 0.f, 1.f) * blockSize;
				Vec3 bPosXZ = basePos + Vec3(1.f, 0.f, 1.f) * blockSize;

				// Create Ground
				Vertex v0 = {basePos, {0.f, 0.f}, up};
				Vertex v1 = {bPosX, {0.f, .5f}, up};
				Vertex v2 = {bPosZ, {.5f, 0.f}, up};
				Vertex v3 = {bPosXZ, {.5f, .5f}, up};

				vertices.push_back(v0);
				vertices.push_back(v1);
				vertices.push_back(v2);
				vertices.push_back(v3);
				vertices.push_back(v2);
				vertices.push_back(v1);

				for (size_t i = 0; i < 4; i++)
				{
					const static int offsetU[] = { 0, 0, -1, 1};
					const static int offsetV[] = {-1, 1,  0, 0};

					int posU = cu + offsetU[i];
					int posV = cv + offsetV[i];

					if (posU < 0 ||
						(size_t)posU >= size.u ||
						posV < 0 ||
						(size_t)posV >= size.v)
					{
						continue;
					}

					CellIndex neighbor(posU, posV);

					if (!getCell(neighbor).isFree())
					{
						const static Vec3 wallOffsets[4][4] =
						{
							{
								Vec3(1.f, 1.f, 0.f),
								Vec3(1.f, 0.f, 0.f),
								Vec3(0.f, 1.f, 0.f),
								Vec3(0.f, 0.f, 0.f),
							},
							{
								Vec3(0.f, 1.f, 1.f),
								Vec3(0.f, 0.f, 1.f),
								Vec3(1.f, 1.f, 1.f),
								Vec3(1.f, 0.f, 1.f),
							},
							{
								Vec3(0.f, 1.f, 0.f),
								Vec3(0.f, 0.f, 0.f),
								Vec3(0.f, 1.f, 1.f),
								Vec3(0.f, 0.f, 1.f),
							},
							{
								Vec3(1.f, 1.f, 1.f),
								Vec3(1.f, 0.f, 1.f),
								Vec3(1.f, 1.f, 0.f),
								Vec3(1.f, 0.f, 0.f),
							}
						};

						// Create Wall
						Vertex w0 = {basePos + wallOffsets[i][0], {.5f, 0.f}, Vec3((float)-offsetU[i], 0.f, (float)-offsetV[i])};
						Vertex w1 = {basePos + wallOffsets[i][1], {.5f, .5f}, Vec3((float)-offsetU[i], 0.f, (float)-offsetV[i])};
						Vertex w2 = {basePos + wallOffsets[i][2], {1.f, 0.f}, Vec3((float)-offsetU[i], 0.f, (float)-offsetV[i])};
						Vertex w3 = {basePos + wallOffsets[i][3], {1.f, .5f}, Vec3((float)-offsetU[i], 0.f, (float)-offsetV[i])};

						vertices.push_back(w0);
						vertices.push_back(w1);
						vertices.push_back(w2);
						vertices.push_back(w3);
						vertices.push_back(w2);
						vertices.push_back(w1);
					}
				}
			}
		}

		for (size_t i = 0; i < vertices.size(); i++)
		{
			Vertex vert = vertices[i];
			std::cout << "Vert[" << i << "]:\t(" << vert.position.x << ", " << vert.position.y << ", " << vert.position.z << ")\t(" <<
				vert.normal.x << ", " << vert.normal.y << ", " << vert.normal.z << ")" << std::endl;
		}
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