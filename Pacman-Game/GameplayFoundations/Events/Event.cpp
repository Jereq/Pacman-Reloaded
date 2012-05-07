#include "Event.h"

namespace GameplayFoundations
{
	namespace Events
	{
		Event::Event(EventType _type)
			: eventType(_type)
		{
		}
	}
}