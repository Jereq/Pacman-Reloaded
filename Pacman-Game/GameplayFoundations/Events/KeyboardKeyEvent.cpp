#include "KeyboardKeyEvent.h"

namespace GameplayFoundations
{
	namespace Events
	{
		KeyboardKeyEvent::KeyboardKeyEvent(char _key, KeyAction _action)
			: Event(KEYBOARD_KEY_EVENT), key(_key), action(_action)
		{
		}
	}
}