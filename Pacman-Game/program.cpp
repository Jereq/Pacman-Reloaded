#include "GameplayFoundations\Grid.h"
#include <cassert>

int main()
{
	using namespace GameplayFoundations;
	GameplayFoundations::Grid grid("testMap.lvl");
	std::vector<void*> objects;
	float testValue = 3.14259f;

	CellIndex testCell(2, 2);

	grid.addObject(testCell, &testValue);
	grid.getObjects(testCell, objects);

	assert(objects.size() == 1);
	assert(objects[0] == &testValue);
	objects.clear();

	grid.removeObject(testCell, &testValue);
	grid.getObjects(testCell, objects);

	assert(objects.size() == 0);
}