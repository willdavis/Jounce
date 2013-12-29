/*
 * timer.cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: bill
 */

#include <time.h>
#include "timer.h"

namespace core
{

  Timer::Timer()
  {
    clock_getres(CLOCK_REALTIME, &clock_frequency);
  }

  Timer::~Timer()
  {
    // TODO Auto-generated destructor stub
  }

  double Timer::get_elapsed_time() {
    return 0;
  }

  long Timer::get_clock_frequency() {
    return clock_frequency.tv_nsec;
  }

} /* namespace core */
