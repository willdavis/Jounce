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
    int get_elapsed_ns();
    int get_clock_frequency();

  protected:
    timespec clock_frequency;
    timespec previous_time;
  };

} /* namespace core */
#endif /* TIMER_H_ */
