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

  // Dispatch top event in the queue
  void EventManager::process_top_event()
  {
    Event* event = event_queue.front();
    event->process_event();
    event_queue.pop();
  }

} /* namespace core */
