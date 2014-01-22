/*
 * event.h
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#ifndef EVENT_H_
#define EVENT_H_

namespace core
{

  class Event
  {
  public:
    Event();
    virtual ~Event();
    virtual void process_event(void*) = 0;  // event callback function
  };

} /* namespace core */
#endif /* EVENT_H_ */
