#pragma once

#include "Event.h"

#include <windows.h>

namespace GameplayFoundations
{
	namespace Events
	{
		class MouseMoveEvent : public Event
		{
		public:
			typedef boost::shared_ptr<MouseMoveEvent> ptr;

			POINT prevPos;
			POINT curPos;

			MouseMoveEvent(POINT _prevPos, POINT _curPos);
		};
	}
}