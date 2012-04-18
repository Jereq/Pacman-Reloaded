#include "CellIndex.h"

namespace GameplayFoundations
{
	CellIndex::CellIndex()
		: u(0), v(0)
	{
	}

	CellIndex::CellIndex(size_t _u, size_t _v)
		: u(_u), v(_v)
	{
	}
}