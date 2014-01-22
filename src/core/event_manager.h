/*
 * event_manager.h
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <queue>
#include "event.h"

namespace core
{

  class EventManager
  {
  public:
    EventManager();
    virtual ~EventManager();

    int get_queue_size();
    void schedule_event (Event*);
    void process_top_event();

  protected:
    std::queue<Event*> event_queue;
  };

} /* namespace core */
#endif /* EVENT_MANAGER_H_ */
