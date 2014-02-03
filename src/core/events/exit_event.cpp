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

} /* namespace core */
