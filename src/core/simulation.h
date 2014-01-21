/*
 * simulation.h
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "timer.h"

namespace core
{

  class Simulation
  {
  public:
    Simulation();
    virtual ~Simulation();

    void run();

    double duration;            // optional duration for simulation (in seconds)
    double elapsed_time;        // current elapsed time for the simulation (in seconds)
    int state;                  // stores the current simulation state ( 0 = off, 1 = done, -1 = errors)
    Timer core_timer;
  };

} /* namespace core */
#endif /* SIMULATION_H_ */
