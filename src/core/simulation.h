/*
 * simulation.h
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "timer.h"
#include "time_manager.h"
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

    uint64_t get_elapsed_sim_time();
    uint64_t get_elapsed_real_time();
    uint64_t get_sim_time_remainder();

    uint64_t get_sim_duration();
    uint64_t get_real_duration();
    uint64_t get_frequency();

    void set_real_and_sim_duration(uint64_t, uint64_t);
    void set_real_duration_and_frequency(uint64_t, uint64_t);
    void set_sim_duration_and_frequency(uint64_t, uint64_t);

    int get_event_queue_size();
    int schedule_event(std::shared_ptr<Event>);

  protected:
    Timer timer;								// core simulation timer
    TimeManager time_manager;		// provides an interface to configure simulation time
    EventManager event_manager; // provides an interface to manage events
    int state;                  // stores the current simulation state ( 0 = off, 1 = done, -1 = errors)
  };

} /* namespace core */
#endif /* SIMULATION_H_ */
