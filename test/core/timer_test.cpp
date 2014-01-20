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
    timer.get_elapsed_time();
    double seconds = timer.get_elapsed_time();
    ASSERT_GT(seconds, 0);
    ASSERT_LT(seconds, 1);
  }

  TEST_F(TimerTest, clock_frequency_must_be_greater_than_zero) {
    long freq = timer.get_clock_frequency();
    ASSERT_GT(freq, 0);
    ASSERT_EQ(freq, 1);         //this is probably wrong.. but frequency doesn't seem to matter any more.
  }

} /* namespace core */
