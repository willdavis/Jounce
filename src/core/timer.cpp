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
