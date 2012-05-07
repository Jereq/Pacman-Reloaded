#include "MouseButtonEvent.h"

namespace GameplayFoundations
{
	namespace Events
	{
		MouseButtonEvent::MouseButtonEvent(MouseButton _button, MouseButtonAction _action, POINT _pos)
			: Event(MOUSE_BUTTON_EVENT), button(_button), action(_action), pos(_pos)
		{
		}
	}
}