#pragma once

namespace GameplayFoundations
{
	class CellIndex
	{
	public:
		size_t u;
		size_t v;

		CellIndex();
		CellIndex(size_t _u, size_t _v);
	};
}