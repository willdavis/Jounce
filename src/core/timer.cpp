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
    get_elapsed_time();         //first time run returns garbage.  Throw those out!
  }

  Timer::~Timer()
  {
    // TODO Auto-generated destructor stub
  }

  double Timer::get_elapsed_time() {
    timespec now;
    clock_gettime(CLOCK_REALTIME, &now);

    double duration = (now.tv_nsec - previous_time.tv_nsec ) / clock_frequency.tv_nsec;
    previous_time = now;

    return duration;
  }

  long Timer::get_clock_frequency() {
    return clock_frequency.tv_nsec;
  }

} /* namespace core */
