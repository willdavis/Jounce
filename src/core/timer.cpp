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
  	// initialize timespec so we can get elapsed time without returning negative time.
  	previous_time.tv_sec = 0;
  	previous_time.tv_nsec = 0;

    clock_getres(1, &clock_frequency);	// not currently being used...  slow PC's might need this, but probably not.
    get_elapsed_time();         				// first time returns garbage.  Throw it away!
  }

  Timer::~Timer()
  {
    // TODO Auto-generated destructor stub
  }

  /* returns elapsed time in nanoseconds */
  uint64_t Timer::get_elapsed_time() {
    timespec now;
    clock_gettime(1, &now);

    timespec* delta = TimespecHelper::get_timespec_diff(&now, &previous_time);
    uint64_t nseconds = delta->tv_sec * 1000000000LL + delta->tv_nsec;
    previous_time = now;

    return nseconds;
  }

  int Timer::get_clock_frequency() {
    return clock_frequency.tv_nsec;
  }

} /* namespace core */
