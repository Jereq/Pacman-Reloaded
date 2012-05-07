#include "EventQueue.h"

namespace GameplayFoundations
{
	namespace Events
	{
		bool EventQueue::isEmpty() const
		{
			return queue.empty();
		}

		void EventQueue::pushEvent(Event::ptr const& _event)
		{
			queue.push(_event);
		}

		Event::ptr EventQueue::popEvent()
		{
			assert(!queue.empty());

			Event::ptr ev = queue.front();
			queue.pop();

			return ev;
		}
	}
}