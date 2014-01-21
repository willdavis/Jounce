/*
 * timer_test.cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: bill
 */

#include "gtest/gtest.h"
#include "../../src/core/timer.h"

namespace core
{

  class TimerTest : public ::testing::Test {
  protected:
    Timer timer;
  };

  TEST_F(TimerTest, elapsed_time_must_be_greater_than_zero) {
    timer.get_elapsed_ns();
    int nanoseconds = timer.get_elapsed_ns();
    ASSERT_GT(nanoseconds, 0);
    ASSERT_LT(nanoseconds, 200);
  }

  TEST_F(TimerTest, clock_frequency_must_be_greater_than_zero) {
    int freq = timer.get_clock_frequency();
    ASSERT_GT(freq, 0);
    ASSERT_EQ(freq, 1);         //this is probably wrong.. but frequency doesn't seem to matter any more.
  }

} /* namespace core */
