/*
 * exit_event.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "exit_event.h"

namespace core
{

  ExitEvent::ExitEvent()
  {

  }

  ExitEvent::~ExitEvent()
  {
    // TODO Auto-generated destructor stub
  }

  // cast the void* to Simulation* and call exit()
  void ExitEvent::dispatch(Dispatcher* dispatcher)
  {
    dispatcher->close();
  }

  // return the highest event priority
  unsigned int ExitEvent::priority()
  {
  	return 0;
  }

  // return the real time offset from the start of the simulation (nanoseconds)
  uint64_t ExitEvent::timestamp()
  {
  	return 0;  //temporary
  }



} /* namespace core */
