#pragma once

#include "Event.h"

#include <Windows.h>

namespace GameplayFoundations
{
	namespace Events
	{
		class MouseButtonEvent : public Event
		{
		public:
			typedef boost::shared_ptr<MouseButtonEvent> ptr;

			enum MouseButton
			{
				MOUSE_BUTTON_LEFT,
				MOUSE_BUTTON_RIGHT,
			};

			enum MouseButtonAction
			{
				MOUSE_BUTTON_PRESSED,
				MOUSE_BUTTON_RELEASED,
			};

			const MouseButton button;
			const MouseButtonAction action;
			const POINT pos;

			MouseButtonEvent(MouseButton _button, MouseButtonAction _action, POINT _pos);
		};
	}
}