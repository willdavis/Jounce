/*
 * exit_event.h
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#ifndef EXIT_EVENT_H_
#define EXIT_EVENT_H_

#include "event.h"
#include "../simulation.h"

namespace core
{

  class ExitEvent : public Event
  {
  public:
    ExitEvent();
    virtual ~ExitEvent();
    void process_event(void*);
  };

} /* namespace core */
#endif /* EXIT_EVENT_H_ */