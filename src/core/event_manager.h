/*
 * event_manager.h
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <queue>
#include "./events/event.h"

namespace core
{

  class EventManager
  {
  public:
    EventManager();
    virtual ~EventManager();

    void* get_parent();
    void set_parent(void*);

    int get_queue_size();
    event_ptr get_top_event();

    void schedule_event (event_ptr);
    void process_top_event();

  protected:
    void* parent;
    std::priority_queue<event_ptr, std::vector<event_ptr>, EventComparator > event_queue;
  };

} /* namespace core */
#endif /* EVENT_MANAGER_H_ */
