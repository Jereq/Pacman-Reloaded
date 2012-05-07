#pragma once

#include "Event.h"

namespace GameplayFoundations
{
	namespace Events
	{
		class KeyboardKeyEvent : public Event
		{
		public:
			typedef boost::shared_ptr<KeyboardKeyEvent> ptr;

			enum KeyAction
			{
				KEY_PRESSED,
				KEY_RELEASED,
			};

			char key;
			KeyAction action;

			KeyboardKeyEvent(char _key, KeyAction _action);
		};
	}
}