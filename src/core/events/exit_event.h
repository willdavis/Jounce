/*
 * exit_event.h
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#ifndef EXIT_EVENT_H_
#define EXIT_EVENT_H_

#include "../interfaces/dispatchable.h"

namespace core
{

  class ExitEvent : public Dispatchable
  {
  public:
    ExitEvent();
    virtual ~ExitEvent();
    void dispatch(Dispatcher* dispatcher);
    unsigned int priority();
    uint64_t timestamp();
  };

} /* namespace core */
#endif /* EXIT_EVENT_H_ */
