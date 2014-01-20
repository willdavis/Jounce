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

  double Timer::get_elapsed_time() {
    timespec now;
    clock_gettime(1, &now);

    double duration = (double)(now.tv_nsec - previous_time.tv_nsec ) / (double)1E9;
    previous_time = now;

    return duration;
  }

  double Timer::get_clock_frequency() {
    return (double)(clock_frequency.tv_sec + clock_frequency.tv_nsec);
  }

} /* namespace core */
