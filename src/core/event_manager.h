/*
 * event_manager.h
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include "event.h"

namespace core
{

  class EventManager
  {
  public:
    EventManager();
    virtual ~EventManager();

    int get_queue_size() { return 0; }
    void schedule_event (Event*);
    void process_top_event();
  };

} /* namespace core */
#endif /* EVENT_MANAGER_H_ */
