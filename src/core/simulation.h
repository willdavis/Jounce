/*
 * simulation.h
 *
 *  Created on: Jan 19, 2014
 *      Author: bill
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

namespace core
{

  class Simulation
  {
  public:
    Simulation();
    virtual ~Simulation();

    void run();

    int duration;       // optional duration for simulation (in seconds)
    int state;          // stores the current simulation state ( 0 = off, 1 = done, -1 = errors)
  };

} /* namespace core */
#endif /* SIMULATION_H_ */
