#include "Grid.h"

#include <iostream>
#include <cassert>
#include <map>

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

	GridCell const& Grid::getCell(size_t _u, size_t _v) const
	{
		assert(_u < size.u);
		assert(_v < size.v);

		return cells[_u + _v * size.u];
	}

	GridCell& Grid::getCell(CellIndex _index)
	{
		return getCell(_index.u, _index.v);
	}

	GridCell const& Grid::getCell(CellIndex _index) const
	{
		return getCell(_index.u, _index.v);
	}

	void addVertex(std::map<Vertex, unsigned int>& _vertexMap, std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices, Vertex const& _vert)
	{
		if (_vertexMap.count(_vert) == 0)
		{
			_vertexMap[_vert] = _vertices.size();
			_vertices.push_back(_vert);
		}

		_indices.push_back(_vertexMap[_vert]);
	}

	Grid::Grid(std::string const& _filename)
	{
		std::cout << "Filename: " << _filename << std::endl;

		Color const* file = testFile;
		size = testFileDim;

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
		
		std::map<Vertex, unsigned int> vertexMap;
		std::vector<Vertex> vertices;
		vertices.reserve(size.u * size.v * 8);
		std::vector<unsigned int> indices;
		indices.reserve(size.u * size.v * 4);

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

				addVertex(vertexMap, vertices, indices, v0);
				addVertex(vertexMap, vertices, indices, v1);
				addVertex(vertexMap, vertices, indices, v2);
				addVertex(vertexMap, vertices, indices, v3);
				addVertex(vertexMap, vertices, indices, v2);
				addVertex(vertexMap, vertices, indices, v1);

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

						addVertex(vertexMap, vertices, indices, w0);
						addVertex(vertexMap, vertices, indices, w1);
						addVertex(vertexMap, vertices, indices, w2);
						addVertex(vertexMap, vertices, indices, w3);
						addVertex(vertexMap, vertices, indices, w2);
						addVertex(vertexMap, vertices, indices, w1);
					}
				}
			}
		}

		//for (size_t i = 0; i < vertices.size(); i++)
		//{
		//	Vertex vert = vertices[i];
		//	std::cout << "Vert[" << i << "]:\t(" << vert.position.x << ", " << vert.position.y << ", " << vert.position.z << ")\t(" <<
		//		vert.normal.x << ", " << vert.normal.y << ", " << vert.normal.z << ")" << std::endl;
		//}

		//for (size_t i = 0; i < indices.size(); i += 3)
		//{
		//	std::cout << "Face[" << i / 3 << "]:\t" << indices[i] << ", " << indices[i+1] << ", " << indices[i+2] << std::endl;
		//}
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

	Paths Grid::getOpenPaths(CellIndex const& _cell) const
	{
		Paths ret = {0};

		if (_cell.u > 0 && getCell(_cell.u - 1, _cell.v).isFree())
		{
			ret.nU = true;
		}
		if (_cell.u < size.u - 1 && getCell(_cell.u + 1, _cell.v).isFree())
		{
			ret.pU = true;
		}
		if (_cell.v > 0 && getCell(_cell.u, _cell.v - 1).isFree())
		{
			ret.nV = true;
		}
		if (_cell.v < size.v - 1 && getCell(_cell.u, _cell.v + 1).isFree())
		{
			ret.pV = true;
		}

		return ret;
	}

	void Grid::removeObject(CellIndex const& _cell, void* _obj)
	{
		getCell(_cell).removeObject(_obj);
	}

	void Grid::addObject(CellIndex const& _cell, void* _obj)
	{
		getCell(_cell).addObject(_obj);
	}
}