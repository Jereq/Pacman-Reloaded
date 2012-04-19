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

		bool operator<(Vec3 const& rhs) const
		{
			if (x < rhs.x) return true;
			if (x > rhs.x) return false;
			if (y < rhs.y) return true;
			if (y > rhs.y) return false;
			if (z < rhs.z) return true;
			return false;
		}
	};

	struct Vertex
	{
		Vec3 position;
		float texPos[2];
		Vec3 normal;

		bool operator<(Vertex const& rhs) const
		{
			if (position < rhs.position) return true;
			if (rhs.position < position) return false;
			if (texPos[0] < rhs.texPos[0]) return true;
			if (texPos[0] > rhs.texPos[0]) return false;
			if (texPos[1] < rhs.texPos[1]) return true;
			if (texPos[1] > rhs.texPos[1]) return false;
			if (normal < rhs.normal) return true;
			return false;
		}
	};

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
		GridCell* cells;
		CellIndex size;
		CellIndex startPos;
		std::vector<CellIndex> ghostStartPos;

		GridCell& getCell(size_t _u, size_t _v);
		GridCell const& getCell(size_t _u, size_t _v) const;
		GridCell& getCell(CellIndex _index);
		GridCell const& getCell(CellIndex _index) const;

	public:
		Grid(std::string const& _filename);
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