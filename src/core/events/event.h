/*
 * event.h
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <memory>

namespace core
{

  class Event
  {
  public:
    Event();
    Event(int);
    virtual ~Event();
    virtual void process_event(void*) = 0;  // event callback function
    int get_priority();		// get the priority for this event

  protected:
    int priority;		// stores the priority for this event
  };

  typedef std::shared_ptr<Event> event_ptr;

  struct EventComparator {
		bool operator() (event_ptr left, event_ptr right) {
			return left->get_priority() > right->get_priority();
		}
	};

} /* namespace core */
#endif /* EVENT_H_ */
