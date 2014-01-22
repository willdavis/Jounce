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
    uint64_t get_scaled_time(uint64_t);
    int get_event_queue_size();
    int schedule_event(Event*);

    double time_scale;          // factor to scale time by
    uint64_t duration;          // duration of the simulation (in nanoseconds) (optional)
    uint64_t elapsed_time;      // current elapsed time of the simulation (in nanoseconds)
    int state;                  // stores the current simulation state ( 0 = off, 1 = done, -1 = errors)
    Timer core_timer;

  protected:
    EventManager event_manager; //Provides an interface to manage Events
  };

} /* namespace core */
#endif /* SIMULATION_H_ */
