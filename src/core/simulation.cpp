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
    state = 0;  //set state to off
  }

  Simulation::~Simulation()
  {
    // TODO Auto-generated destructor stub
  }

  void Simulation::run()
  {
    state = 1;  //exit with no errors
  }

} /* namespace core */
