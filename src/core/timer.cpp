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

  timespec* Timer::get_timespec_diff(timespec* ts1,timespec* ts2)
  {
    static struct timespec ts;
    ts.tv_sec = ts1->tv_sec - ts2->tv_sec;
    ts.tv_nsec = ts1->tv_nsec - ts2->tv_nsec;
    if (ts.tv_nsec < 0) {
      ts.tv_sec--;
      ts.tv_nsec += 1000000000;
    }
    return &ts;
  }

  /* returns elapsed time in nanoseconds */
  uint64_t Timer::get_elapsed_time() {
    timespec now;
    clock_gettime(1, &now);

    timespec* delta = get_timespec_diff(&now, &previous_time);
    uint64_t nseconds = delta->tv_sec * 1000000000LL + delta->tv_nsec;
    previous_time = now;

    return nseconds;
  }

  int Timer::get_clock_frequency() {
    return clock_frequency.tv_nsec;
  }

} /* namespace core */
