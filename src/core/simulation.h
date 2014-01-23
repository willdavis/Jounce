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

    double get_time_scale();
    void set_time_scale(double);

    uint64_t get_real_duration();
    void set_real_duration(uint64_t);

    uint64_t get_simulated_duration();
    void set_simulated_duration(uint64_t);

    uint64_t get_real_elapsed_time();
    uint64_t get_simulated_elapsed_time();

    int get_event_queue_size();
    int schedule_event(Event*);

    Timer core_timer;

  protected:
    EventManager event_manager; // provides an interface to manage events
    int state;                  // stores the current simulation state ( 0 = off, 1 = done, -1 = errors)
    double time_scale;          // factor to scale time by

    uint64_t real_duration;             // real time duration of the simulation (nanoseconds) (optional)
    uint64_t simulated_duration;        // simulated duration of the simulation (optional)

    uint64_t real_elapsed_time;         // current elapsed real time (nanoseconds)
    uint64_t simulated_elapsed_time;    // current elapsed simulated time
  };

} /* namespace core */
#endif /* SIMULATION_H_ */
