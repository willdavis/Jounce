/*
 * simulation.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#include "simulation.h"
#include "./events/exit_event.h"

namespace core
{

  Simulation::Simulation()
  {
    event_manager.set_parent((void*)this);
    state = 0;          //set default state
    time_scale = 1;     //set time scale to normal time (1x)

    real_elapsed_time = 0;      // set elapsed real time to zero
    simulated_elapsed_time = 0; // set elapsed simulation time to zero

    real_duration = 0;          //default to infinite duration (wait for exit event)
    simulated_duration = 0;     //default to infinite duration (wait for exit event)
  }

  Simulation::~Simulation()
  {
    // TODO Auto-generated destructor stub
  }

  void Simulation::exit()
  {
    state = 1;
  }

  void Simulation::run()
  {
    while(state == 0) {
      // first check if we're over the duration.
      // if so, schedule an ExitEvent for immediate termination of the simulation!
      if(real_elapsed_time >= real_duration and real_duration > 0) {
        event_manager.schedule_event(new ExitEvent);
      }

      // whew! we're not done yet!
      // update time between last cycle and this one.
      else {
        uint64_t dt = core_timer.get_elapsed_time();      // get delta time between last frame (nanoseconds)
        real_elapsed_time += dt;
      }

      // process the event queue for this cycle
      int queue_size = event_manager.get_queue_size();
      while(queue_size > 0)
      {
        event_manager.process_top_event();
        queue_size = event_manager.get_queue_size();
      }

      // is the event queue empty?
      // if so, set the simulation to the idle state
    }
  }

  // schedule event with EventManager and return the new queue size
  int Simulation::schedule_event(Event* event)
  {
    event_manager.schedule_event(event);
    return event_manager.get_queue_size();
  }

  // returns the simulated duration (arbitrary units)
  uint64_t Simulation::get_simulated_duration() { return simulated_duration; }

  // get the duration of the simulation in real time (nanoseconds)
  uint64_t Simulation::get_real_duration() { return real_duration; }

  // returns the total elapsed simulation time
  uint64_t Simulation::get_simulated_elapsed_time() { return simulated_duration; }

  // returns the total elapsed real time (nanoseconds)
  uint64_t Simulation::get_real_elapsed_time() { return real_elapsed_time; }

  // returns the value to scale time by
  double Simulation::get_time_scale() { return time_scale; }

  // set the value which will be used to scale simulation time
  void Simulation::set_time_scale(double value) { time_scale = value; }

  // set the simulated duration (arbitrary units)
  void Simulation::set_simulated_duration(uint64_t new_time) { simulated_duration = new_time; }

  // set the real time duration for the simulation (nanoseconds)
  void Simulation::set_real_duration(uint64_t new_time) { real_duration = new_time; }

  // returns the current simulation state (0=ready, 1=done, -1=errors)
  int Simulation::get_state() { return state; }

  // returns the current size of the event queue
  int Simulation::get_event_queue_size() { return event_manager.get_queue_size(); }

} /* namespace core */
