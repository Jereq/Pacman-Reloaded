#pragma once

#include <string>
#include <boost/shared_ptr.hpp>

namespace Resources
{
	class Resource
	{
	protected:
		unsigned int useCount;
		std::string filename;

	public:
		typedef boost::shared_ptr<Resource> ptr;

		Resource(std::string const& _filename);

		virtual void freeResource() = 0;

		std::string getFilename() const;

		unsigned int getUseCount() const;
		void decrementUseCount();
		void incrementUseCount();
	};
}