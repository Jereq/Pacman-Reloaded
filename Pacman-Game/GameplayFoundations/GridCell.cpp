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

	void GridCell::removeObject(GameObject* _obj)
	{
		objects.erase(_obj);
	}

	void GridCell::addObject(GameObject* _obj)
	{
		objects.insert(_obj);
	}
}