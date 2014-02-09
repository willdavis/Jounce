/*
 * event_manager.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "event_manager.h"
#include "simulation.h"

namespace core
{

  EventManager::EventManager()
  {
    // TODO Auto-generated constructor stub

  }

  EventManager::~EventManager()
  {
    // TODO Auto-generated destructor stub
  }

  // set parent to the supplied void* pointer
  void EventManager::set_parent(void* pointer)
  {
    parent = pointer;
  }

  // return a reference to the parent object
  void* EventManager::get_parent()
  {
    return parent;
  }

  // Return the size of the event queue
  unsigned int EventManager::queue_size()
  {
    return event_queue.size();
  }

  // Add Event* to the queue
  void EventManager::schedule(event_ptr event)
  {
  	event_queue.push(event);
	}

  // peek at the top event in the queue
  event_ptr EventManager::get_top_event()
	{
		return event_queue.top();
	}

  // Dispatch top event in the queue
  void EventManager::dispatch_top_event()
  {
    event_queue.top()->dispatch(this);
    event_queue.pop();
  }

  void EventManager::process_event_queue()
  {
		while (event_queue.size() > 0)
		{
			dispatch_top_event();
		}
  }

  void EventManager::close()
  {
  	static_cast<core::Simulation *>(parent)->exit();
  }

} /* namespace core */
