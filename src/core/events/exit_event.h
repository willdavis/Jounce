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

  class ExitEvent : public Dispatchable
  {
  public:
    ExitEvent();
    virtual ~ExitEvent();
    void dispatch(Dispatcher* dispatcher);
    unsigned int priority() { return 0; }
    uint64_t timestamp() { return 0;}
  };

} /* namespace core */
#endif /* EXIT_EVENT_H_ */
