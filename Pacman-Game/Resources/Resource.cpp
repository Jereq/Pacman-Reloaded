#include "Resource.h"

namespace Resources
{
	Resource::Resource(std::string const& _filename)
		: useCount(0), filename(_filename)
	{
	}

	std::string Resource::getFilename() const
	{
		return filename;
	}

	unsigned int Resource::getUseCount() const
	{
		return useCount;
	}

	void Resource::decrementUseCount()
	{
		useCount--;
	}

	void Resource::incrementUseCount()
	{
		useCount++;
	}
}