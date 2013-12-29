/*
 * timer.h
 *
 *  Created on: Dec 27, 2013
 *      Author: bill
 */

#ifndef TIMER_H_
#define TIMER_H_

namespace core
{

  class Timer
  {
  public:
    Timer();
    virtual ~Timer();
    double get_elapsed_time();
    long get_clock_frequency();

  protected:
    timespec clock_frequency;
    timespec previous_time;
  };

} /* namespace core */
#endif /* TIMER_H_ */
