#include "GridCell.h"

namespace GameplayFoundations
{
	GridCell::GridCell()
		: free(true)
	{
	}

	bool GridCell::isFree() const
	{
		return free;
	}

	void GridCell::setFree(bool _free)
	{
		free = _free;
	}
}