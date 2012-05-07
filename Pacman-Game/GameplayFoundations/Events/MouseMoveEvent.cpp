#include "MouseMoveEvent.h"

namespace GameplayFoundations
{
	namespace Events
	{
		MouseMoveEvent::MouseMoveEvent(POINT _prevPos, POINT _curPos)
			: Event(MOUSE_MOVE_EVENT), prevPos(_prevPos), curPos(_curPos)
		{
		}
	}
}