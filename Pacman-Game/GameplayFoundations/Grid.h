#pragma once

#include <string>
#include <vector>

#include "GridCell.h"
#include "CellIndex.h"

namespace GameplayFoundations
{
	struct Vec3
	{
		union
		{
			float val[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};

		Vec3()
			: x(0), y(0), z(0)
		{
		}

		Vec3(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
		{
		}

		Vec3(float _val)
			: x(_val), y(_val), z(_val)
		{
		}

		Vec3 operator*(Vec3 const& rhs) const
		{
			return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		Vec3 operator+(Vec3 const& rhs) const
		{
			return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
		}
	};

	struct Vertex
	{
		Vec3 position;
		float texPos[2];
		Vec3 normal;
	};

	class Grid
	{
	private:
		GridCell* cells;
		CellIndex size;
		CellIndex startPos;
		std::vector<CellIndex> ghostStartPos;

		GridCell& getCell(size_t _u, size_t _v);
		GridCell& getCell(CellIndex _index);

	public:
		Grid(std::string const& _filename);
		~Grid();

		CellIndex getSize() const;
	};
}