#pragma once

namespace GameplayFoundations
{
	class GridCell
	{
	private:
		bool free;

	public:
		GridCell();

		bool isFree() const;
		void setFree(bool _free);
	};
}