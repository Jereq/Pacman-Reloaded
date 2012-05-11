#pragma once

#include <set>

#include "GameObject.h"

namespace GameplayFoundations
{
	class GridCell
	{
	private:
		bool free;
		std::set<GameObject*> objects;

	public:
		GridCell();

		unsigned char type;

		bool isFree() const;
		void setFree(bool _free);

		template<typename Coll>
		void getObjects(Coll& _objs);
		
		void removeObject(GameObject* _obj);
		void addObject(GameObject* _obj);
	};
	
	template<typename Coll>
	void GridCell::getObjects(Coll& _objs)
	{
		_objs.insert(_objs.end(), objects.begin(), objects.end());
	}
}