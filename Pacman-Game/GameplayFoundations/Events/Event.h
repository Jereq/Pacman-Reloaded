#pragma once

#include <boost/shared_ptr.hpp>

namespace GameplayFoundations
{
	namespace Events
	{
		enum EventType
		{
			MOUSE_BUTTON_EVENT,
			MOUSE_MOVE_EVENT,
			KEYBOARD_KEY_EVENT,
		};

		class Event
		{
		protected:
			Event(EventType _type);

		public:
			typedef boost::shared_ptr<Event> ptr;

			const EventType eventType;

			virtual ~Event(){};
		};
	}
}