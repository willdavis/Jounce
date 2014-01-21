/*
 * simulation.cpp
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#include "simulation.h"

namespace core
{

  Simulation::Simulation()
  {
    state = 0;          //set default state
    time_scale = 1;     //set time scale to normal time (1x)
    elapsed_time = 0;   //set elapsed time to zero
    duration = 0;       //default to infinite duration (wait for state != 0)
  }

  Simulation::~Simulation()
  {
    // TODO Auto-generated destructor stub
  }

  void Simulation::run()
  {
    while(state == 0) {
      uint64_t dt = core_timer.get_elapsed_time();      // get delta time between last frame in nanoseconds
      elapsed_time += dt;

      if(elapsed_time >= duration and duration > 0)
        state = 1;

      //this is temporary to avoid infinite loops
      if(duration == 0)
        state = 1;
    }
  }

  uint64_t Simulation::get_scaled_time(uint64_t nanoseconds)
  {
    return (uint64_t)(nanoseconds * time_scale);
  }

} /* namespace core */