#pragma once

namespace GameplayFoundations
{
	class GridCell
	{
	private:
		bool free;

	public:
		GridCell();

		unsigned char type;

		bool isFree() const;
		void setFree(bool _free);
	};
}