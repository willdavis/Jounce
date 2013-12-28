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
    bool get_time() { return true; }
  };

} /* namespace core */
#endif /* TIMER_H_ */
