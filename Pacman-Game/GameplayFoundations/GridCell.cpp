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

	void GridCell::removeObject(void* _obj)
	{
		objects.erase(_obj);
	}

	void GridCell::addObject(void* _obj)
	{
		objects.insert(_obj);
	}
}