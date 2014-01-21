/*
 * timer.cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: bill
 */

#include "timer.h"

namespace core
{

  Timer::Timer()
  {
    clock_getres(1, &clock_frequency);
    get_elapsed_time();         //first time run returns garbage.  Throw those out!
  }

  Timer::~Timer()
  {
    // TODO Auto-generated destructor stub
  }

  int Timer::get_elapsed_time() {
    timespec now;
    clock_gettime(1, &now);

    int delta = now.tv_nsec - previous_time.tv_nsec;
    previous_time = now;

    return delta;
  }

  int Timer::get_clock_frequency() {
    return clock_frequency.tv_nsec;
  }

} /* namespace core */
