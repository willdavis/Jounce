/*
 * event.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: bill
 */

#include "event.h"

namespace core
{

  Event::Event()
  {
  	priority = 1000;
  }

  Event::Event(int p)
  {
  	priority = p;
  }

  Event::~Event()
  {
    // TODO Auto-generated destructor stub
  }

  int Event::get_priority()
  {
  	return priority;
  }
}

 /* namespace core */
