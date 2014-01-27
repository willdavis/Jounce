/*
 * timer.h
 *
 *  Created on: Dec 27, 2013
 *      Author: bill
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include "./helpers/timespec_helper.h"

namespace core
{

  class Timer
  {
  public:
    Timer();
    virtual ~Timer();
    uint64_t get_elapsed_time();
    int get_clock_frequency();

  protected:
    timespec clock_frequency;
    timespec previous_time;
  };

} /* namespace core */
#endif /* TIMER_H_ */
