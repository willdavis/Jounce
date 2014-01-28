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
  	priority = 0;
  }

  ExitEvent::~ExitEvent()
  {
    // TODO Auto-generated destructor stub
  }

  // cast the void* to Simulation* and call exit()
  void ExitEvent::process_event(void* pointer)
  {
    static_cast<core::Simulation *>(pointer)->exit();
  }

} /* namespace core */
