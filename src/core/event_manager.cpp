/*
 * event_manager.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "event_manager.h"

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
  int EventManager::get_queue_size()
  {
    return event_queue.size();
  }

  // Add Event* to the queue
  void EventManager::schedule_event(Event* event)
  {
  	event_queue.push(event);
	}

  // peek at the top event in the queue
	Event* EventManager::get_top_event()
	{
		return event_queue.top();
	}

  // Dispatch top event in the queue
  void EventManager::process_top_event()
  {
    Event* event = event_queue.top();
    event->process_event(parent);
    event_queue.pop();
  }

} /* namespace core */
