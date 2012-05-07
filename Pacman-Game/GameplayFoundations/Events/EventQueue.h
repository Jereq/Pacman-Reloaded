#pragma once

#include <queue>

#include "Event.h"

namespace GameplayFoundations
{
	namespace Events
	{
		class EventQueue
		{
		private:
			typedef std::queue<Event::ptr> eventQueue_t;
			eventQueue_t queue;

		public:
			bool isEmpty() const;

			void pushEvent(Event::ptr const& _event);
			Event::ptr popEvent();
		};
	}
}