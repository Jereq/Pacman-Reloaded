#include "Grid.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <list>

namespace GameplayFoundations
{
	struct ColorCode
	{
		unsigned char val;
		D3DXCOLOR col;
		char charPresentation;
		bool free;
	};

	const static ColorCode empty = {0, D3DXCOLOR(0.f, 0.f, 0.f, 1.f), ' ', true};
	const static ColorCode wall = {1, D3DXCOLOR(1.f, 1.f, 1.f, 1.f), 'X', false};
	const static ColorCode pacmanStart = {2, D3DXCOLOR(1.f, 1.f, 0.f, 1.f), 'S', true};
	const static ColorCode ghostStart = {3, D3DXCOLOR(1.f, 0.f, 0.f, 1.f), 'G', true};
	const static ColorCode food = {4, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 'F', true};
	const static ColorCode candy = {5, D3DXCOLOR(0.f, 1.f, 0.f, 1.f), 'C', true};

	const static ColorCode colorCodes[] =
	{
		empty,
		wall,
		pacmanStart,
		ghostStart,
		food,
		candy,
	};

	const std::pair<int, int> Paths::INDEX_OFFSETS[4] =
	{
		std::pair<int, int>(1, 0),
		std::pair<int, int>(0, 1),
		std::pair<int, int>(-1, 0),
		std::pair<int, int>(0, -1)
	};

	bool Grid::NavigationGrid::NodeComparer::operator()(NavigationNode* _lhs, NavigationNode* _rhs) const
	{
		if (_lhs->f_score < _rhs->f_score) return true;
		if (_lhs->f_score > _rhs->f_score) return false;
		
		return _lhs < _rhs;
	}

	Grid::NavigationGrid::NavigationNode::NavigationNode()
		: paths(), closed(false), prevNode(NULL), g_score(0), h_score(0), f_score(0)
	{
	}

	Grid::NavigationGrid::NavigationNode& Grid::NavigationGrid::getNode(size_t _u, size_t _v)
	{
		assert(_u < size.u);
		assert(_v < size.v);

		return nodes[_u + _v * size.u];
	}

	Grid::NavigationGrid::NavigationNode& Grid::NavigationGrid::getNode(CellIndex const& _nodeIndex)
	{
		return getNode(_nodeIndex.u, _nodeIndex.v);
	}

	float Grid::NavigationGrid::estimate(CellIndex const& _first, CellIndex const& _second) const
	{
		float dU = static_cast<float>((int)_first.u - (int)_second.u);
		float dV = static_cast<float>((int)_first.v - (int)_second.v);

		return sqrt(dU * dU + dV * dV);
	}

	void Grid::NavigationGrid::reconstructPath(NavigationNode* _lastNode, std::vector<CellIndex>& _out) const
	{
		std::list<CellIndex> temp;

		NavigationNode* currentNode = _lastNode;

		while (currentNode)
		{
			temp.push_front(currentNode->index);
			currentNode = currentNode->prevNode;
		}

		_out.insert(_out.end(), temp.begin(), temp.end());
	}

	Grid::NavigationGrid::NavigationGrid()
		: nodes(NULL)
	{
	}

	Grid::NavigationGrid::NavigationGrid(NavigationGrid const& _orig)
	{
		size = _orig.size;
		
		size_t numNodes = size.u * size.v;
		nodes = new NavigationNode[numNodes];

		for (size_t i = 0; i < numNodes; i++)
		{
			nodes[i] = _orig.nodes[i];
		}
	}

	Grid::NavigationGrid::~NavigationGrid()
	{
		if (nodes)
		{
			delete[] nodes;
			nodes = NULL;
		}
	}

	void Grid::NavigationGrid::create(CellIndex const& _size)
	{
		size = _size;
		nodes = new NavigationNode[_size.u * _size.v];

		for (size_t u = 0; u < _size.u; u++)
		{
			for (size_t v = 0; v < _size.v; v++)
			{
				getNode(u, v).index = CellIndex(u, v);
			}
		}
	}

	void Grid::NavigationGrid::setPaths(CellIndex const& _index, Paths const& _paths)
	{
		getNode(_index).paths = _paths;
	}

	bool Grid::NavigationGrid::findPath(CellIndex const& _from, CellIndex const& _to, std::vector<CellIndex>& _out)
	{
		NodeQueue_t openNodes;

		NavigationNode* currentNode = &getNode(_from);
		currentNode->h_score = estimate(_from, _to);
		currentNode->f_score = currentNode->h_score;

		openNodes.insert(currentNode);

		while (!openNodes.empty())
		{
			currentNode = *openNodes.begin();
			openNodes.erase(currentNode);

			if (currentNode->index == _to)
			{
				reconstructPath(currentNode, _out);
				return true;
			}

			currentNode->closed = true;

			for (size_t i = 0; i < 4; i++)
			{
				if (currentNode->paths.vals[i])
				{
					CellIndex neighborIndex = currentNode->index;
					neighborIndex.u += Paths::INDEX_OFFSETS[i].first;
					neighborIndex.v += Paths::INDEX_OFFSETS[i].second;

					NavigationNode* neighbor = &getNode(neighborIndex);
					
					if (neighbor->closed)
					{
						continue;
					}

					float tentative_g_score = currentNode->g_score + 1.f;

					bool tentative_is_better;
					if (openNodes.count(neighbor) == 0)
					{
						neighbor->h_score = estimate(neighbor->index, _to);
						tentative_is_better = true;
					}
					else
					{
						openNodes.erase(neighbor);
						tentative_is_better = tentative_g_score < neighbor->g_score;
					}

					if (tentative_is_better)
					{
						neighbor->prevNode = currentNode;
						neighbor->g_score = tentative_g_score;
						neighbor->f_score = neighbor->g_score + neighbor->h_score;
					}

					openNodes.insert(neighbor);
				}
			}
		}

		return false;
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

	void Grid::addVertex(Grid::vertexMap_t& _vertexMap,
		Grid::vertexVector_t& _vertices,
		Grid::indexVector_t& _indices,
		Resources::vertex const& _vert)
	{
		if (_vertexMap.count(_vert) == 0)
		{
			_vertexMap[_vert] = _vertices.size();
			_vertices.push_back(_vert);
		}

		_indices.push_back(_vertexMap[_vert]);
	}

	D3DXVECTOR3 mul(D3DXVECTOR3 const& lhs, D3DXVECTOR3 const& rhs)
	{
		return D3DXVECTOR3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	Grid::Grid(Resources::MapTexture::ptr const& _map)
	{
		std::vector<D3DXCOLOR> cols;
		_map->extractColors(cols);

		size = CellIndex(_map->getHeight(), _map->getWidth());
		std::vector<D3DXCOLOR>::iterator it = cols.begin();

		cells = new GridCell[size.u * size.v];

		bool startFound = false;

		size_t cCount = 0;
		for (size_t cu = 0; cu < size.u; cu++)
		{
			for (size_t cv = 0; cv < size.v; cv++)
			{
				D3DXCOLOR cellC = *(it++);

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

		navigationGrid.create(size);

		for (size_t u = 0; u < size.u; u++)
		{
			for (size_t v = 0; v < size.v; v++)
			{
				CellIndex index(u, v);
				navigationGrid.setPaths(index, getOpenPaths(index));
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

	CellIndex Grid::getStartPos() const
	{
		return startPos;
	}

	std::vector<CellIndex> Grid::getGhostStartPos() const
	{
		return ghostStartPos;
	}

	void Grid::removeObject(CellIndex const& _cell, void* _obj)
	{
		getCell(_cell).removeObject(_obj);
	}

	void Grid::addObject(CellIndex const& _cell, void* _obj)
	{
		getCell(_cell).addObject(_obj);
	}

	ID3DX10Mesh* Grid::createMesh(ID3D10Device* _device)
	{
		vertexMap_t vertexMap;
		vertexVector_t vertices;
		vertices.reserve(size.u * size.v * 8);
		indexVector_t indices;
		indices.reserve(size.u * size.v * 4);

		const static float TEXTURE_MARGIN = 1.f / 32.f;

		const static D3DXVECTOR2 GROUND_TEXCOORD[4] =
		{
			D3DXVECTOR2(0.f, 0.f),
			D3DXVECTOR2(0.f, .5f - TEXTURE_MARGIN),
			D3DXVECTOR2(.5f - TEXTURE_MARGIN, 0.f),
			D3DXVECTOR2(.5f - TEXTURE_MARGIN, .5f - TEXTURE_MARGIN),
		};

		const static D3DXVECTOR2 WALL_TEXCOORD[4] =
		{
			D3DXVECTOR2(.5f + TEXTURE_MARGIN, 0.f),
			D3DXVECTOR2(.5f + TEXTURE_MARGIN, .5f - TEXTURE_MARGIN),
			D3DXVECTOR2(1.f, 0.f),
			D3DXVECTOR2(1.f, .5f - TEXTURE_MARGIN),
		};
		
		for (size_t cu = 0; cu < size.u; cu++)
		{
			for (size_t cv = 0; cv < size.v; cv++)
			{
				if (!getCell(cu, cv).isFree())
				{
					continue;
				}

				const static D3DXVECTOR3 blockSize(1.f, 1.f, 1.f);
				const static D3DXVECTOR3 up(0.f, 1.f, 0.f);

				D3DXVECTOR3 basePos = mul(D3DXVECTOR3((float)cu, 0.f, (float)cv), blockSize);
				D3DXVECTOR3 bPosX = basePos + mul(D3DXVECTOR3(1.f, 0.f, 0.f), blockSize);
				D3DXVECTOR3 bPosZ = basePos + mul(D3DXVECTOR3(0.f, 0.f, 1.f), blockSize);
				D3DXVECTOR3 bPosXZ = basePos + mul(D3DXVECTOR3(1.f, 0.f, 1.f), blockSize);

				// Create Ground
				Resources::vertex v0(basePos, GROUND_TEXCOORD[0], up);
				Resources::vertex v1(bPosX, GROUND_TEXCOORD[1], up);
				Resources::vertex v2(bPosZ, GROUND_TEXCOORD[2], up);
				Resources::vertex v3(bPosXZ, GROUND_TEXCOORD[3], up);

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
						const static D3DXVECTOR3 wallOffsets[4][4] =
						{
							{
								D3DXVECTOR3(1.f, 1.f, 0.f),
								D3DXVECTOR3(1.f, 0.f, 0.f),
								D3DXVECTOR3(0.f, 1.f, 0.f),
								D3DXVECTOR3(0.f, 0.f, 0.f),
							},
							{
								D3DXVECTOR3(0.f, 1.f, 1.f),
								D3DXVECTOR3(0.f, 0.f, 1.f),
								D3DXVECTOR3(1.f, 1.f, 1.f),
								D3DXVECTOR3(1.f, 0.f, 1.f),
							},
							{
								D3DXVECTOR3(0.f, 1.f, 0.f),
								D3DXVECTOR3(0.f, 0.f, 0.f),
								D3DXVECTOR3(0.f, 1.f, 1.f),
								D3DXVECTOR3(0.f, 0.f, 1.f),
							},
							{
								D3DXVECTOR3(1.f, 1.f, 1.f),
								D3DXVECTOR3(1.f, 0.f, 1.f),
								D3DXVECTOR3(1.f, 1.f, 0.f),
								D3DXVECTOR3(1.f, 0.f, 0.f),
							}
						};

						// Create Wall
						D3DXVECTOR3 normal((float)-offsetU[i], 0.f, (float)-offsetV[i]);

						Resources::vertex w0(basePos + wallOffsets[i][0], WALL_TEXCOORD[0], normal);
						Resources::vertex w1(basePos + wallOffsets[i][1], WALL_TEXCOORD[1], normal);
						Resources::vertex w2(basePos + wallOffsets[i][2], WALL_TEXCOORD[2], normal);
						Resources::vertex w3(basePos + wallOffsets[i][3], WALL_TEXCOORD[3], normal);

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

		ID3DX10Mesh* mesh;
		D3DX10CreateMesh(
			_device,
			Resources::vertexInputLayout,
			Resources::simpleVertexInputLayoutNumElements,
			"POSITION",
			vertices.size(),
			indices.size() / 3,
			0,
			&mesh);

		mesh->SetVertexData(NULL, vertices.data());
		mesh->SetIndexData(indices.data(), indices.size());
		mesh->CommitToDevice();

		return mesh;
	}

	bool Grid::findPath(CellIndex const& _from, CellIndex const& _to, std::vector<CellIndex>& _out)
	{
		NavigationGrid tmpNavGrid(navigationGrid);

		return tmpNavGrid.findPath(_from, _to, _out);
	}
}