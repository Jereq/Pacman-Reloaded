#pragma once

namespace ResourceHandling
{
	class Resource
	{
	protected:
		unsigned int useCount;

	public:
		Resource();

		virtual void freeResource() = 0;
	};
}