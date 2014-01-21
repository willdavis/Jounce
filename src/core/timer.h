/*
 * timer.h
 *
 *  Created on: Dec 27, 2013
 *      Author: bill
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>

namespace core
{

  class Timer
  {
  public:
    Timer();
    virtual ~Timer();
    int get_elapsed_time();
    int get_clock_frequency();

    timespec* get_timespec_diff(timespec*,timespec*);

  protected:
    timespec clock_frequency;
    timespec previous_time;
  };

} /* namespace core */
#endif /* TIMER_H_ */
