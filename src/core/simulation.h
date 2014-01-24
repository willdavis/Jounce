/*
 * simulation.h
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "timer.h"
#include "event_manager.h"

namespace core
{

  class Simulation
  {
  public:
    Simulation();
    virtual ~Simulation();

    void run();
    void exit();

    int get_state();

    int get_event_queue_size();
    int schedule_event(Event*);

    Timer core_timer;

  protected:
    EventManager event_manager; // provides an interface to manage events
    int state;                  // stores the current simulation state ( 0 = off, 1 = done, -1 = errors)
  };

} /* namespace core */
#endif /* SIMULATION_H_ */
