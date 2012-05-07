#pragma once

#include <boost/shared_ptr.hpp>

namespace GameplayFoundations
{
	namespace Events
	{
		class Event
		{
		public:
			typedef boost::shared_ptr<Event> ptr;

			enum EventType
			{
				MOUSE_BUTTON_EVENT,
				MOUSE_MOVE_EVENT,
				KEYBOARD_KEY_EVENT,
			};

		protected:
			Event(EventType _type);

		public:
			const EventType eventType;

			virtual ~Event(){};
		};
	}
}