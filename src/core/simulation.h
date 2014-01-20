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

    int get_state() { return state; }

    void run();

  protected:
    int state;          // stores the current simulation state ( 0 = off, 1 = done, -1 = errors)
  };

} /* namespace core */
#endif /* SIMULATION_H_ */
