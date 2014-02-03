/*
 * event_manager.h
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <queue>
//#include "./events/event.h"
#include "./interfaces/dispatcher.h"

namespace core
{

	typedef std::shared_ptr<Dispatchable> event_ptr;

  class EventManager : public Dispatcher
  {
  public:
    EventManager();
    virtual ~EventManager();

    void* get_parent();
    void set_parent(void*);
    event_ptr get_top_event();

    /* Dispatcher interface */
    unsigned int queue_size();
    void schedule(event_ptr);
    void dispatch_top_event();
    void close();
    /* end Dispatcher interface */

  protected:
    void* parent;
    std::priority_queue<event_ptr, std::vector<event_ptr>, DispatchableComparator > event_queue;
  };

} /* namespace core */
#endif /* EVENT_MANAGER_H_ */
