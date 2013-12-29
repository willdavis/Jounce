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
  };

} /* namespace core */
#endif /* TIMER_H_ */
