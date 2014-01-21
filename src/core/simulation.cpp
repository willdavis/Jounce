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
    state = 0;          //set state to off
    elapsed_time = 0;
    duration = -1;      //default to infinite duration (wait for state != 0)
  }

  Simulation::~Simulation()
  {
    // TODO Auto-generated destructor stub
  }

  void Simulation::run()
  {
    while(state == 0) {
      double dt = core_timer.get_elapsed_time();      // get delta time between last frame in seconds
      elapsed_time += dt;

      if(elapsed_time >= duration)
        state = 1;

      //this is temporary to avoid infinite loops
      if(duration < 0)
        state = 1;
    }
  }

} /* namespace core */
